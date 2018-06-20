#pragma once
#ifndef _HARRIS_TEST_H_
#define _HARRIS_TEST_H_
#include <iostream>
#include <highgui.hpp>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

void harris_test_fi()
{
	cout << ">> Ω«µ„ºÏ≤‚≤‚ ‘\n";
	Mat src0 = imread("D:/work/train_set/opencv_test_set/2.jpg", 0); imshow("src0", src0);

	Mat img0;
	cornerHarris(src0, img0, 2, 3, 0.01);

	Mat img1;
	threshold(img0, img1, 0.00001, 255, THRESH_BINARY);
	imshow("img1", img1);
	waitKey(0);
}

#endif // !_HARRIS_TEST_H_
