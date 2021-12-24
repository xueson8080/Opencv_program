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

    pyrUp(src, dst, Size(src.cols*2, src.rows*2));
    imshow("out_up", dst);

    Mat s_down;
    pyrDown(src, s_down, Size(src.cols / 2, src.rows/2));
    imshow("out_down", s_down);

    /*
    高斯不同(Difference of Gaussian-DOG)
    定义：就是把同一张图像在不同的参数下做高斯模糊之后的结果相减，得到的输出图像。称为高斯不同(DOG)
    高斯不同是图像的内在特征，在灰度图像增强、角点检测中经常用到。
    */
    Mat gray_src, g1, g2, dogImg;
    cvtColor(src, gray_src, CV_BGR2GRAY);
    GaussianBlur(gray_src, g1, Size(5, 5), 0, 0);
    GaussianBlur(g1, g2, Size(5,5), 0, 0);
    subtract(g1, g2, dogImg, Mat());
    // 归一化显示
    normalize(dogImg, dogImg, 255, 0, NORM_MINMAX);
    imshow("output",dogImg);
    
    
    waitKey(0);
    return 0;
}
