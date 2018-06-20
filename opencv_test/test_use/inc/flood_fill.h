#pragma once
#ifndef _FLOOD_FILL_H_
#define _FLOOD_FILL_H_

#include <highgui.hpp>
#include <imgproc.hpp>

Mat flood_fill_src_img = imread("E:\\Í¼Æ¬²Ö¿â\\×ÀÃæ\\2.jpg");

using namespace cv;

static void on_mouse(int event, int x, int y, int, void*)
{
	if (event != EVENT_FLAG_LBUTTON)
		return;

	const int low_diffence = 20, up_diffence = 20;
	floodFill(flood_fill_src_img, Point(x,y), Scalar(255, 0, 0), 0,
		Scalar(low_diffence, low_diffence, low_diffence),
		Scalar(up_diffence, up_diffence, up_diffence),
		8|FLOODFILL_FIXED_RANGE);
	imshow("flood_fill_test", flood_fill_src_img);
}

void flood_fill_test(void)
{
	namedWindow("flood_fill_test",WINDOW_AUTOSIZE);
	setMouseCallback("flood_fill_test", on_mouse, 0);
	while (1) {
		imshow("flood_fill_test", flood_fill_src_img);
		waitKey(0);
	}
}
#endif // ! _FLOOD_FILL_H_

