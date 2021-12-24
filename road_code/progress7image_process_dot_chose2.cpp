#include<opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace cv;
int main(int argc, char** argv) {
    Mat src, hsv, hue, meblur_ima, gray_src_ima, gray_src, dot_image,\
    backPrjImage, mop_ima, not_ima, process_image;
    src = imread("road/straight2.jpg");
    if (!src.data) {
        printf("could not load image...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    namedWindow("input",0);
    imshow("input", src);
    
    medianBlur(src, dot_image, 25);
    namedWindow("meblur_ima", 0);
    imshow("meblur_ima",dot_image);

    cvtColor(dot_image, gray_src, CV_BGR2GRAY);    // 转为灰度图像
    threshold(gray_src, backPrjImage, 0, 255, THRESH_OTSU);  // 自动阈值
    namedWindow("backPrjImage", 0);
    imshow("backPrjImage",backPrjImage);
    // printf("input image channels:%d\n", src.channels());
    // printf("output image channels:%d\n", gray_src.channels());
    // printf("input image rows:%d\n", src.rows);
    // printf("input image cols:%d\n", src.cols);

    int height = dot_image.rows;
    int width = dot_image.cols;
    int nc = dot_image.channels();    // 这里选择改图片
    uint32_t b_cnt = 0, g_cnt = 0, r_cnt = 0;
    uint32_t b_sum = 0, g_sum = 0, r_sum = 0;
    uint32_t dot_cnt = 0;
    int b_ave = 0, g_ave = 0, r_ave = 0;
    for (int row = 0; row < height; row++) {    // 图片颜色反转
        for (int col = 0; col < width; col++) {
            if (nc == 3) {
                int b = dot_image.at<Vec3b>(row, col)[0];
                int g = dot_image.at<Vec3b>(row, col)[1];
                int r = dot_image.at<Vec3b>(row, col)[2];
                if (b >= 90 && b <=200 && g >=90 && g <= 200 && r > 90 && r <= 200 )
                {
                    dot_image.at<Vec3b>(row, col)[0] = 255;
                    dot_image.at<Vec3b>(row, col)[1] = 255;
                    dot_image.at<Vec3b>(row, col)[2] = 255;
                    dot_cnt++;
                }
                else
                {
                    dot_image.at<Vec3b>(row, col)[0] = 0;
                    dot_image.at<Vec3b>(row, col)[1] = 0;
                    dot_image.at<Vec3b>(row, col)[2] = 0;
                }
            }
        }
    }

    namedWindow("dot_image",0);
    imshow("dot_image", dot_image);

    // /*
    // CV_MOP_OPEN/ CV_MOP_CLOSE/ CV_MOP_GRADIENT / 
    // CV_MOP_TOPHAT/ CV_MOP_BLACKHAT 形态学操作类型
    // */
    Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7), Point(-1,-1));
    morphologyEx(dot_image, process_image, 1, kernel);

    printf("input image dot_cnt:%d\n", dot_cnt);

  
    // bitwise_not(src,gray_src);   // 直接图片反转
    namedWindow("process_image",0);
    imshow("process_image", process_image);

    waitKey(0);
    return 0;
}