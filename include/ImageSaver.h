#pragma once
#include <string>

#include <opencv2/opencv.hpp>

using namespace std;

class ImageSaver
{
private:
	cv::Mat img;

public:
	ImageSaver();
	ImageSaver(const string& path);
	void loadImg(const string& path);
	cv::Mat getImg();
	~ImageSaver();
};

