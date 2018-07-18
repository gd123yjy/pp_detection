#pragma once
#include "string"

#include "ObjectDetector.h"
#include "ImageReader.h"

using namespace std;

class HandDetector :
	public ObjectDetector
{
private:
	ImageReader ir;
	cv::Mat result;
public:
	HandDetector();
	HandDetector(ImageReader ir);
	HandDetector detect();
	void saveResult(string path);
	cv::Mat getResult() { return result; };
	cv::Mat getBinaryTemplate();
	~HandDetector();
};

