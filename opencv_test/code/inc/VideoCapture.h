#ifndef _VIDEOCAPTURE_H_
#define _VIDEOCAPTURE_H_
#include<opencv2/core/core.hpp>				//matͷ�ļ�
#include<opencv2/highgui/highgui.hpp>		//opencv highgui ģ��ͷ�ļ�	
#include<opencv2/imgproc/imgproc.hpp>		//opencv ͼ�����ļ�
#include <iostream>  

using namespace std;
using namespace cv;

void canny_use(Mat image);

void videocapture_test_fi()
{
	VideoCapture video;											//����һ����Ƶ����
	//video.open("E:\\ͼƬ�ֿ�\\����ĩ��\\MV\\mv1.mp4");		//����·������Ƶ
	video.open(0);												//����Ϊ0����������ͷ����
	Mat frame;													//����һ��֡
	
	while (1)
	{
		video >> frame;
		canny_use(frame);
		if (frame.empty())
		{
			break;
		}
		imshow("��Ƶ��ǰ֡", frame);
		waitKey(10);
	}

	waitKey(0);
}

#endif

