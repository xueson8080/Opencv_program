#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;
Mat src, dst ;
void update_map(void);
int main(int argc, char** argv) {
    
    src = imread("image/girl.jpg");
    if (!src.data) {
        printf("could not load image src...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    char input_title[] = "input_image";
    char output_title[] = "output-image1";
    char output_title2[] = "output-image2";
    namedWindow(input_title, 1);
    namedWindow(output_title, 1);
    namedWindow(output_title2, 1);
    imshow(input_title, src);
    
    // 分通道显示
    vector<Mat> bgr_planes;
    split(src, bgr_planes);
    // imshow(output_title2, bgr_planes[2]);

    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = { range };
    Mat b_hist, g_hist, r_hist;
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, true, false);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, true, false);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, true, false);
    // 归一化
    int hist_h = 400;
    int hist_w = 512;
    int bin_w = hist_w / histSize;
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());

    // render histogram chart
    for (int i = 1; i < histSize; i++) {
        line(histImage, Point((i-1) * bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))),\
        Point((i) * bin_w, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, LINE_AA);

        line(histImage, Point((i-1) * bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))),\
        Point((i) * bin_w, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, LINE_AA);

        line(histImage, Point((i-1) * bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))),\
        Point((i) * bin_w, hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, LINE_AA);
    }



    imshow(output_title, histImage);
    
    waitKey(0);
    return 0;
}
