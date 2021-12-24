#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv) {
    Mat src, dst, gray_src, dst2;
    src = imread("image/girl.jpg");
    if (!src.data) {
        printf("could not load image src...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    char input_title[] = "input_image";
    char output_title[] = "hough-line-detection";
    imshow(input_title, src);
    /*
    因为霍夫圆检测对噪声比较敏感，所以首先要对图像做中值滤波。
    基于效率考虑，Opencv中实现的霍夫变换圆检测是基于图像梯度的实现，分为两步：
	1. 检测边缘，发现可能的圆心
	2. 基于第一步的基础上从候选圆心开始计算最佳半径大小
    HoughCircles(
        InputArray image, // 输入图像 ,必须是8位的单通道灰度图像
        OutputArray circles, // 输出结果，发现的圆信息
        Int method, // 方法 - HOUGH_GRADIENT
        Double dp, // dp = 1; 
        Double mindist, // 10 最短距离-可以分辨是两个圆的，否则认为是同心圆- src_gray.rows/8
        Double param1, // canny edge detection low threshold
        Double param2, // 中心点累加器阈值 – 候选圆心
        Int minradius, // 最小半径
        Int maxradius//最大半径 
    )

    */
    // 中值滤波
    Mat moutput;
    medianBlur(src, moutput, 3);
    cvtColor(moutput, moutput, CV_BGR2GRAY);
    
    // 霍夫圆检测
    vector<Vec3f> pcircles;
    HoughCircles(moutput, pcircles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 5, 50);
    src.copyTo(dst);
    for (size_t i = 0; i < pcircles.size(); i++) {
        Vec3f cc = pcircles[i];
        circle(dst, Point(cc[0], cc[1]), cc[2], Scalar(0, 0, 255),2, LINE_AA);
        circle(dst, Point(cc[0], cc[1]), 2, Scalar(198, 23, 155), 2, LINE_AA);
    }
    imshow(output_title, dst);



    imshow(output_title, dst);

    waitKey(0);
    return 0;
}
