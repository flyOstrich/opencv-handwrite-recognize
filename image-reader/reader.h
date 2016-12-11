#pragma once

#include "../common.h"
#include <highgui.h>
#include <list>

using namespace cv;
namespace Reader {
    class ImageReader {
    public:
        list<list<IplImage*>> readMatOfImage(const char *image_url);
        IplImage* resizeImage(IplImage* image,int size);
        IplImage* cutGrayImageByColorVal(IplImage* img,int colorVal);
        void saveIplImageData(IplImage* img,string url);

    private:
        IplImage *getRowIplImage(IplImage *image, int startRow, int endRow,string direction);
        list<IplImage*> cutIplImage(IplImage* image,string direction);
        int getRowScanImgExpectCnt(IplImage *image);
    };
}