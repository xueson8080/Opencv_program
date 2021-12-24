#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    VideoCapture capture("road/video.mp4");
    // if (!capture.isOpened())
     if (!capture.isOpened()) {
        cout << "Movie open error" << endl;
        waitKey(0);
        return -1;
    }
    // 获取视频帧率
    double rate = capture.get(5);
    cout << "帧率为："<<""<<rate<<endl;
    int total_rate = capture.get(7);
    printf("总帧数：%d\n",total_rate);
    Mat frame;
    Mat element=getStructuringElement(MORPH_RECT,Size(3,3));
    
    namedWindow("Movie Player",0);

    while(1) {
        if (!capture.read(frame)) {
            break;
        }
        cvtColor(frame,frame,CV_BGR2GRAY);               //颜色空间转换
        medianBlur(frame, frame,3);                      //中值滤波
        // hreshold(frame, frame, 55, 220, 0);             //二值化，显示大于55的像素值，其余为220
        threshold(frame, frame, 0, 255, THRESH_OTSU);  // 自动阈值
        morphologyEx(frame, frame, MORPH_OPEN, element); //开运算
        imshow("Movie Player", frame); 

        char c = waitKey(33);
            if (c == 27)           //27为"Esc"的ASCII码值，表示按下"Esc"时退出视频播放
            break;
    }
	waitKey(0);
	return 0;
}
