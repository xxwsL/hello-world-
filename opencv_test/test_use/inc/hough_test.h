#pragma once
#ifndef _HOUGHT_TEST_H_
#define _HOUGHT_TEST_H_

#include <opencv.hpp>
#include <iostream>
#include <imgproc.hpp>
#include <core.hpp>
#include <highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;

void hought_test_fi(void)
{
	cout << ">> ªÙ∑Ú±‰ªª≤‚ ‘\n";
	Mat src0 = imread("D:/work/train_set/opencv_test_set/2.jpg");

	Mat img0, img1;
	Canny(src0, img0, 50, 200);

	vector<Vec4i> lines;
	HoughLinesP(img0, lines, 1, CV_PI / 180, 100, 0, 0);
	img1 = img0.clone().setTo(Scalar(0, 0, 0));
	for (uint i = 0; i < lines.size(); ++i) {
		line(img1, Point(lines[i][0], lines[i][1]),Point(lines[i][2],lines[i][3]), Scalar(255,255,255));
	}

	imshow("img0", img0);
	imshow("img1", img1);
	waitKey(0);
}
#endif // !_HOUGHT_TEST_H_

