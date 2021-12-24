#include<opencv2\opencv.hpp>
#include <iostream>
using namespace cv;
Mat src, dst;
int element_size = 3;
int max_size = 21;
void CallBack_Demo(int, void*);
int main(int argc, char** argv) {
    
    src = imread("image/girl2.jpg");
    if (!src.data) {
        printf("could not load image src...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    namedWindow("input",1);
    imshow("input", src);
    namedWindow("erode_output", 1);
    createTrackbar("Element Size :", "erode_output", &element_size, max_size, CallBack_Demo);
	CallBack_Demo(0, 0);

    waitKey(0);
    return 0;
}

void CallBack_Demo(int, void*) {
    int s = element_size *2 + 1;
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    dilate(src, dst, structureElement, Point(-1, -1), 1);   // 膨胀
    // erode(src, dst, structureElement);   // 腐蚀
    
    imshow("erode_output", dst);
}
