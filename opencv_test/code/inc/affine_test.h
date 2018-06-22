#pragma once
#ifndef _AFFINE_TEST_H_
#define _AFFINE_TEST_H_

#include<iostream>

#include <opencv.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

void affine_test_fi(void)
{
	cout << ">> 仿射变换测试\n";
	//输入输出Mat
	Mat src0 = imread("D:/work/train_set/opencv_test_set/2.jpg"), img0 = Mat::zeros(src0.size(),src0.type());
	//仿射三角形的三个点
	Point2f src_angle[3], img0_triangle[3];
	src_angle[0] = Point2f(0.0f, 0.0f);
	src_angle[1] = Point2f((float)(src0.cols - 1.0f), 0.0f);
	src_angle[2] = Point2f(0.0f, (float)(src0.rows - 1.0f));

	//仿射矩阵
	Mat affine(2, 3, CV_32FC1);
	//缩放旋转矩阵
	Mat rot_mat(2, 3, CV_32FC1);

	img0_triangle[0] = Point2f((float)src0.cols * 0.0f, (float)src0.rows * 0.3f);
	img0_triangle[1] = Point2f((float)src0.cols * 0.6f, (float)src0.rows * 0.3f);
	img0_triangle[2] = Point2f((float)src0.cols * 0.1f, (float)src0.rows * 0.6f);

	affine = getAffineTransform(src_angle, img0_triangle);
	//开始变换
	warpAffine(src0, img0, affine, img0.size());

	//旋转中心
	Point center(img0.cols / 2, img0.rows / 2);
	//旋转角度
	double angle = 35;
	//缩放比例
	double scale = 1.5;
	rot_mat = getRotationMatrix2D(center, angle, scale);
	Mat img1 = Mat::zeros(img0.size(), img0.type());
	//开始变换
	warpAffine(img0, img1, rot_mat, img1.size());

	//显示测试
	imshow("src0", src0);
	imshow("img0", img0);
	imshow("img1", img1);
	waitKey(0);
}
#endif // !_AFFINE_TEST_H_
