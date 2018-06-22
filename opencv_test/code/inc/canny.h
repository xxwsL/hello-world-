#ifndef _CANNY_H_
#define _CANNY_H_

#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>		//opencv highgui ģ��ͷ�ļ�	
#include<opencv2/imgproc/imgproc.hpp>		//opencv ͼ�����ļ�
#include <cv.h>  
#include <highgui.h>  
#include <iostream>  

using namespace std;
using namespace cv;


//int main()
void canny_use(void)
{
	Mat image = imread("E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test0\\4.jpg");  //����Լ�ͼ���·�� 
	namedWindow("ԭͼ");
	imshow("ԭͼ", image);												//ԭͼ��ʾ


	Mat dstimage;
	cvtColor(image, dstimage, COLOR_BGR2GRAY);
	imshow("�Ҷ�ͼ", dstimage);

	Mat edge;
	blur(dstimage, edge, Size(3, 3));								//���о�ֵ�˲�����,���� ����

	Canny(edge,edge,3,9,3);

	imshow("Ч��ͼ��ģ��ͼ��", edge);

	waitKey(0);
}

#endif