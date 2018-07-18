#include <string>

#include <opencv2/opencv.hpp>

#include "ImageReader.h"

using namespace std;

ImageReader::ImageReader()
{
}

ImageReader::ImageReader(const std::string& path)
{
	cv::Mat img1 = cv::imread(path);
	img = img1;
	
	cv::cvtColor(img, img,cv::COLOR_BGR2GRAY);
	cv::threshold(img, img, 30, 200.0, cv::THRESH_BINARY);
	//cv::imshow("template", img);
	//cv::waitKey();
}

void ImageReader::loadImg(const string& path)
{
	cv::Mat img1 = cv::imread(path);
	img = img1;

	cv::cvtColor(img, img,cv::COLOR_BGR2GRAY);
	cv::threshold(img, img, 30, 200.0, cv::THRESH_BINARY);
	//cv::imshow("template", img);
	//cv::waitKey();
	return;
}

cv::Mat ImageReader::getImg()
{
	return img;
}

ImageReader::~ImageReader()
{
}
