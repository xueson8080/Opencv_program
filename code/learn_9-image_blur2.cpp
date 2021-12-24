#include<opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
int main(int argc, char** argv) {
    Mat src, dst1, dst2, dst3;
    src = imread("image/girl2.jpg");
    if (!src.data) {
        printf("could not load image src...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }

    namedWindow("input",1);
    imshow("input", src);

    medianBlur(src, dst1, 3);   // 中值模糊
    namedWindow("medianBlur", 1);
    imshow("medianBlur", dst1);
    bilateralFilter(src, dst2, 15,100,5);   // 双边模糊
    namedWindow("bilateralFilter", 1);
    imshow("bilateralFilter", dst2);

    Mat kernel = (Mat_<char>(3,3) << 0,-1,0, -1,5,-1, 0,-1,0);
    filter2D(dst1, dst3, -1, kernel, Point(-1, -1), 0); // 眼膜
    namedWindow("Final_Result", 1);
    imshow("Final_Result", dst3);

    // GaussianBlur(src, gaublue_ima, Size(11, 11), 0, 0);
    // imshow("gaublue_ima",gaublue_ima);



    waitKey(0);
    return 0;
}
