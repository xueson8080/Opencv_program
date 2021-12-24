#include <opencv2\opencv.hpp>
// #include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace cv;

int main(int argc, char** argv) {
    Mat src, dst, dst2;
    src = imread("image/girl.jpg");
    if (!src.data) {
        printf("could not load image src...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }

    char input_title[] = "input_image";
    char output_title[] = "output_image";
    char output_title2[] = "output_image2";
    namedWindow(input_title, 1);
    namedWindow(output_title, 1);
    // namedWindow(output_title2, 1);
    imshow(input_title, src);

    // 自定义线性滤波
    // // Robort x
    // Mat kernel_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);
    // filter2D(src, dst, -1, kernel_x, Point(-1,-1), 0.0);
    // // Robort y
    // Mat kernel_y = (Mat_<int>(2, 2) << 0, 1, -1, 0);
    // filter2D(src, dst2, -1, kernel_y, Point(-1,-1), 0.0);

    // // Sobel x
    // Mat kernel_x = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    // filter2D(src, dst, -1, kernel_x, Point(-1,-1), 0.0);
    // // Sobel y
    // Mat kernel_y = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    // filter2D(src, dst2, -1, kernel_y, Point(-1,-1), 0.0);

    // 拉普拉斯算子
    // Mat lapulace = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
    // filter2D(src, dst, -1, lapulace, Point(-1,-1), 0.0);

    int c = 0;
    int index = 0;
    int ksize = 0;
    while (true) {
        c = waitKey(500);
        if ((char)c == 27) { //ESC
            break;
        }
        ksize = 4 + (index % 8) *2 + 1;
        Mat kernel = Mat::ones(Size(ksize, ksize), CV_32F) / (float)(ksize * ksize);
        filter2D(src, dst, -1, kernel, Point(-1,-1));
        index++;
        imshow(output_title, dst);
    }

    imshow(output_title, dst);

    // imshow(output_title2, dst2);

    waitKey(0);
    return 0;
}
