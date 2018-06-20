#include <iostream>  

#include <highgui.hpp>
#include <imgproc.hpp>

#include <make_graphics_fi.h>
#include <flood_fill.h>
#include <pyr_up_down_test.h>
#include <face_identify_t.h>
#include <hough_test.h>
#include <remap_test.h>
#include <affine_test.h>
#include <equil_test.h>
#include <histogram_test.h>
#include <harris_test.h>

using namespace std;
using namespace cv;

void t0(void)
{
	Mat img, gray;
	imread("E:\\Í¼Æ¬²Ö¿â\\×ÀÃæ\\3.jpg").copyTo(img);
	namedWindow("original");
	imshow("original", img);
	cvtColor(img, gray, COLOR_BGR2GRAY);
	//¸ßË¹ÂË²¨
	GaussianBlur(gray, gray, Size(7, 7), 1.5);
	Canny(gray, gray, 0, 50);

	imshow("edges", gray);
}

void t1(void) {
	Mat img0 = imread("E:\\Í¼Æ¬²Ö¿â\\×ÀÃæ\\3.jpg"); Mat img1 = imread("E:/Í¼Æ¬²Ö¿â/ÊÀ½çÄ©ÈÕ/opencv_test3/8.jpg");
	Mat mask = imread("E:/Í¼Æ¬²Ö¿â/ÊÀ½çÄ©ÈÕ/opencv_test3/8.jpg", 0);
	Mat img0_rect = img0(Rect(200, 200, mask.cols, mask.rows));	Mat rect_temp(img0);
	rect_temp.setTo(0);
	imshow("img0_rect", img0_rect);
	//img1.copyTo(img0_rect, mask);
	imshow("new_graph", img0);
}

int main(int argc, char** argv)
{
	//remap_test_fi();
	affine_test_fi();
	//equil_test_fi();
	//histogram_test_fi();
	//harris_test_fi();
	//face_identify();

	waitKey(0);
	while (1);
	return 0;
}