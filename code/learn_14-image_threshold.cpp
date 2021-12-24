#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace cv;
Mat src, gray_src, dst;
int threshold_value = 123;
int threshold_max = 255;
int type_value = 0;
int type_max = 5;
void Threshold_Demo(int, void*);
int main(int argc, char** argv) {
    src = imread("image/girl.jpg");
    if (!src.data) {
        printf("could not load image src...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    namedWindow("input",1);
    imshow("input", src);

    namedWindow("binary_image",1);
    createTrackbar("threshold_Value", "binary_image", &threshold_value, threshold_max, Threshold_Demo);
    createTrackbar("Type Value:", "binary_image", &type_value, type_max, Threshold_Demo);
    Threshold_Demo(0, 0);

    waitKey(0);
    return 0;
}
void Threshold_Demo(int, void*) {
    cvtColor(src, gray_src, CV_BGR2GRAY);
    threshold(gray_src, dst, threshold_value, threshold_max, type_value);
    // threshold(gray_src, dst, 0, 255, THRESH_OTSU);  // 自动阈值
    imshow("binary_image", dst);
    // imwrite("image/girl222.jpg", dst);
}
