#ifndef _BIUR_H_
#define _BIUR_H_

#include <opencv.hpp>
#include <cv.h>  
#include <iostream>  

using namespace std;
using namespace cv;

void blur_test_fi(void)
{
	Mat image = imread("E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test0\\0.jpg");  //����Լ�ͼ���·�� 
	namedWindow("ԭͼ");
	imshow("ԭͼ", image);												//ԭͼ��ʾ


	Mat dstimage; 
	blur(image, dstimage,Size(15,15));									//���о�ֵ�˲�����

	imshow("Ч��ͼ��ģ��ͼ��", dstimage);

	waitKey(0);
}

#endif // !_BIUR_H_
