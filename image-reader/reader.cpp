#include "reader.h"
#include <fstream>
#include <iostream>
#include <list>

#define EXPECTED_RGB_VAL 100
#define EXPECTED_PTS_CNT 10
#define SCAN_IMAGE_LENGTH 10

using namespace cv;
using namespace std;


list<list<IplImage*>> Reader::ImageReader::readMatOfImage(char *image_url) {


    list<list<IplImage*>> res;
    //读取图片,将其灰度化,进行cannny特征处理
    IplImage *image = cvLoadImage(image_url);
    IplImage *grayImage = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
    cvCvtColor(image, grayImage, CV_RGB2GRAY);
    IplImage *pCannyImg = cvCreateImage(cvGetSize(grayImage), IPL_DEPTH_8U, 1);
    cvCanny(grayImage, pCannyImg, 250, 200, 3);
    list<IplImage*> yIplImages=this->cutIplImage(pCannyImg,"y");
    while (!yIplImages.empty()){
        list<IplImage*> listItem;
        IplImage* img=yIplImages.front();
        listItem=this->cutIplImage(img,"x");
        res.push_front(listItem);
        yIplImages.pop_front();
    }

    return res;
}

list<IplImage*> Reader::ImageReader::cutIplImage(IplImage *image, string direction) {
    list<IplImage*> res;
    CvSize size;
    int step;
    //逐行扫描图片,将每一行文字数据分开
    if(direction=="x"){
        size.height=image->height;
        size.width=SCAN_IMAGE_LENGTH;
        step=image->width/SCAN_IMAGE_LENGTH;
    }else{
        size.width=image->width;
        size.height=SCAN_IMAGE_LENGTH;
        step = image->height / SCAN_IMAGE_LENGTH;
    }

    IplImage *cutImg = cvCreateImage(size, IPL_DEPTH_8U, 1);

    bool startFound = false;
    int start = -1;
    int end = -1;
    for (int i = 0; i < step; i++) {
        CvRect roiRect;
        if(direction=="x"){
           roiRect=cvRect(i*SCAN_IMAGE_LENGTH,0,SCAN_IMAGE_LENGTH,image->height);
        }else{
           roiRect=cvRect(0, i * SCAN_IMAGE_LENGTH, image->width, SCAN_IMAGE_LENGTH);
        }
        cvSetImageROI(image, roiRect);
        cvCopy(image, cutImg);
        cvResetImageROI(image);
        int count=this->getRowScanImgExpectCnt(cutImg);
//        cout<<count<<'-';
        if(count>EXPECTED_PTS_CNT){
            if(!startFound){
                startFound=true;
                start=i*SCAN_IMAGE_LENGTH;
            }
        }else{
            if(startFound){
                startFound=false;
                end=i*SCAN_IMAGE_LENGTH;
                IplImage* img=this->getRowIplImage(image,start,end,direction);
                res.push_front(img);
            }
        }
//        cout<<count<<endl;
    }
    return res;
}

IplImage* Reader::ImageReader::getRowIplImage(IplImage *image, int startRow, int endRow,string direction) {
    CvSize size;
    CvRect roiRect;
    if(direction=="x"){
        size=cvSize(endRow-startRow,image->height);
        roiRect=cvRect(startRow, 0, endRow - startRow, image->height);
    }else{
        size=cvSize(image->width, endRow - startRow);
        roiRect=cvRect(0, startRow, image->width, endRow - startRow);
    }

    IplImage *rowImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
    cvSetImageROI(image,roiRect);
    cvCopy(image, rowImage);
    cvResetImageROI(image);
    return rowImage;
}

int Reader::ImageReader::getRowScanImgExpectCnt(IplImage* image) {
    char* imageData = image->imageData;
    int count=0;
    for(int i=0;i<image->imageSize;i++){
        int cVal=(int) *(unsigned char *) (imageData + i);
        if(cVal>EXPECTED_RGB_VAL)count++;
    }
    return count;
}

