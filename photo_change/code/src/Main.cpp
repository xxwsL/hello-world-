#include "Image_to_BinaryData.h"

int main()
{
	string base_path = "D:/work/train_set/2018_6_16_set/";
	Image2BinaryData IBD(128,128);											//����ͼƬ��С(Height,Width)
	
	/*------------����ѵ�����ļ�--------------------------*/
	printf("----------����ѵ�����ļ�-------------\n");
	string trainfilefolder = base_path + "128train39";		//ѵ��ͼƬ�ļ�·��
	vector<string> trainfileLists = IBD.getFileLists(trainfilefolder);				//����ļ����б�

	const int train_size_list = trainfileLists.size();
	cout << "Images Number: " << train_size_list << endl;							//����ļ�����

	string trainimagebinfilepath = base_path + "train-images-idx3-ubyte";		//ѵ��ͼƬת������·��
	string trainlabelbinfilepath = base_path + "train-labels-idx1-ubyte";		//ѵ����ǩת������·��
	vector<cv::Mat> TrainImagesMat;															//�����洢ѵ��ͼƬ����ֵ
	vector<int> train_image_labels(train_size_list);										//�����洢ѵ�����ǩ�б�
	IBD.ReadImage(trainfilefolder, trainfileLists, train_image_labels, TrainImagesMat);		//��ȡѵ��ͼƬ
	IBD.Image2BinaryFile(trainimagebinfilepath, TrainImagesMat, train_image_labels);		//ѵ��ͼƬת�������ļ�
	IBD.Label2BinaryFile(trainlabelbinfilepath, train_image_labels);						//ѵ����ǩת�������ļ�
	 
	/*------------���ɲ��Լ��ļ�--------------------------*/
	printf("\n\n----------���ɲ��Լ��ļ�-------------\n");
	string testfilefolder = base_path + "128test39";		//����ͼƬ�ļ�·��
	vector<string> testfileLists = IBD.getFileLists(testfilefolder);			//����ļ����б�
	
	const int test_size_list = testfileLists.size();
	cout << "Images Number: " << test_size_list << endl;									//����ļ�����
	string testimagebinfilepath = base_path + "t10k-images-idx3-ubyte";		//����ͼƬת������·��
	string testlabelbinfilepath  = base_path + "t10k-labels-idx1-ubyte";		//���Ա�ǩת������·��
	vector<cv::Mat> TestImagesMat;															//�����洢����ͼƬ����ֵ
	vector<int> test_image_labels(test_size_list);											//�����洢�������ǩ�б�
	IBD.ReadImage(testfilefolder, testfileLists, test_image_labels, TestImagesMat);			//��ȡ����ͼƬ
	IBD.Image2BinaryFile(testimagebinfilepath, TestImagesMat, test_image_labels);			//����ͼƬת�������ļ�
	IBD.Label2BinaryFile(testlabelbinfilepath, test_image_labels);							//���Ա�ǩת�������ļ�

	return 0;
}