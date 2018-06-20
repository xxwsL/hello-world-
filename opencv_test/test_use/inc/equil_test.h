#pragma once
#ifndef _EQUIL_TEST_H_
#define _EQUIL_TEST_H_

#include <iostream>
#include <highgui.hpp>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

void equil_test_fi()
{
	cout << ">> 直方图均衡化测试\n";
	//输入输出Mat
	Mat src0 = imread("D:/work/train_set/opencv_test_set/2.jpg"), img0 = Mat::zeros(src0.size(), src0.type());
	cvtColor(src0, src0, COLOR_BGR2GRAY);
	//开始均衡化
	equalizeHist(src0, img0);

	imshow("src0", src0);
	imshow("img0", img0);
	waitKey(0);
}
#endif // !_EQUIL_TEST_H_
