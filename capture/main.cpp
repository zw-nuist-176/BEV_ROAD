#include <iostream>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include "lane_detection.h"

using namespace std;
using namespace cv;


int main() {

    cv::VideoCapture capture("catroad.mp4");
//    cv::VideoCapture capture(0);
    if(!capture.isOpened()){
        cout<<"can not open video file !"<<endl;
        pause();
        return -1;
    }
    Point2d p1(339,301);
    Point2d p2(604,317);
    Point2d p3(142,434);
    Point2d p4(770,420);

    Mat frame,image;
    while(capture.read(frame)){
        char key = waitKey(10);
        if(key == 27){
            break;
        }
        GetROI(frame, image);
        DetectRoadLine(frame, image);
        imshow("frame",frame);
//        executeimp(frame, image, p1, p2, p3, p4);


    }
    capture.release();
    destroyAllWindows();
    pause();
    return 0;
}
