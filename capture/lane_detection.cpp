//
// Created by z on 11/11/22.
//
#include <iostream>
#include "lane_detection.h"

using namespace std;
using namespace cv;

//获取兴趣范围

void GetROI(Mat src, Mat &ROI) {
    int width = src.cols;
    int height = src.rows;

    vector<Point> pts;
    Point ptA((width / 8 ) * 0.5,(height / 20) * 19);
    Point ptB((width / 8 ) * 0.5,(height / 8) * 7);
    Point ptC((width / 10 ) * 3,(height / 5) * 3);
    Point ptD((width / 10 ) * 7,(height / 5) * 3);
    Point ptE((width / 8 ) * 8,(height / 8) * 7);
    Point ptF((width / 8 ) * 8,(height / 20) * 19);
    pts = {ptA,ptB,ptC,ptD,ptE,ptF};

    vector<vector<Point>> ppts;
    ppts.push_back(pts);

    Mat mask = Mat::zeros(src.size(),src.type());
    fillPoly(mask,ppts,Scalar::all(255));

    src.copyTo(ROI,mask);
    imshow("thresh1",ROI);
}
//分割道路线
void DetectRoadLine(Mat src, Mat &ROI) {
    Mat gray;
    //色彩转化（输入图像，输出图像，颜色空间变换标志符，通道数目）
    cvtColor(ROI,gray,COLOR_BGR2GRAY);


    Mat thresh;
    // threshold 对灰度图像进行阈值操作得到二值图像或者去噪
//    第一个参数：InputArray类型的src，输入数组，必须为单通道，8位或32位的浮点型Mat即可。
//    第二个参数：OutputArray类型的dst，与输入有一样的尺寸和类型。
//    第三个参数：double类型的thresh，阈值。
//    第四个参数：double类型的maxval，当第五个参数的类型为CV_THRESH_BINARY或CV_THRESH_BINARY_INV时的最大值。
//    第五个参数：int类型的type，阈值类型
    threshold(gray,thresh,180,255,THRESH_BINARY);

    imshow("ROI2",thresh);
    vector<Point> left_line;
    vector<Point> right_line;
    //中线
    vector<Point> middle_line;

    //获取非零像素
    //左车道线
    for(int i = 0;i<thresh.cols/2;i++){
        for(int j= 0;j<thresh.rows;j++){
            if(thresh.at<uchar>(j,i) == 255){
                left_line.push_back(Point(i,j));
            }
        }
    };
    //右车道线
    for(int i = thresh.cols/2;i<thresh.cols;i++){
        for(int j = 0;j<thresh.rows;j++){
            if(thresh.at<uchar>(j,i) == 255){
                right_line.push_back(Point(i,j));
            }
        }
    }
//    //中间车道线
//    for(int = i = )

    //绘制车道线
    if(left_line.size() > 0 && right_line.size()>0){
        Point B_L = (left_line[0]);
        Point T_L = (left_line[left_line.size() - 1]);
        Point T_R = (right_line[0]);
        Point B_R = (right_line[right_line.size() - 1]);

        circle(src,B_L,10,Scalar(0,0,255),-1 );
        circle(src,T_L,10,Scalar(0,255,0),-1 );
        circle(src,T_R,10,Scalar(255,0,0),-1 );
//        circle(src,B_R,10,Scalar(0,255,255),-1 );
        circle(src,B_R,10,Scalar(128,0,128),-1 );

        line(src,Point(B_L),Point(T_L),Scalar(0,255,0),10);
        line(src,Point(T_R),Point(B_R),Scalar(0,255,0),10);

        vector<Point> pts;
//        pts = {B_L,T_L,T_R,B_R};
       pts = {B_L,T_L,T_R,B_R};
        vector<vector<Point>> ppts;
        ppts.push_back(pts);
//        fillPoly(src,ppts,Scalar(133,230,238));
        fillPoly(src,ppts,Scalar(50,205,50));
//        addWeighted( src, 0.5,src, 0.5, 0,src);

    }


}
bool executeimp(Mat src,Mat &dst,Point2d p1,Point2d p2,Point2d p3,
                                Point2d p4) {
    if (src.data)
    {
        Point2f corners[4]={p1,p2,p3,p4};//原图四个点
        Point2f corners_trans[4];//逆透视图四个点

        //**车载场景图象的其他参数**//
        float roi_x0=0;
        float roi_y0=228;
        float ROI_HEIGHT=30000;
        float ROI_WIDTH=3750;
        //************************//
        //设定逆透视图的宽度
        float IPM_WIDTH=500;
        float N=5;
        //保证逆透视图的宽度大概为N个车头宽
        float sacale=(IPM_WIDTH/N)/ROI_WIDTH;
        float IPM_HEIGHT=ROI_HEIGHT * sacale;


//        cout << IPM_WIDTH/2-IPM_WIDTH/(2*N)<<endl;
//        cout << IPM_WIDTH/2+IPM_WIDTH/(2*N)<<endl;
//        cout << IPM_HEIGHT<<endl;

        //计算原图到逆透视图和逆透视图到原图的变换矩阵
        Mat warpMatrix_src2ipm;
        warpMatrix_src2ipm = getPerspectiveTransform(corners, corners_trans);
        warpPerspective(src, dst, warpMatrix_src2ipm, dst.size());
        //标出两组点
//        for(int i=0;i<4;i++)
//            circle(src,corners[i],5,Scalar(0,255,255),4);
//        for(int i=0;i<4;i++)
//            circle(dst,corners_trans[i],5,Scalar(0,255,255),4);

 //       imshow("img",src);
        imshow("dst",dst);
//        imwrite("../img/original123.jpg", img);
//        imwrite("../img/original123.jpg", dst);

    }
    return true;
};