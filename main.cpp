#include <opencv2/opencv.hpp>
#include <fstream>
#include "mouse-draw/mousedraw.h"
#include <dirent.h>
#include "train/train.h"
#include "common.h"
#include "image-reader/reader.h"


using namespace std;
using namespace cv;






void buildImg() {
    BoxExtractor box;
    Mat res = box.MouseDraw("draw", Mat(400, 400, CV_8UC3, Scalar(0, 0, 0)), Scalar(255, 255, 255), 18);
    string mouse_draw_img = MOUSE_DRAW_IMG;
    imwrite(mouse_draw_img, res);
}


void testPredict(IplImage* img) {
    IplImage *test;
    char result[300]; //存放预测结果

    CvSVM svm;
    Train::FileScanner scanner;
    string hog_svm_data_s = HOG_SVM_DATA;
    const char *hog_svm_data = hog_svm_data_s.c_str();
    svm.load(hog_svm_data);//加载训练好的xml文件，这里训练的是10K个手写数字
    //检测样本
    string mouse_draw_img = MOUSE_DRAW_IMG;
    const char *draw_img = mouse_draw_img.c_str();
//    test = cvLoadImage(draw_img, 1); //待预测图片，用系统自带的画图工具随便手写
    test=img;
    if (!test) {
        cout << "not exist" << endl;
        return;
    }
    cout << "load image done" << endl;
    IplImage *trainTempImg = cvCreateImage(cvSize(28, 28), 8, 1);
    cvZero(trainTempImg);
    cvResize(img, trainTempImg);
    cvShowImage("predict img",trainTempImg);
    cvWaitKey(0);
    HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 9);
    vector<float> descriptors;//存放结果
    hog->compute(trainTempImg, descriptors, Size(1, 1), Size(0, 0)); //Hog特征计算
    cout << "HOG dims: " << descriptors.size() << endl;  //打印Hog特征维数  ，这里是324
    CvMat *SVMtrainMat = cvCreateMat(1, descriptors.size(), CV_32FC1);
    int n = 0;
    for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++) {
        cvmSet(SVMtrainMat, 0, n, *iter);
        n++;
    }

    int ret = svm.predict(SVMtrainMat);//检测结果
    map<int, string> res = scanner.getLabelCharacterMap();
    map<int, string>::iterator it = res.find(ret);
    cout << it->second << endl;
    cvReleaseImage(&test);
    cvReleaseImage(&trainTempImg);
}

int main() {


    Train::FileScanner fileScanner;

    fileScanner.train();

//    testTrain();
//    return 0;


//    Reader::ImageReader image_reader;
//    string s_image_url=getProjectDir()+"/numbers.jpg";
//    const char* image_url=s_image_url.c_str();
//    list<list<IplImage*>> imgMat=image_reader.readMatOfImage(image_url);
//    while (!imgMat.empty()){
//        list<IplImage*> listItem= imgMat.front();
//        while(!listItem.empty()){
//            IplImage* img=listItem.front();
//            testPredict(img);
//
//            listItem.pop_front();
//        }
//        imgMat.pop_front();
//    }

    return 0;
}








