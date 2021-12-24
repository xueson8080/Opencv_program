#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>

using namespace std;
using namespace cv;
 
int main()
{
	cv::Mat src = cv::imread("C:\\Users\\dell\\Desktop\\xin1.jpg", 1);
	if (src.empty() || src.channels() != 3)
	{
		cout << "Source image load error!" << endl;
		while(!(waitKey(500) == 27));
		return -1;
	}
 
	//采用CV_BGR2GRAY,转换公式Gray = 0.1140*B + 0.5870*G + 0.2989*R
	cv::Mat bgr2grayImg;	
	cvtColor(src, bgr2grayImg, CV_BGR2GRAY);	
 
	//采用CV_RGB2GRAY,转换公式Gray = 0.1140*R + 0.5870*G + 0.2989*B
	cv::Mat rgb2grayImg;
	cvtColor(src, rgb2grayImg, CV_RGB2GRAY);	
 
	//采用CV_GRAY2BGR,转换公式B = G = R = Gray
	cv::Mat gray2bgrImg;
	cvtColor(bgr2grayImg, gray2bgrImg, CV_GRAY2BGR);	
 
	//采用CV_GRAY2RGB,转换公式R = G = B = Gray
	cv::Mat gray2rgbImg;
	cvtColor(rgb2grayImg, gray2rgbImg, CV_GRAY2RGB);	
	
	waitKey(0);
	return 0;
}