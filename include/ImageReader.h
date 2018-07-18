#pragma once
#include <string>

#include <opencv2/opencv.hpp>

using namespace std;

class ImageReader
{
private:
	cv::Mat img;

public:
	ImageReader();
	ImageReader(const string& path);
	void loadImg(const string& path);
	cv::Mat getImg();
	~ImageReader();
};

