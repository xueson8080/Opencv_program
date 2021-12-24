#include<opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace cv;
int main(int argc, char** argv) {
    Mat src, dst;
    src = imread("image/girl.jpg");
    if (!src.data) {
        printf("could not load image...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    namedWindow("input",1);
    imshow("input", src);
    
    cvtColor(src, dst, CV_BGR2GRAY);    // 转为灰度图像
    printf("input image channels:%d\n", src.channels());
    printf("output image channels:%d\n", dst.channels());

    int height = dst.rows;
    int width = dst.cols;
    int nc = src.channels();    // 这里选择改图片
    for (int row = 0; row < height; row++) {    // 图片颜色反转
        for (int col = 0; col < width; col++) {
            if (nc == 1) {
                int gray = dst.at<uchar>(row, col);
                dst.at<uchar>(row, col) = 255-gray;
            }
            else if (nc == 3) {
                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];
                src.at<Vec3b>(row, col)[0] = 255 - b;
                src.at<Vec3b>(row, col)[1] = 255 - g;
                src.at<Vec3b>(row, col)[2] = 255 - r;
            }
        }
    }

    // bitwise_not(src,dst);   // 直接图片反转
    namedWindow("output",1);
    imshow("output", src);

    waitKey(0);
    return 0;
}
