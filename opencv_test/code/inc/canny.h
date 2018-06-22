#ifndef _CANNY_H_
#define _CANNY_H_

#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>		//opencv highgui 模块头文件	
#include<opencv2/imgproc/imgproc.hpp>		//opencv 图像处理文件
#include <cv.h>  
#include <highgui.h>  
#include <iostream>  

using namespace std;
using namespace cv;


//int main()
void canny_use(void)
{
	Mat image = imread("E:\\图片仓库\\世界末日\\opencv_test0\\4.jpg");  //存放自己图像的路径 
	namedWindow("原图");
	imshow("原图", image);												//原图显示


	Mat dstimage;
	cvtColor(image, dstimage, COLOR_BGR2GRAY);
	imshow("灰度图", dstimage);

	Mat edge;
	blur(dstimage, edge, Size(3, 3));								//进行均值滤波处理,降低 噪声

	Canny(edge,edge,3,9,3);

	imshow("效果图（模糊图）", edge);

	waitKey(0);
}

#endif