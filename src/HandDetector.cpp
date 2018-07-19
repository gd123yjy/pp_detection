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
	cv::Mat gray_img;
	vector<vector<cv::Point>> contours;
	int max_x, min_x, max_y, min_y, max_area, max_area_i, count;

	min_x = min_y = 1e6;
	max_x = max_y = max_area = max_area_i = count = 0;

	assert(this->ir.getImg().type() == CV_8U);
	cv::findContours(this->ir.getImg(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	for (vector<vector<cv::Point>>::iterator i = contours.begin(); i != contours.end(); i++)
	{
		int area = cv::contourArea(*i);
		if (area > max_area)
		{
			max_area = area;
			max_area_i = count;
		}
		count++;
	}

	for (vector<cv::Point>::iterator i = contours[max_area_i].begin(); i != contours[max_area_i].end(); i++)
	{
		if (max_x < i->x)
		{
			max_x = i->x;
		}
		if (max_y < i->y)
		{
			max_y = i->y;
		}
		if (min_x > i->x)
		{
			min_x = i->x;
		}
		if (min_y > i->y)
		{
			min_y = i->y;
		}
	}

	this->ir.getImg().rowRange(min_y, max_y).colRange(min_x, max_x).copyTo(this->result);

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
