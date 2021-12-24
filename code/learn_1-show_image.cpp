#include<opencv2\opencv.hpp>
#include <iostream>
using namespace cv;
int main(int argc, char** argv) {
    Mat src = imread("image/girl.jpg"); //图片路径为同一文件夹
    namedWindow("window_1",0);
    imshow("window_1", src);
    waitKey(0);
    return 0;
}
