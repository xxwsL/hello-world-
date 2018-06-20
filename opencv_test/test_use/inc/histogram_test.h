#pragma once
#ifndef _HISTOGRAM_TEST_H_
#define _HISTOGRAM_TEST_H_
#include <iostream>
#include <highgui.hpp>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

void histogram_test_fi()
{
	cout << ">> 直方图测试\n";
	Mat src0 = imread("D:/work/train_set/opencv_test_set/2.jpg"); imshow("src0", src0);
	//cvtColor(src0, hist_img0, COLOR_BGR2HSV);

	MatND hist0;
	//通道数
	int channels[] = { 0 };
	//特征数，维度
	int dim = 1;
	//直方图各个维度尺寸
	int hist0_size[] = { 256 };
	//每一唯直方图的边界范围
	float ranges0[] = { 0.0f,255.0f };
	//必须为const类型
	const float *hist0_ranges[] = {ranges0};

	//开始计算直方图
	calcHist(&src0, 1, channels, Mat(), hist0, dim, hist0_size, hist0_ranges);

	//获取最大值和最小值
	double min_value, max_value;
	minMaxLoc(hist0, &min_value, &max_value);

	//开始绘制直方图
	int hpt = (int)(0.9 * hist0_size[0]);
	Mat hist_img0;
	hist_img0 = Mat::zeros(hist0_size[0], hist0_size[0], CV_8U);
	for (int i = 0; i < 256; ++i) {
		float binvalue = (float)hist0.at<float>(i);
		int realvalue = (int)(binvalue * hpt / max_value);
		rectangle(hist_img0, Point(i, hist0_size[0] - 1), Point(i, hist0_size[0] - realvalue), Scalar(255));
	}
	imshow("hsv_img0", hist_img0);
	waitKey(0);

}
#endif