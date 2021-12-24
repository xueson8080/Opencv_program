#include<opencv2\opencv.hpp>
#include <opencv2\imgproc\types_c.h>
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
    namedWindow("input",1);
    imshow("input", src);
    
    /*
    Mat dst;    做一张图片
    dst = Mat(src.size(), src.type());
    dst = Scalar(127, 0, 255);  // BGR
    */
    /*
    Mat A = imread(imgFilePath);
    Mat B(A);   // 只复制指针，B跟随A变而变
    */
    // Mat dst = src.clone();  // 克隆图片
    // Mat dst;
    src.copyTo(dst);    // 复制图片

    // imwrite("image/girl_gray.jpg", gray_src);
   
    namedWindow("window_2",1);
    imshow("window_2", dst);

    waitKey(0);
    return 0;
}
