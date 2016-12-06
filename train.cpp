#pragma once

#include "train.h"
#include <dirent.h>
#include <iostream>
#include <list>


std::list<std::string>* Train::FileScanner::getFiles(const char *dirname,const char* ext) {
    DIR* pdir=opendir(dirname);
    std::list<std::string> res;
    struct dirent *direntp;
    while ((direntp = readdir(pdir)) != NULL){
          std::string fname=direntp->d_name;
          size_t loc=fname.find_last_of(ext);
          std::cout<<"----------"<<std::endl;
          std::cout<<loc<<std::endl;`
          res.push_front(fname);
          std::cout<<direntp->d_name<<std::endl;
    }

}

