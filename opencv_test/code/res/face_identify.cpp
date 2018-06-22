#include <face_identify_t.h>
#include <xxwsL.h>

#include <iostream>
#include <stdio.h>
#include <vector>

#include <opencv.hpp>
#include <core.hpp>
#include <opencv2/face.hpp>

using namespace std;
using namespace cv;
using namespace face;

void face_identify(void)
{
	cv::CascadeClassifier cas("E:/opencv3.40/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml");    //加载人脸分类器
	cv::Ptr<EigenFaceRecognizer> fc = EigenFaceRecognizer::create();

	//加载训练照片
	cv::Mat t0 = cv::imread("D:/work/train_set/face_test/2000.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat t1 = cv::imread("D:/work/train_set/face_test/2001.jpg", CV_LOAD_IMAGE_GRAYSCALE);  
	cv::Mat t2 = cv::imread("D:/work/train_set/face_test/2002.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat t3 = cv::imread("D:/work/train_set/face_test/2004.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//cv::Mat t4 = cv::imread("D:/work/train_set/face_test/t4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//cv::Mat t5 = cv::imread("D:/work/train_set/face_test/t5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//cv::Mat t6 = cv::imread("D:/work/train_set/face_test/t6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//cv::Mat t7 = cv::imread("D:/work/train_set/face_test/t7.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//cv::Mat a8 = cv::imread("D:/work/train_set/face_test/08.jpg", CV_LOAD_IMAGE_GRAYSCALE);


	vector<cv::Mat> images;
	vector<int>labels;
	images.push_back(t0);
	labels.push_back(0);
	images.push_back(t1);        
	labels.push_back(0);
	images.push_back(t2);
	labels.push_back(0);
	images.push_back(t3);
	labels.push_back(0);
	//images.push_back(t4);
	//labels.push_back(0);
	//images.push_back(t5);
	//labels.push_back(0);
	//images.push_back(t6);
	//labels.push_back(0);
	//images.push_back(t7);
	//labels.push_back(0);

	//images.push_back(a8);
	//labels.push_back(1);
	fc->train(images, labels);    //训练


	cv::VideoCapture cap;
	cap.open(0);
	string test_image_path;
	vector<cv::Rect> recs;
	cv::Mat test(600, 600, CV_8UC1);
	cv::Mat gray;
	int x = 0, y = 0;
	char key_value = 1;

	//开始采集人脸数据
	//cout << "input C getimage	 input T start train	input Q exit\n";
	//while (key_value) {
	//	if (KEY_DOWN('C')) {
	//		cv::Mat tr_images;
	//		cap >> tr_images;
	//		cv::resize(tr_images, tr_images, cv::Size(600, 600));
	//		cvtColor(tr_images, tr_images, CV_BGR2GRAY);
	//		imshow("tr_images", tr_images);
	//		images.push_back(tr_images);
	//		labels.push_back(0);
	//	}
	//	if (KEY_DOWN('T')){
	//		fc->train(images, labels);    //训练
	//		key_value = 0;
	//	}
	//	if (KEY_DOWN('Q')) {
	//		key_value = 0;
	//	}
	//	cv::waitKey(10);
	//}


	for (;;)
	{
		cv::Mat image;
		//cin >> test_image_path;
		//cv::imread(test_image_path);
		cap >> image;
		cv::resize(image, image, cv::Size(600, 600));
		if (image.empty())
			break;
		cas.detectMultiScale(image, recs, 1.2, 6, 0, cv::Size(50, 50));    //先检测人脸
		for (int i = 0; i < recs.size(); i++)
		{
			rectangle(image, recs[i], cv::Scalar(0, 0, 255));
			x = recs[i].x + recs[i].width / 2;
			y = recs[i].y + recs[i].height / 2;

			cv::Mat roi = image(recs[i]);
			cvtColor(roi, gray, CV_BGR2GRAY);
			resize(gray, test, cv::Size(600, 600));
			int result = fc->predict(test);
			switch (result)
			{
			case 0:
				putText(image, "hzw", cv::Point(recs[i].x, recs[i].y), cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar(0, 0, 255), 2); break;
			case 1:
				putText(image, "other", cv::Point(recs[i].x, recs[i].y), cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar(0, 0, 255), 2); break;
			case 2:
				putText(image, "c", cv::Point(recs[i].x, recs[i].y), cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar(0, 0, 255), 2); break;
			}
		}
		imshow("Sample", image);
		if (cv::waitKey(30) >= 0)
			break;
	}
}

void face_identify_online(void) {
	//创建摄像头类
	VideoCapture cap;
	//加载人脸分类器
	cv::CascadeClassifier cas("E:/opencv3.40/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml"); 
	//创建训练模型类
	cv::Ptr<FisherFaceRecognizer> fc = FisherFaceRecognizer::create();
	//创建图片容器 & 标签容器
	vector<Mat> images; vector<int> labels;
	//打开摄像头
	cap.open(0);
}
