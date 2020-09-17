#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat RGBGrey(Mat RGB) {
	Mat grey = Mat::zeros(RGB.size(), CV_8UC1);
	for (int i = 0; i < RGB.rows; i++) {
		for (int j = 0; j < RGB.cols * 3; j = j + 3) {
			grey.at<uchar>(i, j / 3) = (RGB.at<uchar>(i, j) + RGB.at<uchar>(i, j + 1) + RGB.at<uchar>(i, j + 2)) / 3;
		}
	}
	return grey;
}

Mat GreyBinary(Mat Grey, int t1) {
	Mat binary = Mat::zeros(Grey.size(), CV_8UC1);
	for (int i = 0; i < Grey.rows; i++) {
		for (int j = 0; j < Grey.cols; j++) {
			if (Grey.at<uchar>(i, j) >= t1)
				binary.at<uchar> (i, j) = 255;
		}
	}
	return binary;
}

Mat Invert(Mat Grey) {
	Mat invert = Mat::zeros(Grey.size(), CV_8UC1);
	for (int i = 0; i < Grey.rows; i++) {
		for (int j = 0; j < Grey.cols; j++) {
			invert.at<uchar>(i, j) = 255 - Grey.at<uchar>(i, j);
		}
	}
	return invert;
}

Mat FunctionImg(Mat Grey, int thresh) {
	Mat func = Mat::zeros(Grey.size(), CV_8UC1);
	for (int i = 0; i < Grey.rows; i++) {
		for (int j = 0; j < Grey.cols; j++) {
			if (Grey.at<uchar>(i, j) > thresh)
				func.at<uchar>(i, j) = thresh;
			else
				func.at<uchar>(i, j) = Grey.at<uchar>(i, j);
		}
	}
	return func;
}


Mat StepFunction(Mat Grey, int t1, int t2) {
	Mat Step = Mat::zeros(Grey.size(), CV_8UC1);
	for (int i = 0; i < Grey.rows; i++) {
		for (int j = 0; j < Grey.cols; j++) {
			if (Grey.at<uchar>(i, j) >= t1 && Grey.at<uchar>(i, j) <= t2)
				Step.at<uchar>(i, j) = 255;
		}
	}
	return Step;
}

Mat Equalizer(Mat grey) {
	Mat equalize = Mat::zeros(grey.size(), CV_8UC1);
	//algorithm from count to prob to acc to new pixel to replace
	int count_pixel[256] = { 0 }; //initialize the pixel from 0-255 as 0 to start the count
	for (int i = 0; i < grey.rows; i++) {
		for (int j = 0; j < grey.cols; j++) {

			count_pixel[grey.at<uchar>(i, j)++];
		}
	}


	// code section to calculate probability of the pixel from 0-255
	double probability[256] = { 0.0 };
	for (int i = 0; i < 256; i++)
		probability[i] = (double)count_pixel[i] / (double)(grey.rows * grey.cols);

	//calculate accumute probability


}




int main()
{
	Mat image;
	image = imread("C:\\Users\\Forge-15R\\Desktop\\IPCV Assignment\\Dataset\\Dataset\\1.jpg");
	imshow("RGB", image);

	Mat GreyImage = RGBGrey(image);
	imshow("Grey", GreyImage);

	Mat BinaryImage = GreyBinary(GreyImage, 70);
	imshow("Binary", BinaryImage);

	Mat InvertImage = Invert(GreyImage);
	imshow("Invert", InvertImage);

	Mat StepImage = StepFunction(GreyImage, 70, 100);
	imshow("StepUp", StepImage);

	Mat Function = FunctionImg(GreyImage, 170);
	imshow("Threshhold Image", Function);


	waitKey(0);
	return 0;
}


