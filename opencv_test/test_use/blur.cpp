#include <opencv.hpp>
#include <cv.h>  
#include <iostream>  

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("E:\\图片仓库\\世界末日\\opencv_test0\\0.jpg");  //存放自己图像的路径 
	namedWindow("原图");
	imshow("原图", image);												//原图显示


	Mat dstimage; 
	blur(image, dstimage,Size(15,15));									//进行均值滤波处理

	imshow("效果图（模糊图）", dstimage);

	waitKey(0);
	return 0;
}