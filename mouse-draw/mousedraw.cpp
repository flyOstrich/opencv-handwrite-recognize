#include "mousedraw.h"
#include <iostream>
using namespace std;
BoxExtractor::BoxExtractor()
{
}

void BoxExtractor::mouseHandler(int event, int x, int y, int flags, void *param){
    BoxExtractor *self =static_cast<BoxExtractor*>(param);
    self->opencv_mouse_callback(event,x,y,flags,param);
}

void BoxExtractor::opencv_mouse_callback( int event, int x, int y, int , void *param ){
    handlerT * data = (handlerT*)param;
    switch( event ){
    // update the selected bounding box
    case EVENT_MOUSEMOVE:
        if( data->isDrawing ){
            data->points.push_back (cv::Point(x,y));
        }
        break;
        // start to select the bounding box
    case EVENT_LBUTTONDOWN:
        data->isDrawing = true;
        data->points.clear ();
        data->points.push_back (cv::Point(x,y));
        break;
        // cleaning up the selected bounding box
    case EVENT_LBUTTONUP:
        data->isDrawing = false;
        break;
    }
}

Mat BoxExtractor::MouseDraw(Mat img){
    return MouseDraw("DRAW AN DIGIT", img,Scalar(0,0,0),4);
}

Mat BoxExtractor::MouseDraw(string windowName, Mat img,Scalar color, int border){
    int key=0;
//    string windowName1=windowName;
    cout<<"请在弹出窗口上书写:"+windowName+",并按enter保存!"<<endl;
    imshow(windowName,img);
    params.image=img.clone();
    setMouseCallback(windowName, mouseHandler, (void *)&params );
    while(!(key==32 || key==27 || key==13)){
        int length = params.points.size ();
        for(int i = 0;i<length && length > 2;i++){
            if(i == length-1){
                cv::line (params.image,params.points.at (i),params.points.at (i),color,border);
            }else{
                cv::line (params.image,params.points.at (i),params.points.at (i+1),color,border);
            }
        }
        imshow(windowName,params.image);
//        params.image=img.clone();
        key=waitKey(1);
    }
    destroyAllWindows();
    return params.image;
}
