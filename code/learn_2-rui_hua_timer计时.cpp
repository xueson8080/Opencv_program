#include<opencv2\opencv.hpp>
#include <iostream>
#include <math.h>
using namespace cv;
int main(int argc, char** argv) {
    Mat src, dst;
    src = imread("image/girl.jpg");
    if (!src.data) {
        printf("could not load image...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    namedWindow("window_1",1);
    imshow("window_1", src);
    /*
    int cols = (src.cols-1) * src.channels();
    int offsetx = src.channels();
    int rows = src.rows;
    dst = Mat::zeros(src.size(), src.type());
    for (int row = 1; row < (rows-1); row++) {
        const uchar* previous = src.ptr<uchar>(row - 1);
        const uchar* current = src.ptr<uchar>(row);
        const uchar* next = src.ptr<uchar>(row + 1);
        uchar* output = dst.ptr<uchar>(row);
        for (int col = offsetx; col<cols; col++) {
            output[col] = saturate_cast<uchar>(5 * current[col]\
             - (current[col - offsetx] + current[col + offsetx] \
             + previous[col] + next[col]));
        }
    }
    */
   double t = getTickCount();
   Mat kernel = (Mat_<char>(3,3) << 0,-1,0, -1,5,-1, 0,-1,0);
   filter2D(src, dst, src.depth(), kernel);
   double timeconsum = (getTickCount() - t) / getTickFrequency();
   printf("tim consum %.2f\n", timeconsum);
   
    namedWindow("window_2",1);
    imshow("window_2", dst);

    waitKey(0);
    return 0;
}
