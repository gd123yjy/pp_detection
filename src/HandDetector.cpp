#include "string"

#include "HandDetector.h"

using namespace std;

HandDetector::HandDetector()
{
}

HandDetector::HandDetector(ImageReader ir)
{
	this->ir = ir;
	//todo: asert ir.getImg() is binary image
}


HandDetector HandDetector::detect()
{
	//todo:eee
	this->ir.getImg().rowRange(60,420).colRange(100,550).copyTo(this->result);
	return *this;
}


void HandDetector::saveResult(string path)
{
	cv::imwrite(path, this->result);
}

cv::Mat HandDetector::getBinaryTemplate()
{
	return this->result;
}

HandDetector::~HandDetector()
{
}
