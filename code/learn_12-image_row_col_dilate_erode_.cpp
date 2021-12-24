#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace cv;
void CallBack_Demo(int, void*);
int main(int argc, char** argv) {
    Mat src, dst;
    src = imread("image/girl.jpg");
    if (!src.data) {
        printf("could not load image src...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    namedWindow("input",1);
    imshow("input", src);

    Mat gray_src;
    cvtColor(src, gray_src, CV_BGR2GRAY);
    // imwrite("image/girl_gray.jpg", gray_src);
    imshow("gray_src", gray_src);
    Mat binImg;
    adaptiveThreshold(~gray_src, binImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15,-2);

    // 水平结构元素
    Mat hline = getStructuringElement(MORPH_RECT, Size(src.cols/16, 1), Point(-1,-1));
    // 垂直结构元素
    Mat vline = getStructuringElement(MORPH_RECT, Size(1, src.cols/16), Point(-1,-1));

    Mat temp;
    // erode(binImg, temp, vline);
    // dilate(temp, dst, vline);

    erode(binImg, temp, hline);
    dilate(temp, dst, hline);


    imshow("output",dst);
    
    waitKey(0);
    return 0;
}
