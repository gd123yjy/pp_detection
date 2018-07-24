#pragma once
#include "string"

#include "ObjectDetector.h"
#include "ImageReader.h"

using namespace std;

class HandDetector : virtual public ObjectDetector
{
private:
	ImageReader ir_gray;
	ImageReader ir_color;
	cv::Mat detected_result;
	cv::Mat binaryTemplate;

	void cropTemplate(cv::Mat grayImg, cv::Mat &result);
	int distance(cv::Vec3b a, cv::Vec3b b);
	cv::Mat binary_skin_model(cv::Mat colorImg, int low_thred, int high_thred);
	void matchTemplateFromBinaryImg(cv::Mat colorImg, cv::Mat binaryTemplate, cv::Point &maxLoc, cv::Point &maxLoc_diangle);

public:
	HandDetector();
	HandDetector(ImageReader gray, ImageReader color);
	HandDetector detect();
	cv::Mat getResult() { return detected_result; };
	cv::Mat getBinaryTemplate() { return binaryTemplate; };
	~HandDetector();
};
