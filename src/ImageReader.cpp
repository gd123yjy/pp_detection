#include <string>

#include <opencv2/opencv.hpp>

#include "ImageReader.h"

using namespace std;

ImageReader::ImageReader()
{
}

ImageReader::ImageReader(const std::string &path)
{
	cv::Mat img1 = cv::imread(path);
	img = img1;
}

ImageReader ImageReader::binary()
{
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	cv::threshold(img, img, 30, 200.0, cv::THRESH_BINARY);
	return *this;
}

void ImageReader::loadImg(const string &path)
{
	img = cv::imread(path);
	return;
}

cv::Mat ImageReader::getImg()
{
	return img;
}

ImageReader::~ImageReader()
{
}
