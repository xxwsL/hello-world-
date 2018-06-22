#pragma once
#ifndef _PYR_UP_DOWN_TEST_H_
#define _PYR_UP_DOWN_TEST_H_

#include <highgui.hpp>
#include <imgproc.hpp>

using namespace cv;

void pyr_up_down_test(void)
{
	Mat img0 = imread("E:\\Í¼Æ¬²Ö¿â\\×ÀÃæ\\2.jpg");
	Mat img1 = img0.clone();
	for (uint i = 0; i < 1; ++i) {
		pyrDown(img1, img1);
		//pyrDown(img1, img1);
		//pyrDown(img1, img1);
		//pyrUp(img1, img1);
		//pyrUp(img1, img1);
		pyrUp(img1, img1);
	}
	namedWindow("img0", WINDOW_AUTOSIZE);
	imshow("img0", img1);
	waitKey(0);
}
#endif // !_PYR_UP_DOWN_TEST_H_
