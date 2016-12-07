#pragma once
#include <dirent.h>
#include <list>
#include <cv.h>
#include "../mouse-draw/mousedraw.h"
using namespace std;
namespace Train {

    class FileScanner
    {
    public:
        std::list<std::string> getFiles(const char* dirname,const char* ext);
        std::list<pair<string,int>> parseTrainConfig(string dirname,string trainConfigFile);
        map<int, string> getLabelCharacterMap();
        map<string, int> getCharacterLabelMap();
        void genPathTextForTrain(string dir,string text_file_name);
        void buildImg(string img_url,string img_title);
        void buildTrainImgsByConfig(string dirname,string trainConfigFile);

    };

}