#include<opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
Mat bgImage;
void Myline();
void MyRectangle();
void MyEllipse();
void RandomLineDemo();
int main(int argc, char** argv) {
    bgImage = imread("image/han.jpg");
    if (!bgImage.data) {
        printf("could not load image src...\n");
        while(!(waitKey(500) == 27));
		return -1;
    }
    Myline();
    MyRectangle();
    MyEllipse();
    namedWindow("output",1);
    // putText(bgImage, "hello opencv", Point(300,300),CV_FONT_HERSHEY_COMPLEX, 1.0,Scalar(12,23,200),3,8);
    imshow("output", bgImage);

    RandomLineDemo();

    waitKey(0);
    return 0;
}

void Myline() {
    Point p1 = Point(20,30);
    Point p2;
    p2.x = 400;
    p2.y = 400;
    Scalar color = Scalar(0,0,255);
    line(bgImage, p1, p2, color, 2,LINE_8);
}

void MyRectangle() {
    Rect rect = Rect(100,100,200,200);
    Scalar color = Scalar(255,0,0);
    rectangle(bgImage,rect,color,1,LINE_8);
}

void MyEllipse() {
    Scalar color = Scalar(0,255,0);
    ellipse(bgImage, Point(bgImage.cols/2,bgImage.rows/2),Size(bgImage.cols/4,bgImage.rows/8), 90,0,360,color,2,LINE_8);
}
void RandomLineDemo() {
    RNG rng(12345);
    Point pt1;
    Point pt2;
    Mat bg = Mat::zeros(bgImage.size(), bgImage.type());
    namedWindow("random line demo", 1);
    for (int i = 0; i < 100000; i++) {
        pt1.x = rng.uniform(0,bgImage.cols);
        pt2.x = rng.uniform(0,bgImage.cols);
        pt1.y = rng.uniform(0,bgImage.rows);
        pt2.y = rng.uniform(0,bgImage.rows);
        Scalar color = Scalar(rng.uniform(0,255), rng.uniform(0,255),rng.uniform(0,255));
        if (waitKey(50) > 0) {
            break;
        }
        line(bg,pt1,pt2,color,1,LINE_AA);
        imshow("random line demo",bg);
    }
}
