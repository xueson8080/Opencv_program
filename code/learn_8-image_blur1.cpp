#include<opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
int main(int argc, char** argv) {
    Mat src, dst;
    src = imread("image/call2.jpg");
    if (!src.data) {
        printf("could not load image src...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    namedWindow("input",1);
    imshow("input", src);

    blur(src, dst, Size(11,11),Point(-1,-1));   //Size里面的是XY方向的模糊
    imshow("output_blur",dst);

    Mat gbur;
    GaussianBlur(src, gbur,Size(5, 5), 11,11);
    imshow("GaussiaBlue", gbur);

    waitKey(0);
    return 0;
}
