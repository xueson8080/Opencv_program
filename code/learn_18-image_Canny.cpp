#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace cv;
int t1_value = 50;
int max_value = 255;
Mat src, dst, gray_src, dst2;
void Canny_Demo(int, void*);
int main(int argc, char** argv) {
    
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
    // namedWindow(output_title2, 1);
    imshow(input_title, src);
    /*
    Canny是边缘检测算法，在1986年提出的。
    是一个很好的边缘检测器
    很常用也很实用的图像处理方法
    高斯模糊 - GaussianBlur
    灰度转换 - cvtColor
    计算梯度 – Sobel/Scharr
    非最大信号抑制
    高低阈值输出二值图像
    Canny算法介绍 - 非最大信号抑制
    Canny算法介绍-高低阈值输出二值图像：T1， T2为阈值，凡是高于T2的都保留，凡是小
    于T1都丢弃，从高于T2的像素出发，凡是大于T1而且相互连接的，都保留。最终得到一个
    输出二值图像。推荐的高低阈值比值为 T2: T1 = 3:1/2:1其中T2为高阈值，T1为低阈值
    */

   cvtColor(src,gray_src, CV_BGR2GRAY);
   createTrackbar("threshold Value", output_title, &t1_value, max_value, Canny_Demo);
   Canny_Demo(0, 0);
    
    waitKey(0);
    return 0;
}

void Canny_Demo(int, void*) {
    Mat edge_output;
    blur(gray_src, gray_src, Size(3,3), Point(-1, -1), BORDER_DEFAULT);
    Canny(gray_src, edge_output, t1_value, t1_value * 2, 3, false);
    imshow("gray_image", ~edge_output);
}
