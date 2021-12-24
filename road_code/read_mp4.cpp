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
    // ��ȡ��Ƶ֡��
    double rate = capture.get(5);
    cout << "֡��Ϊ��"<<""<<rate<<endl;
    int total_rate = capture.get(7);
    printf("��֡����%d\n",total_rate);
    Mat frame;
    Mat element=getStructuringElement(MORPH_RECT,Size(3,3));
    
    namedWindow("Movie Player",0);

    while(1) {
        if (!capture.read(frame)) {
            break;
        }
        cvtColor(frame,frame,CV_BGR2GRAY);               //��ɫ�ռ�ת��
        medianBlur(frame, frame,3);                      //��ֵ�˲�
        // hreshold(frame, frame, 55, 220, 0);             //��ֵ������ʾ����55������ֵ������Ϊ220
        threshold(frame, frame, 0, 255, THRESH_OTSU);  // �Զ���ֵ
        morphologyEx(frame, frame, MORPH_OPEN, element); //������
        imshow("Movie Player", frame); 

        char c = waitKey(33);
            if (c == 27)           //27Ϊ"Esc"��ASCII��ֵ����ʾ����"Esc"ʱ�˳���Ƶ����
            break;
    }
	waitKey(0);
	return 0;
}
