#include<opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace cv;
int main(int argc, char** argv) {
    Mat src, dst;
    src = imread("road/stright6.jpg");
    if (!src.data) {
        printf("could not load image...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    namedWindow("input",0);
    imshow("input", src);
    
    cvtColor(src, dst, CV_BGR2GRAY);    // 转为灰度图像
    printf("input image channels:%d\n", src.channels());
    printf("output image channels:%d\n", dst.channels());
    printf("input image rows:%d\n", src.rows);
    printf("input image cols:%d\n", src.cols);

    int height = dst.rows;
    int width = dst.cols;
    int nc = src.channels();    // 这里选择改图片
    uint32_t b_cnt = 0, g_cnt = 0, r_cnt = 0;
    uint32_t b_sum = 0, g_sum = 0, r_sum = 0;
    uint32_t dot_cnt = 0;
    int b_ave = 0, g_ave = 0, r_ave = 0;
    for (int row = 0; row < height; row++) {    // 图片颜色反转
        for (int col = 0; col < width; col++) {
            if (nc == 3) {
                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];
                if (b >= 90 && b <=255 && g >=90 && g <= 255 && r > 90 && r <= 255 )
                {
                    src.at<Vec3b>(row, col)[0] = 255;
                    src.at<Vec3b>(row, col)[1] = 255;
                    src.at<Vec3b>(row, col)[2] = 255;
                    dot_cnt++;
                }
                else
                {
                    src.at<Vec3b>(row, col)[0] = 0;
                    src.at<Vec3b>(row, col)[1] = 0;
                    src.at<Vec3b>(row, col)[2] = 0;
                }
            }
        }
    }

    printf("input image dot_cnt:%d\n", dot_cnt);

  
    // bitwise_not(src,dst);   // 直接图片反转
    namedWindow("output",0);
    imshow("output", src);

    waitKey(0);
    return 0;
}