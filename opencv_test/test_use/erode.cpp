#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>		//opencv highgui ģ��ͷ�ļ�	
#include<opencv2/imgproc/imgproc.hpp>		//opencv ͼ�����ļ�
#include <cv.h>  
#include <highgui.h>  
#include <iostream>  

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test0\\0.jpg");  //����Լ�ͼ���·�� 
	namedWindow("ԭͼ");
	imshow("ԭͼ", image);
	
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));//ȡͼ�䳤Ϊ15�ķ������ص���Ϊһ������
	Mat dstlmage;
	erode(image, dstlmage, element);							//��getStructuringElementȡ�����ؼ��Ͻ���ģ��
	imshow("Ч��ͼ����ʴͼ��",dstlmage);

	waitKey(0);
	return 0;
}