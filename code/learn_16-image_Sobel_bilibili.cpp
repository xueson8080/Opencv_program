#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
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
    char output_title[] = "gray_image";
    char output_title2[] = "output_image2";
    char output_title3[] = "output_image3";
    char output_title4[] = "final_result";
    namedWindow(input_title, 1);
    namedWindow(output_title, 1);
    namedWindow(output_title2, 1);
    imshow(input_title, src);

    Mat gray_src;
    GaussianBlur(src, dst, Size(3, 3), 0, 0);
    cvtColor(dst, gray_src, CV_BGR2GRAY);
    imshow(output_title, gray_src);

    Mat xgrad, ygrad;
// Laplance算子
// 高斯模糊 – 去噪声GaussianBlur()
// 转换为灰度图像cvtColor()
// 拉普拉斯 – 二阶导数计算Laplacian()
// 取绝对值convertScaleAbs()
// 显示结果
    Scharr(gray_src, xgrad, CV_16S, 1, 0);
    Scharr(gray_src, ygrad, CV_16S, 0, 1);
    // Sobel(gray_src, xgrad, CV_16S, 1, 0, 3);
    // Sobel(gray_src, ygrad, CV_16S, 0, 1, 3);
    convertScaleAbs(xgrad, xgrad);
    convertScaleAbs(ygrad, ygrad);
    imshow(output_title2, xgrad);
    imshow(output_title3, ygrad);

    Mat xygrad = Mat(xgrad.size(), xgrad.type());
    printf("type:%d\n", xgrad.type());
    int width = xgrad.cols;
    int height = ygrad.rows;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int xg = xgrad.at<uchar>(row, col);
            int yg = ygrad.at<uchar>(row, col);
            int xy = xg + yg;
            xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);
        }
    }
    // addWeighted(xgrad, 0.5, ygrad, 0.5, 0, xygrad);
    imshow(output_title4, xygrad);

    // imshow(output_title, dst);

    waitKey(0);
    return 0;
}
