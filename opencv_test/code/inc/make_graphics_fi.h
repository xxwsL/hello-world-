#ifndef _MAKE_GRAPHICS_FI_H_
#define _MAKE_GRAPHICS_FI_H_

#include <highgui.hpp>
#include <imgproc.hpp>

using namespace cv;

#define WINDOW_WIDTH 600

void DrawEllipse(Mat img, double angle)
{
	int thickness = 2, line_type = 8;
	ellipse(img,
		Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
		Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
		angle,
		0,
		360,
		Scalar(255, 129, 0),
		thickness,
		line_type
	);
}
#endif // !_MAKE_GRAPHICS_FI_H_h

