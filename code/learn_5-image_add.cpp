#include<opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
    Mat src1, src2, dst;
    src1 = imread("image/longmao.jpg");
    src2 = imread("image/plane.jpg");
    if (!src1.data) {
        printf("could not load image src1...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    if (!src2.data) {
        printf("could not load image src2...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    namedWindow("input1",0);
    imshow("input1", src1);
    namedWindow("input2",0);
    imshow("input2", src2);

    double alpha = 0.5;
    if (src1.rows == src2.rows && src1.cols == src2.cols && src1.type() == src2.type()){
        addWeighted(src1, alpha, src2, (1.0-alpha), 0.0, dst);
    }
    
    namedWindow("output",0);
    imshow("output", dst);

    waitKey(0);
    return 0;
}
