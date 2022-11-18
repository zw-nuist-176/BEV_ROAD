//
// Created by z on 11/11/22.
//

#ifndef CAPTURE_LANE_DETECTION_H
#define CAPTURE_LANE_DETECTION_H
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;

//class lane_detection {
//private:
//
//
//public:
//
//
//
//};
void GetROI(Mat src, Mat &image);
void DetectRoadLine(Mat src, Mat &image);
bool executeimp(Mat src, Mat &image, Point2d p, Point2d p2, Point2d p1, Point2d p4);



//class  lane_detection2{
//private:
//public:
//};


#endif //CAPTURE_LANE_DETECTION_H
