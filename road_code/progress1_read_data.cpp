#include<opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace cv;
int main(int argc, char** argv) {
    Mat src, dst;
    src = imread("road/straight.jpg");
    if (!src.data) {
        printf("could not load image...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    namedWindow("input",0);
    imshow("input", src);
    
    cvtColor(src, dst, CV_BGR2GRAY);    // 转为灰度图像
    printf("input image channels:%d\n", src.channels());
    printf("dst image channels:%d\n", dst.channels());
    printf("input image rows:%d\n", src.rows);
    printf("input image cols:%d\n", src.cols);

    // imwrite("image/car_gray.jpg", dst);

    // int b = src.at<Vec3b>(row, col)[0];
    // printf("input image cols:%d\n", src.at<Vec3b>(row, col)[0]);
    
    int height = dst.rows;
    int width = dst.cols;
    int nc = src.channels();    // 这里选择改图片
    uint32_t b_cnt = 0, g_cnt = 0, r_cnt = 0;
    uint32_t b_sum = 0, g_sum = 0, r_sum = 0;
    int b_ave = 0, g_ave = 0, r_ave = 0;
    for (int row = height/4*3; row < height; row++) {    // 图片颜色反转
        for (int col = 0; col < width/4*3; col++) {
            if (nc == 3) {
                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];
                b_sum+=b;
                g_sum+=g;
                r_sum+=r;
                b_cnt++;
                g_cnt++;
                r_cnt++;
                // if (b >= 160 && b <=190 )
                // {
                //     src.at<Vec3b>(row, col)[0] = 255;
                // }
                // else
                // {
                //     src.at<Vec3b>(row, col)[0] = 0;
                // }
                // if (g >= 160 && b <=190 )
                // {
                //     src.at<Vec3b>(row, col)[0] = 255;
                // }
                // else
                // {
                //     src.at<Vec3b>(row, col)[0] = 0;
                // }
                // if (b >= 160 && b <=210 )
                // {
                //     src.at<Vec3b>(row, col)[0] = 255;
                // }
                // else
                // {
                //     src.at<Vec3b>(row, col)[0] = 0;
                // }
            }
        }
    }

    b_ave = b_sum / b_cnt;
    g_ave = g_sum / g_cnt;
    r_ave = r_sum / r_cnt;

    printf("input image b_ave:%d\n", b_ave);
    printf("input image g_ave:%d\n", g_ave);
    printf("input image r_ave:%d\n", r_ave);

    // bitwise_not(src,dst);   // 直接图片反转
    namedWindow("output",0);
    imshow("output", src);

    waitKey(0);
    return 0;
}