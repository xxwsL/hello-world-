#ifndef _LOAD_PHOTO_H_
#define _LOAD_PHOTO_H_
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void load_photo_test_fi(void)
{
	Mat image = imread("E:\\图片仓库\\世界末日\\opencv_test0\\9.jpg");  //存放自己图像的路径 
	namedWindow("test");
	imshow("显示图像", image);
	Mat I;
	FileStorage fs("test.xml", FileStorage::READ);
	read(fs["E:\\图片仓库\\世界末日\\opencv_test0\\9.jpg"], I);
	fs.release();
	waitKey(0);
}

#endif
