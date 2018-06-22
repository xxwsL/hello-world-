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
	cout << ">> ����任����\n";
	//�������Mat
	Mat src0 = imread("D:/work/train_set/opencv_test_set/2.jpg"), img0 = Mat::zeros(src0.size(),src0.type());
	//���������ε�������
	Point2f src_angle[3], img0_triangle[3];
	src_angle[0] = Point2f(0.0f, 0.0f);
	src_angle[1] = Point2f((float)(src0.cols - 1.0f), 0.0f);
	src_angle[2] = Point2f(0.0f, (float)(src0.rows - 1.0f));

	//�������
	Mat affine(2, 3, CV_32FC1);
	//������ת����
	Mat rot_mat(2, 3, CV_32FC1);

	img0_triangle[0] = Point2f((float)src0.cols * 0.0f, (float)src0.rows * 0.3f);
	img0_triangle[1] = Point2f((float)src0.cols * 0.6f, (float)src0.rows * 0.3f);
	img0_triangle[2] = Point2f((float)src0.cols * 0.1f, (float)src0.rows * 0.6f);

	affine = getAffineTransform(src_angle, img0_triangle);
	//��ʼ�任
	warpAffine(src0, img0, affine, img0.size());

	//��ת����
	Point center(img0.cols / 2, img0.rows / 2);
	//��ת�Ƕ�
	double angle = 35;
	//���ű���
	double scale = 1.5;
	rot_mat = getRotationMatrix2D(center, angle, scale);
	Mat img1 = Mat::zeros(img0.size(), img0.type());
	//��ʼ�任
	warpAffine(img0, img1, rot_mat, img1.size());

	//��ʾ����
	imshow("src0", src0);
	imshow("img0", img0);
	imshow("img1", img1);
	waitKey(0);
}
#endif // !_AFFINE_TEST_H_
