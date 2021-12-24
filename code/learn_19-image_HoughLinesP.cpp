#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv) {
    Mat src, dst, gray_src, dst2;
    src = imread("road/straight2.jpg");
    if (!src.data) {
        printf("could not load image src...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    char input_title[] = "input_image";
    char output_title[] = "hough-line-detection";
    // char output_title2[] = "output_image2";
    // char output_title3[] = "output_image3";
    // char output_title4[] = "final_result";
    /*
    霍夫直线介绍：
    Hough Line Transform用来做直线检测
    前提条件 – 边缘检测已经完成
    平面空间到极坐标空间转换
    对于任意一条直线上的所有点来说
    变换到极坐标中，从[0~360]空间，可以得到r的大小
    属于同一条直线上点在极坐标空(r, theta)必然在一个点上有最强的信号出
    现，根据此反算到平面坐标中就可以得到直线上各点的像素坐标。从而得直线
    */
    namedWindow(input_title, 0);
    namedWindow(output_title, 0);
    imshow(input_title, src);
    Canny(src, gray_src, 150, 200);

    cvtColor(gray_src, dst, CV_GRAY2BGR);
    namedWindow("edgr_image", 0);
    imshow("edgr_image", gray_src);

    vector<Vec4f> plines;
    HoughLinesP(gray_src, plines, 1, CV_PI /180.0, 10, 0, 10);
    Scalar color = Scalar(0, 0, 255);
    for (size_t i = 0; i < plines.size(); i++) {
        Vec4f hline = plines[i];
        line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 3, LINE_AA);
    }
    imshow(output_title, dst);

    waitKey(0);
    return 0;
}
