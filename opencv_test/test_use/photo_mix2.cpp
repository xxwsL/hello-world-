//-----------------------------------������˵����----------------------------------------------  
//  ��������:����OpenCV���Ž̳�֮�ġ� ROI����ͼ�����&����ͼ���� ȫ����   ����Դ��  
// VS2010��   OpenCV�汾��2.4.8  
//     2014��3��10�� Create by ǳī  
//    ͼƬ�زĳ�����dota2ԭ�� dota2logo   
//     ǳī��΢����@ǳī_ë����  
//------------------------------------------------------------------------------------------------  

//-----------------------------------��ͷ�ļ��������֡�---------------------------------------  
//     ����������������������ͷ�ļ�  
//----------------------------------------------------------------------------------------------                                                                                      
#include <cv.h>  
#include <highgui.h>  
#include <iostream>  
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  

//-----------------------------------�������ռ��������֡�---------------------------------------  
//     ����������������ʹ�õ������ռ�  
//-----------------------------------------------------------------------------------------------    
using namespace cv;
using namespace std;


//-----------------------------------��ȫ�ֺ����������֡�--------------------------------------  
//     ������ȫ�ֺ�������  
//-----------------------------------------------------------------------------------------------  
bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();

//-----------------------------------��main( )������--------------------------------------------  
//     ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
//-----------------------------------------------------------------------------------------------  
int main()
{
	system("color 5E");

	if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending())
	{
		cout << endl << "�š����ˣ��ó�������Ҫ��ͼ��~! : )";
	}


	waitKey(0);
	return 0;
}

//----------------------------------��ROI_AddImage( )������----------------------------------  
// ��������ROI_AddImage����  
//     ���������ø���Ȥ����ROIʵ��ͼ�����  
//----------------------------------------------------------------------------------------------  
bool ROI_AddImage()
{

	//��1������ͼ��  
	Mat srcImage1 = imread("E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test0\\3.jpg");
	Mat logoImage = imread("E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test3\\4.jpg");
	if (!srcImage1.data) { printf("���ã���ȡsrcImage1����~�� \n"); return false; }
	if (!logoImage.data) { printf("���ã���ȡlogoImage����~�� \n"); return false; }

	//��2������һ��Mat���Ͳ������趨ROI����  
	Mat imageROI = srcImage1(Rect(100, 20, logoImage.cols, logoImage.rows));

	//��3��������ģ�������ǻҶ�ͼ��  
	Mat mask = imread("E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test3\\4.jpg");

	//��4������Ĥ������ROI  
	logoImage.copyTo(imageROI, mask);

	//��5����ʾ���  
	namedWindow("<1>����ROIʵ��ͼ�����ʾ������");
	imshow("<1>����ROIʵ��ͼ�����ʾ������", srcImage1);

	return true;
}


//---------------------------------��LinearBlending����������-------------------------------------  
// ��������LinearBlending����  
// ����������cv::addWeighted��������ʵ��ͼ�����Ի��  
//--------------------------------------------------------------------------------------------  
bool LinearBlending()
{
	//��0������һЩ�ֲ�����  
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	//��1����ȡͼ�� ( ����ͼƬ��Ϊͬ�������ͺͳߴ� )  
	srcImage2 = imread("E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test2\\0.jpg");
	srcImage3 = imread("E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test2\\1.jpg");

	if (!srcImage2.data) { printf("���ã���ȡsrcImage2����~�� \n"); return false; }
	if (!srcImage3.data) { printf("���ã���ȡsrcImage3����~�� \n"); return false; }

	//��2������ͼ���ϼ�Ȩ����  
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	//��3����������ʾԭͼ����  
	namedWindow("<2>���Ի��ʾ�����ڡ�ԭͼ�� byǳī", 1);
	imshow("<2>���Ի��ʾ�����ڡ�ԭͼ�� byǳī", srcImage2);

	namedWindow("<3>���Ի��ʾ�����ڡ�Ч��ͼ�� byǳī", 1);
	imshow("<3>���Ի��ʾ�����ڡ�Ч��ͼ�� byǳī", dstImage);

	return true;

}

//---------------------------------��ROI_LinearBlending������-------------------------------------  
// ��������ROI_LinearBlending����  
// ���������Ի��ʵ�ֺ���,ָ����������ͼ����.����cv::addWeighted����������϶���  
//                     ����Ȥ����ROI��ʵ���Զ�����������Ի��  
//--------------------------------------------------------------------------------------------  
bool ROI_LinearBlending()
{

	//��1����ȡͼ��  
	Mat srcImage4 = imread("E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test0\\3.jpg", 1);
	Mat logoImage = imread("E:\\ͼƬ�ֿ�\\����ĩ��\\opencv_test3\\4.jpg");

	if (!srcImage4.data) { printf("���ã���ȡsrcImage4����~�� \n"); return false; }
	if (!logoImage.data) { printf("���ã���ȡlogoImage����~�� \n"); return false; }

	//��2������һ��Mat���Ͳ������趨ROI����  
	Mat imageROI;
	//����һ  
	imageROI = srcImage4(Rect(100, 20, logoImage.cols, logoImage.rows));
	//������  
	//imageROI=srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));  

	//��3����logo�ӵ�ԭͼ��  
	addWeighted(imageROI, 0.4, logoImage, 0.6, 0., imageROI);

	//��4����ʾ���  
	namedWindow("<4>��������ͼ����ʾ������ byǳī");
	imshow("<4>��������ͼ����ʾ������ byǳī", srcImage4);
	namedWindow("ԭͼ");
	imshow("ԭͼ", logoImage); 

	return true;
}