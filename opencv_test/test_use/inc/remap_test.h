#pragma once
#ifndef _REMAP_TEST_H_
#define _REMAP_TEST_H_
#include <iostream>

#include <highgui.hpp>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

void remap_test_fi(void)
{
	cout << ">> ÷ÿ”≥…‰≤‚ ‘\n";
	Mat src0 = imread("D:/work/train_set/opencv_test_set/2.jpg"), img0, map_x, map_y;
	img0.create(src0.size(), src0.type());
	map_x.create(src0.size(), CV_32FC1);
	map_y.create(src0.size(), CV_32FC1);
	imshow("src0", src0);

	for (uint j = 0; j < src0.rows; ++j) {
		for (uint i = 0; i < src0.cols; ++i) {
			if (i > src0.cols*0.25 && i < src0.cols*0.75 && j > src0.rows*0.25 && j < src0.rows*0.75) {
				map_x.at<float>(j, i) = (float)(2*(i - src0.cols*0.25));
				map_y.at<float>(j, i) = (float)(2*(j - src0.rows*0.25));
			}
			else {
				map_x.at<float>(j, i) = 0;
				map_y.at<float>(j, i) = 0;
			}
		}
	}

	remap(src0, img0, map_x, map_y,INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0,0));
	imshow("img0", img0);

	waitKey(0);
}
#endif // ! _REMAAP_TEST_H_
