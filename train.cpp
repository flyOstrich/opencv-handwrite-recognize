#pragma once
#include <dirent.h>
#include <iostream>
#include <list>

namespace Train {

    class FileScanner
    {
     public:
     std::list<DIR> *getFiles(const char* dirname);

    };
}

std::list<DIR>* Train::FileScanner::getFiles(const char *dirname) {
    DIR* pdir=opendir(dirname);
    char buf[80];

    struct dirent *direntp;
    while ((direntp = readdir(pdir)) != NULL){
        sprintf(buf,"%s/%s",dirname,direntp->d_name);
//        if (get_file_size_time(buf) == -1)break;
    }

}

