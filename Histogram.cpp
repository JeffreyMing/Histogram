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

	// 轉換為灰階影像
	Mat GrayImage;
	cvtColor(img, GrayImage, COLOR_BGR2GRAY);
	imshow("Gray Image", GrayImage);

	//定義直方圖參數
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float pranges[2] = { 0,255 };
	const float * ranges[] = { pranges };

	//計算直方圖
	MatND hist;
	calcHist(&GrayImage, 1, channels, Mat(), hist,1, histSize, ranges);

	// 初始化圖表參數
	int hist_w = 1000; 
	int hist_h = 500; 
	int nHistSize = 255;
	int bin_w = cvRound((double)hist_w / nHistSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	//將直方圖標準化至[0, histImage.rows]，避免超出圖表
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	//在圖表上畫出直方圖
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
