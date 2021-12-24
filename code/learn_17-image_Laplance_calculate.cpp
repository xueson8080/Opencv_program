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

    // 高斯模糊 – 去噪声GaussianBlur()
    // 转换为灰度图像cvtColor()
    // 拉普拉斯 – 二阶导数计算Laplacian()
    // 取绝对值convertScaleAbs()
    // 显示结果

    Mat gray_src, edge_image;
    GaussianBlur(src, dst, Size(3, 3), 0, 0);
    cvtColor(dst, gray_src, CV_BGR2GRAY);

    Laplacian(gray_src, edge_image, CV_16S, 3);
    convertScaleAbs(edge_image, edge_image);

    threshold(edge_image, edge_image, 0, 255, THRESH_OTSU| THRESH_BINARY);
    imshow(output_title, edge_image);

    waitKey(0);
    return 0;
}
