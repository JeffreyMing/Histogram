#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char ** argv)
{

	// Read the image
	string filename = "../../data/images/capsicum.jpg";
	if (argc == 2)
	{
		filename = argv[1];
	}

	Mat img = imread(filename);
	imshow("Image", img);

	// �ഫ���Ƕ��v��
	Mat GrayImage;
	cvtColor(img, GrayImage, COLOR_BGR2GRAY);
	imshow("Gray Image", GrayImage);

	//�w�q����ϰѼ�
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float pranges[2] = { 0,255 };
	const float * ranges[] = { pranges };

	//�p�⪽���
	MatND hist;
	calcHist(&GrayImage, 1, channels, Mat(), hist,1, histSize, ranges);

	// ��l�ƹϪ�Ѽ�
	int hist_w = 1000; 
	int hist_h = 500; 
	int nHistSize = 255;
	int bin_w = cvRound((double)hist_w / nHistSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	//�N����ϼзǤƦ�[0, histImage.rows]�A�קK�W�X�Ϫ�
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	//�b�Ϫ�W�e�X�����
	for (int i = 1; i < nHistSize; i++) {
		line(histImage, Point(bin_w*(i - 1), hist_h - hist.at<float>(i - 1)), 
			Point(bin_w*(i), hist_h - hist.at<float>(i)), 
			Scalar(0, 0, 255), 2, CV_AA, 0);
	}
	imshow("histImage", histImage);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
