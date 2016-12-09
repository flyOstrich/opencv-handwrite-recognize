#include "train.h"
#include <fstream>
#include "../common.h"

void int2str(const int &int_temp,string &string_temp)
{
    stringstream stream;
    stream<<int_temp;
    string_temp=stream.str();   //此处也可以用 stream>>string_temp
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
    string config_file_url=dirname+"/"+trainConfigFile;
    ifstream config_file(config_file_url);
    list<pair<string, int>> res;
    if(config_file.is_open()){
        string buf;
        while(getline(config_file,buf)){
            size_t loc=buf.find(":");
            char* text=(char*)malloc(sizeof(char)*10);
            char* count=(char*)malloc(sizeof(char)*10);
            buf.copy(text,loc,0);
            buf.copy(count,buf.length()-loc,loc+1);
            string t=text;
            int c=(*count-48);
            res.push_front(pair<string,int>(t,c));
        }
    }else{
        cout<<"config file not opened!  -->"+config_file_url<<endl;
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

void Train::FileScanner::buildImg(string img_url,string img_title) {
    BoxExtractor box;
    Mat res = box.MouseDraw(img_title, Mat(400, 400, CV_8UC3, Scalar(0, 0, 0)), Scalar(255, 255, 255), 18);
    imwrite(img_url, res);
}

void Train::FileScanner::buildTrainImgsByConfig(string dirname,string trainConfigFile) {
    Train::FileScanner fileScanner;
    map<string, int> map=fileScanner.getCharacterLabelMap();
    list<pair<string,int>> config_list=fileScanner.parseTrainConfig(dirname,trainConfigFile);
    dirname=dirname+"/train-images";
    while (!config_list.empty()){
        pair<string,int> config=config_list.front();
        int count = config.second;
        string text=config.first;
        int val=map.find(text)->second;
        string cVal;
        int2str(val,cVal);
        for(int i=0;i<count;i++){
            const char* dn=dirname.c_str();
            char ext[]=".bmp";
            list<string> imgs=fileScanner.getFiles(dn,ext);
            int exist_count=0;
            while(!imgs.empty()){
                string img_file_name=imgs.front();
                size_t loc=img_file_name.find(cVal+"_");
                if(loc==0){
                    exist_count++;
                }
                imgs.pop_front();
            }
            string order;
            int2str(++exist_count,order);
            cout<<"order:"<<order<<endl;
            cout<<"cVal:"<<cVal<<endl;
            string img_url=dirname+"/"+cVal+"_"+order+".bmp";
            fileScanner.buildImg(img_url,text);

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
            pair<string, int> mapItem = pair<string, int>( sCharacter,nLabel);
            res.insert(mapItem);
        }
    }
    return res;
}


