// #include "stdafx.h"
#include<opencv2\opencv.hpp>
 
using namespace cv;
int main()
{
	cv::Mat src, dst;
	src = cv::imread("image/girl.jpg");
	dst = src.clone();
	// 遍历像素
	// for (int col = 0; col < dst.cols; col++)
	// {
	// 	for (int row = 0; row < dst.rows; row++)
	// 	{
	// 		Vec3b bgr = src.at<Vec3b>(row, col);
	// 		bgr[0] = 255 - bgr[0];
	// 		bgr[1] = 255 - bgr[1];
	// 		bgr[2] = 255 - bgr[2];
	// 		dst.at<Vec3b>(row, col) = bgr;
	// 	}
	// }
 
	imshow("src",src);
	imshow("-src", dst);
	cv::waitKey();
    return 0;
 
}
 