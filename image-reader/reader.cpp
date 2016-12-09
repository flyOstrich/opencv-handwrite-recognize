#include "reader.h"
#include <stdlib.h>

using namespace cv;
using namespace std;


Mat Reader::ImageReader::readMatOfImage(char* image_url) {
    IplImage* image = cvLoadImage(image_url);
    IplImage* grayImage=cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
    cvCvtColor(image,grayImage,CV_RGB2GRAY);

    IplImage* pCannyImg = cvCreateImage(cvGetSize(grayImage),IPL_DEPTH_8U,1);

    cvCanny(grayImage, pCannyImg, 250,50, 3);

    cvShowImage("aaaa",pCannyImg);
//    pCannyImg=grayImage;
    cvWaitKey(0);

    int G,B,R;
    char* imageData = pCannyImg->imageData;
    for(int i=0;i<pCannyImg->height;i++){
        const char* rowData=imageData+i*image->widthStep;
        for(int j=0;j<pCannyImg->width;j++){
                 B=(int)*(unsigned char*)(rowData+j);
//                 G=(int)*(unsigned char*)(rowData+j*3+1);
//                 R=(int)*(unsigned char*)(rowData+j*3+2);
                 printf("(%d) ",B);
        }
        cout<<endl;
    }

}

