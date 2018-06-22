#ifndef _VIDEOCAPTURE_H_
#define _VIDEOCAPTURE_H_
#include<opencv2/core/core.hpp>				//mat头文件
#include<opencv2/highgui/highgui.hpp>		//opencv highgui 模块头文件	
#include<opencv2/imgproc/imgproc.hpp>		//opencv 图像处理文件
#include <iostream>  

using namespace std;
using namespace cv;

void canny_use(Mat image);

void videocapture_test_fi()
{
	VideoCapture video;											//定义一个视频的类
	//video.open("E:\\图片仓库\\世界末日\\MV\\mv1.mp4");		//载入路径的视频
	video.open(0);												//参数为0，启用摄像头载入
	Mat frame;													//定义一个帧
	
	while (1)
	{
		video >> frame;
		canny_use(frame);
		if (frame.empty())
		{
			break;
		}
		imshow("视频当前帧", frame);
		waitKey(10);
	}

	waitKey(0);
}

#endif

