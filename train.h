#pragma once
#include <dirent.h>
#include <iostream>
#include <list>

namespace Train {

    class FileScanner
    {
    public:
        std::list<std::string> *getFiles(const char* dirname,const char* ext);

    };
}