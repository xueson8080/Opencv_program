#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace std;
using namespace cv;

Mat src, temp, dst;
int match_method = TM_SQDIFF;
int max_track = 5;
const char* INPUT_T = "input image";
const char* OUTPUT_T = "result image";
const char* match_t = "template match-demo";
void Match_Demo(int, void*);
int main(int argc, char** argv) {
	// 待检测图像
	src = imread("image/girl.jpg");
	// 模板图像
	temp = imread("image/girl_head.jpg");
	if (src.empty() || temp.empty()) {
		printf("could not load image...\n");
		while(!(waitKey(500) == 27));
		return -1;
	}
	namedWindow(INPUT_T, 1);
	namedWindow(OUTPUT_T, 0);
	namedWindow(match_t, 1);
	imshow(INPUT_T, temp);
	const char* trackbar_title = "Match Algo Type:";
	createTrackbar(trackbar_title, OUTPUT_T, &match_method, max_track, Match_Demo);
	Match_Demo(0, 0);

	waitKey(0);
	return 0;
}

void Match_Demo(int, void*) {
	int width = src.cols - temp.cols + 1;
	int height = src.rows - temp.rows + 1;
	Mat result(width, height, CV_32FC1);

	matchTemplate(src, temp, result, match_method, Mat());
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	Point minLoc;
	Point maxLoc;
	double min, max;
	src.copyTo(dst);
	Point temLoc;
	minMaxLoc(result, &min, &max, &minLoc, &maxLoc, Mat());
	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) {
		temLoc = minLoc;
	} else {
		temLoc = maxLoc;
	}

	// 绘制矩形
	rectangle(dst, Rect(temLoc.x, temLoc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2, 8);
	rectangle(result, Rect(temLoc.x, temLoc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2, 8);
	
	imshow(OUTPUT_T, result);
	imshow(match_t, dst);
}
