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
    imshow(input_title, src);

    cvtColor(src, src,CV_BGR2GRAY);
    imshow(output_title, src);
    equalizeHist(src,dst);
    
    imshow(output_title2, dst);
    
    waitKey(0);
    return 0;
}
