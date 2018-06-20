#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>		//opencv highgui 模块头文件	
#include<opencv2/imgproc/imgproc.hpp>		//opencv 图像处理文件
#include <cv.h>  
#include <highgui.h>  
#include <iostream>  

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("E:\\图片仓库\\世界末日\\opencv_test0\\0.jpg");  //存放自己图像的路径 
	namedWindow("原图");
	imshow("原图", image);
	
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));//取图变长为15的方行像素点作为一个集合
	Mat dstlmage;
	erode(image, dstlmage, element);							//以getStructuringElement取的像素集合进行模糊
	imshow("效果图（腐蚀图）",dstlmage);

	waitKey(0);
	return 0;
}