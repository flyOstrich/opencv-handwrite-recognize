#pragma once
#include "../common.h"
#include <highgui.h>

using namespace cv;
namespace Reader {
    class ImageReader {
    public:
        Mat readMatOfImage(char* image_url);
    };
}