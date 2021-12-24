#include<opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
    Mat src,dst;
    src = imread("image/girl.jpg");
    if (!src.data) {
        printf("could not load image src...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }

    namedWindow("input",0);
    imshow("input", src);
    int height = src.rows;
    int width = src.cols;
    dst = Mat::zeros(src.size(), src.type());
    float alpha = 1.5;
    float beta = 0;
    Mat m1;
    src.convertTo(m1, CV_32F);
    for (int row = 0; row < height; row++) {    // 图片颜色反转
        for (int col = 0; col < width; col++) {
            float b = src.at<Vec3b>(row, col)[0];
            float g = src.at<Vec3b>(row, col)[1];
            float r = src.at<Vec3b>(row, col)[2];
            dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b*alpha + beta);
            dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g*alpha + beta);
            dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r*alpha + beta);
        }
    }
    
    namedWindow("output",0);
    imshow("output", dst);

    waitKey(0);
    return 0;
}
