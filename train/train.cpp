#include "train.h"
#include <fstream>
#include "../common.h"
#include "../image-reader/reader.h"

void int2str(const int &int_temp, string &string_temp) {
    stringstream stream;
    stream << int_temp;
    string_temp = stream.str();   //此处也可以用 stream>>string_temp
}

list<string> Train::FileScanner::getFiles(const char *dirname, const char *ext) {
    DIR *pdir = opendir(dirname);
    list<string> res;
    struct dirent *direntp;
    while ((direntp = readdir(pdir)) != NULL) {
        std::string fname = direntp->d_name;
        size_t loc = fname.find(ext);
        if (loc != -1) {
            res.push_front(fname);
        }
    }
    closedir(pdir);
    return res;
}

list<pair<string, int>> Train::FileScanner::parseTrainConfig(string dirname, string trainConfigFile) {
    string config_file_url = dirname + "/" + trainConfigFile;
    ifstream config_file(config_file_url);
    list<pair<string, int>> res;
    if (config_file.is_open()) {
        string buf;
        while (getline(config_file, buf)) {
            size_t loc = buf.find(":");
            char *text = (char *) malloc(sizeof(char) * 10);
            char *count = (char *) malloc(sizeof(char) * 10);
            buf.copy(text, loc, 0);
            buf.copy(count, buf.length() - loc, loc + 1);
            string t = text;
            int c = (*count - 48);
            res.push_front(pair<string, int>(t, c));
        }
    } else {
        cout << "config file not opened!  -->" + config_file_url << endl;
    }
    config_file.close();
    return res;
}

void Train::FileScanner::genPathTextForTrain(string dir, string text_file_name) {
    const char *dirname = dir.c_str();
    const char *ext = ".bmp";
    Train::FileScanner scanner;
    list<string> bmpfiles = scanner.getFiles(dirname, ext);
    ofstream result(dir + "/" + text_file_name);
    if (result.is_open()) {
        while (!bmpfiles.empty()) {
            string file_name = (string) bmpfiles.front();
            bmpfiles.pop_front();
            char *value = (char *) malloc(sizeof(char) * 50);
            size_t loc = file_name.find("_");
            file_name.copy(value, loc, 0);
            result << dir + "/" + file_name << endl;
            result << value << endl;
        }
    }
    result.close();
}

void Train::FileScanner::buildImg(string img_url, string img_title) {
    BoxExtractor box;
    Mat res = box.MouseDraw(img_title, Mat(400, 400, CV_8UC3, Scalar(0, 0, 0)), Scalar(255, 255, 255), 18);
    imwrite(img_url, res);
}

void Train::FileScanner::buildTrainImgsByConfig(string dirname, string trainConfigFile) {
    Train::FileScanner fileScanner;
    map<string, int> map = fileScanner.getCharacterLabelMap();
    list<pair<string, int>> config_list = fileScanner.parseTrainConfig(dirname, trainConfigFile);
    dirname = dirname + "/train-images";
    while (!config_list.empty()) {
        pair<string, int> config = config_list.front();
        int count = config.second;
        string text = config.first;
        int val = map.find(text)->second;
        string cVal;
        int2str(val, cVal);
        for (int i = 0; i < count; i++) {
            const char *dn = dirname.c_str();
            char ext[] = ".bmp";
            list<string> imgs = fileScanner.getFiles(dn, ext);
            int exist_count = 0;
            while (!imgs.empty()) {
                string img_file_name = imgs.front();
                size_t loc = img_file_name.find(cVal + "_");
                if (loc == 0) {
                    exist_count++;
                }
                imgs.pop_front();
            }
            string order;
            int2str(++exist_count, order);
            cout << "order:" << order << endl;
            cout << "cVal:" << cVal << endl;
            string img_url = dirname + "/" + cVal + "_" + order + ".bmp";
            fileScanner.buildImg(img_url, text);

        }
        config_list.pop_front();
    }
}

map<int, string> Train::FileScanner::getLabelCharacterMap() {
    ifstream labelCharacterData(LABEL_CHARACTER_MAP);
    string *buf = (string *) malloc(sizeof(char) * 10);
    map<int, string> res;
    while (labelCharacterData) {
        if (getline(labelCharacterData, *buf)) {
            size_t loc = buf->find_first_of(":");
            string sLabel = buf->substr(0, loc);
            int nLabel = stoi(sLabel);
            string sCharacter = buf->substr(loc + 1, buf->length());
            pair<int, string> mapItem = pair<int, string>(nLabel, sCharacter);
            res.insert(mapItem);
        }
    }
    return res;
}

map<string, int> Train::FileScanner::getCharacterLabelMap() {
    ifstream labelCharacterData(LABEL_CHARACTER_MAP);
    string *buf = (string *) malloc(sizeof(char) * 10);
    map<string, int> res;
    while (labelCharacterData) {
        if (getline(labelCharacterData, *buf)) {
            size_t loc = buf->find_first_of(":");
            string sLabel = buf->substr(0, loc);
            int nLabel = stoi(sLabel);
            string sCharacter = buf->substr(loc + 1, buf->length());
            pair<string, int> mapItem = pair<string, int>(sCharacter, nLabel);
            res.insert(mapItem);
        }
    }
    return res;
}

void Train::FileScanner::train() {
    this->genPathTextForTrain(getProjectDir() + "/train/train-images", "result.txt");

    //读取训练样本图片地址及对应的label
    vector<string> img_path;//输入文件名变量
    vector<int> img_catg;
    int nLine = 0;
    string buf;
    ifstream svm_data(HOG_TXT_DATA);//训练样本图片的路径都写在这个txt文件中，使用bat批处理文件可以得到这个txt文件
    unsigned long n;
    while (svm_data)//将训练样本文件依次读取进来
    {
        if (getline(svm_data, buf)) {
            nLine++;
            if (nLine % 2 == 0)//注：奇数行是图片全路径，偶数行是标签
            {
                img_catg.push_back(atoi(buf.c_str()));//atoi将字符串转换成整型，标志(0,1，2，...，9)，注意这里至少要有两个类别，否则会出错
            } else {
                img_path.push_back(buf);//图像路径
            }
        }
    }
    svm_data.close();//关闭文件


    CvMat *data_mat, *res_mat;
    int nImgNum = nLine / 2; //nImgNum是样本数量，只有文本行数的一半，另一半是标签
    data_mat = cvCreateMat(nImgNum, 324,
                           CV_32FC1);  //第二个参数，即矩阵的列是由下面的descriptors的大小决定的，可以由descriptors.size()得到，且对于不同大小的输入训练图片，这个值是不同的
    cvSetZero(data_mat);
    //类型矩阵,存储每个样本的类型标志
    res_mat = cvCreateMat(nImgNum, 1, CV_32FC1);
    cvSetZero(res_mat);
    IplImage *src;
    IplImage *trainImg = cvCreateImage(cvSize(28, 28), IPL_DEPTH_8U,
                                       1);//需要分析的图片，这里默认设定图片是28*28大小，所以上面定义了324，如果要更改图片大小，可以先用debug查看一下descriptors是多少，然后设定好再运行

    //处理HOG特征
    for (string::size_type i = 0; i != img_path.size(); i++) {
        src = cvLoadImage(img_path[i].c_str(), 1);
        if (src == NULL) {
            cout << "无法加载图片: " << img_path[i].c_str() << endl;
            continue;
        }


        IplImage *grayImage = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
        cvCvtColor(src, grayImage, CV_RGB2GRAY);
//        IplImage *pCannyImg = cvCreateImage(cvGetSize(grayImage), IPL_DEPTH_8U, 1);
//        cvSetZero(pCannyImg);
//        cvCanny(grayImage, pCannyImg, 51, 10, 3);

        Reader::ImageReader reader;
        char a=(char)i;
        reader.saveIplImageData(grayImage,getProjectDir()+"/train/train-text/"+a);
//        cout << "deal with\t" << img_path[i].c_str() << endl;
        src=reader.cutGrayImageByColorVal(grayImage,200);



        cvResize(src, trainImg);
        cvvShowImage("train img", trainImg);

        cvWaitKey(100);

        HOGDescriptor *hog = new HOGDescriptor(
                cvSize(28, 28)    //winSize
                , cvSize(14, 14)  //表示块（block）大小
                , cvSize(7, 7)    //块滑动增量（blockStride）大小
                , cvSize(7, 7)    //cvSize(4, 3)表示胞元（cell）大小
                , 9); //9表示每个胞单元中梯度直方图的数量
        vector<float> descriptors;//存放结果
        hog->compute(trainImg, descriptors, Size(28, 28), Size(0, 0)); //Hog特征计算
        cout << "HOG dims: " << descriptors.size() << endl;
        n = 0;
        for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++) {
            cvmSet(data_mat, i, n, *iter);//存储HOG特征
            n++;
        }
        cvmSet(res_mat, i, 0, img_catg[i]);
        cout << "Done !!!: " << img_path[i].c_str() << " " << img_catg[i] << endl;
    }
    CvSVM svm;//新建一个SVM
    CvSVMParams param;//这里是SVM训练相关参数
    CvTermCriteria criteria;
    criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON);
    param = CvSVMParams(CvSVM::C_SVC, CvSVM::RBF, 10.0, 0.09, 1.0, 10.0, 0.5, 1.0, NULL, criteria);
    svm.train(data_mat, res_mat, NULL, NULL, param);//训练数据
    //保存训练好的分类器
    std::cout << "saving... ... !!! \n " << endl;
    string hog_svm_data_file_s = HOG_SVM_DATA;
    const char *hog_svm_data_file = hog_svm_data_file_s.c_str();
    svm.save(hog_svm_data_file);
    cout << "HOG_SVM_DATA.xml is saved !!! \n exit train process" << endl;
    cvReleaseMat(&data_mat);
    cvReleaseMat(&res_mat);
    cvReleaseImage(&trainImg);
}


