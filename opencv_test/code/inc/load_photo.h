#ifndef _LOAD_PHOTO_H_
#define _LOAD_PHOTO_H_
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void load_photo_test_fi(void)
{
	Mat image = imread("E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test0\\9.jpg");  //����Լ�ͼ���·�� 
	namedWindow("test");
	imshow("��ʾͼ��", image);
	Mat I;
	FileStorage fs("test.xml", FileStorage::READ);
	read(fs["E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test0\\9.jpg"], I);
	fs.release();
	waitKey(0);
}

#endif
