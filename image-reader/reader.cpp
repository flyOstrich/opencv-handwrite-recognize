#include "reader.h"
#include <fstream>
#include <iostream>
#include <list>

#define EXPECTED_RGB_VAL 200
#define EXPECTED_PTS_CNT 10
#define SCAN_IMAGE_LENGTH 10

using namespace cv;
using namespace std;


list<list<IplImage *>> Reader::ImageReader::readMatOfImage(const char *image_url) {


    list<list<IplImage *>> res;
    //读取图片,将其灰度化,进行cannny特征处理
    IplImage *image = cvLoadImage(image_url);
    IplImage *grayImage = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
    cvCvtColor(image, grayImage, CV_RGB2GRAY);
//    IplImage *pCannyImg = cvCreateImage(cvGetSize(grayImage), IPL_DEPTH_8U, 1);
//    cvCanny(grayImage, pCannyImg, 250, 200, 3);
    cvShowImage("gray",grayImage);
    cvWaitKey(0);
    list<IplImage *> yIplImages = this->cutIplImage(grayImage, "y");
    while (!yIplImages.empty()) {
        list<IplImage *> listItem;
        IplImage *img = yIplImages.front();
//        cvShowImage("aaaa", img);
//        cvWaitKey(0);
        listItem = this->cutIplImage(img, "x");
        res.push_front(listItem);
        yIplImages.pop_front();
    }

    return res;
}

list<IplImage *> Reader::ImageReader::cutIplImage(IplImage *image, string direction) {
    list<IplImage *> res;
    CvSize size;
    int step;
    //逐行扫描图片,将每一行文字数据分开
    if (direction == "x") {
        size.height = image->height;
        size.width = SCAN_IMAGE_LENGTH;
        step = image->width / SCAN_IMAGE_LENGTH;
    } else {
        size.width = image->width;
        size.height = SCAN_IMAGE_LENGTH;
        step = image->height / SCAN_IMAGE_LENGTH;
    }

    IplImage *cutImg = cvCreateImage(size, IPL_DEPTH_8U, 1);

    bool startFound = false;
    int start = -1;
    int end = -1;
    for (int i = 0; i < step; i++) {
        CvRect roiRect;
        if (direction == "x") {
            roiRect = cvRect(i * SCAN_IMAGE_LENGTH, 0, SCAN_IMAGE_LENGTH, image->height);
        } else {
            roiRect = cvRect(0, i * SCAN_IMAGE_LENGTH, image->width, SCAN_IMAGE_LENGTH);
        }
        cvSetImageROI(image, roiRect);
        cvCopy(image, cutImg);
        cvResetImageROI(image);
        int count = this->getRowScanImgExpectCnt(cutImg);
//        cout<<count<<'-';
        if (count > EXPECTED_PTS_CNT) {
            if (!startFound) {
                startFound = true;
                start = i * SCAN_IMAGE_LENGTH;
            }
        } else {
            if (startFound) {
                startFound = false;
                end = i * SCAN_IMAGE_LENGTH;
                IplImage *img = this->getRowIplImage(image, start, end, direction);
//                cvShowImage("bbb", img);
//                cvWaitKey(0);
                res.push_front(img);
            }
        }
    }
    return res;
}

IplImage *Reader::ImageReader::getRowIplImage(IplImage *image, int startRow, int endRow, string direction) {
    CvSize size;
    CvRect roiRect;
    if (direction == "x") {
        size = cvSize(endRow - startRow, image->height);
        roiRect = cvRect(startRow, 0, endRow - startRow, image->height);
    } else {
        size = cvSize(image->width, endRow - startRow);
        roiRect = cvRect(0, startRow, image->width, endRow - startRow);
    }

    IplImage *rowImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
    cvSetImageROI(image, roiRect);
    cvCopy(image, rowImage);
    cvResetImageROI(image);
    return rowImage;
}

int Reader::ImageReader::getRowScanImgExpectCnt(IplImage *image) {
    int count = 0;
    for(int i=0;i<image->height;i++){
        for(int j=0;j<image->width;j++) {
            int cVal= (int)*(unsigned char*)(image->imageData+i*image->widthStep+j);
            if (cVal > EXPECTED_RGB_VAL)count++;
        }
    }
    return count;
}

IplImage *Reader::ImageReader::resizeImage(IplImage *image, int size) {
    int maxLen = image->width > image->height ? image->width : image->height;
    int rest = maxLen % size;
    if (rest > 0) size = maxLen + (28 - rest);
    IplImage *resizedImg = cvCreateImage(cvSize(size, size), IPL_DEPTH_8U, 1);
    cvSetZero(resizedImg);
    cvSetImageROI(resizedImg, cvRect(0, 0, image->width, image->height));
    cvCopy(image, resizedImg);
    cvResetImageROI(resizedImg);

    return resizedImg;

}

IplImage *Reader::ImageReader::cutGrayImageByColorVal(IplImage *img, int colorVal) {
    IplImage *res;
    if (img->nChannels != 1) {
        cout << "该图片不是灰度图！" << endl;
        return res;
    }
    ofstream resMat(getProjectDir()+"/resMat.txt");
//    for(int i=0;i<img->height;i++){
//        for(int j=0;j<img->width;j++) {
//            char cVal= *(unsigned char*)(img->imageData+i*img->widthStep+j);
//            int a=(int)cVal;
//            printf("%d-",cVal);
//            resMat<<a<<"-";
//        }
//        printf("\n");
//        resMat<<endl;
//    }

//    IplImage* cpImg=cvCreateImage(cvSize(1,img->height),IPL_DEPTH_8U,1);
//    cvSetImageROI(img, cvRect(0, 0, 1, img->height));
//    cvCopy(img,cpImg);

//    resMat<<endl;
//    resMat<<endl;
//    resMat<<endl;
//    resMat<<endl;
//    resMat<<endl;
//    resMat<<endl;
//    for(int k=0;k<cpImg->width*cpImg->height;k++){
//        int cVal= (int)*(unsigned char*)(img->imageData+k);
//        resMat<<cVal<<"-";
//    }
//    resMat<<endl;
//
//
//    resMat.close();
//
//    return res;
//    CvMat* mat=cvCreateMatHeader(1,img->height,CV_8UC1);

//    CvMat* mat2=cvGetCol(img,mat,6);


//    return res;

    IplImage* cpImg;
    //找出上边界
    int topBound = 0;
    while (topBound < img->height) {
        cpImg=cvCreateImage(cvSize(img->width,5),IPL_DEPTH_8U,1);
        cvSetImageROI(img, cvRect(0, topBound, img->width, 5));
        cvCopy(img,cpImg);
        cvResetImageROI(img);
//        cvShowImage("top",cpImg);
//        cvWaitKey(1000);
        int count=this->getRowScanImgExpectCnt(cpImg);
        if(count!=0){
            resMat<<topBound<<":"<<count<<endl;
            cvResetImageROI(img);
            cvReleaseImage(&cpImg);
            break;
        }
        topBound++;
    }
    //找出下边界
    int bottomBound=img->height-1;
    while (bottomBound >0) {
        cpImg=cvCreateImage(cvSize(img->width,5),IPL_DEPTH_8U,1);
        cvSetImageROI(img, cvRect(0, bottomBound-5, img->width, 5));
        cvCopy(img,cpImg);
        cvResetImageROI(img);

//        cvShowImage("bottom",cpImg);
//        cvWaitKey(1000);
        int count=this->getRowScanImgExpectCnt(cpImg);

        if(count!=0){
            resMat<<bottomBound<<":"<<count<<endl;
            cvResetImageROI(img);
            cvReleaseImage(&cpImg);
            break;
        }
        bottomBound--;
    }
    //找出左边界
    int leftBound=0;
    while (leftBound < img->width) {
        cpImg=cvCreateImage(cvSize(5,img->height),IPL_DEPTH_8U,1);
        cvSetZero(cpImg);
        cvSetImageROI(img, cvRect(leftBound, 0, 5, img->height));
        cvCopy(img,cpImg);
        cvResetImageROI(img);
//        cvShowImage("left",cpImg);
//        cvWaitKey(1000);
        int count=this->getRowScanImgExpectCnt(cpImg);
        if(count!=0){
            resMat<<leftBound<<":"<<count<<endl;
            cvResetImageROI(img);
            cvReleaseImage(&cpImg);
            break;
        }
        leftBound++;
    }
    //找出右边界
    int rightBound=img->width-1;
    while (rightBound >0) {
        cpImg=cvCreateImage(cvSize(5,img->height),IPL_DEPTH_8U,1);
        cvSetImageROI(img, cvRect(rightBound-5,0, 5, img->height));
        cvCopy(img,cpImg);
        cvResetImageROI(img);
//        cvShowImage("right",cpImg);
//        cvWaitKey(1000);
        int count=this->getRowScanImgExpectCnt(cpImg);
        if(count!=0){
            resMat<<rightBound<<":"<<count<<endl;
            cvResetImageROI(img);
            cvReleaseImage(&cpImg);
            break;
        }
        rightBound--;
    }
    resMat.close();
    res=cvCreateImage(cvSize(rightBound-leftBound,bottomBound-topBound),IPL_DEPTH_8U,1);
    CvRect rect = cvRect(leftBound, topBound, rightBound-leftBound, bottomBound-topBound);
//    printf("(%d,%d,%d,%d)",leftBound,topBound,rightBound-leftBound,bottomBound-topBound);
    cvSetImageROI(img,rect);
    cvCopy(img,res);
    return res;

}
void Reader::ImageReader::saveIplImageData(IplImage *img, string url) {
      ofstream res(url);
      for(int i=0;i<img->height;i++){
          for(int j=0;j<img->width;j++){
              int cVal=(int)*(unsigned char*)(img->imageData+img->widthStep*i+j);
              res<<cVal<<"-";
          }
          res<<endl;

      }
      res.close();
}
