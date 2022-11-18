#include <iostream>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include "lane_detection.h"

using namespace std;
using namespace cv;


int main() {

    cv::VideoCapture capture("catroad.mp4");
    if(!capture.isOpened()){
        cout<<"can not open video file !"<<endl;
        pause();
        return -1;
    }
//
//    Point2d p4(484,412);
//    Point2d p1(150,602);
//    Point2d p3(772,413);
//    Point2d p2(1089,648);
//    Point2d p4(504,432);
//    Point2d p1(180,622);
//    Point2d p3(792,433);
//    Point2d p2(1109,668);


    //待定
//    Point2d p1(339,301);
//    Point2d p3(604,317);
//    Point2d p4(142,434);
//    Point2d p2(812,448);
    Mat frame,image;
    while(capture.read(frame)){
        char key = waitKey(10);
        if(key == 27){
            break;
        }
        GetROI(frame, image);
        DetectRoadLine(frame, image);
        imshow("frame",frame);
//        executeimp(frame, image, p2, p1, p4, p3);
//        executeimp(frame, image, p4, p3, p1, p2);

    }
    capture.release();
    destroyAllWindows();
    pause();
    //std::cout << "Hello, World!" << std::endl;
    return 0;
}
