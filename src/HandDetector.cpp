#include "string"
#include "math.h"

#include "HandDetector.h"

using namespace std;

HandDetector::HandDetector()
{
}

HandDetector::HandDetector(ImageReader gray, ImageReader color)
{
	//todo: asert ir.getImg() is binary image
	this->ir_gray = gray;
	this->ir_color = color;
	ir_color.getImg().copyTo(this->detected_result);
}

void HandDetector::cropTemplate(cv::Mat grayImg, cv::Mat &result)
{
	vector<vector<cv::Point>> contours;
	int max_x, min_x, max_y, min_y, max_area, max_area_i, count;

	min_x = min_y = 1e6;
	max_x = max_y = max_area = max_area_i = count = 0;

	assert(grayImg.type() == CV_8U);
	cv::findContours(grayImg, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

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

	grayImg.rowRange(min_y, max_y).colRange(min_x, max_x).copyTo(result);
}

int HandDetector::distance(cv::Vec3b a, cv::Vec3b b)
{
	return sqrt(pow((a[0] - b[0]), 2) + pow((a[1] - b[1]), 2) + pow((a[2] - b[2]), 2));
}

cv::Mat HandDetector::binary_skin_model(cv::Mat colorImg, int low_thred, int high_thred)
{
	cv::Mat result;

	result.create(colorImg.size(), CV_8U);
	assert(high_thred >= low_thred);

	//binary basing on skin color model
	//bgr(58,89,108)~bgr(20,26,30) mid(39,57,69)
	cv::MatConstIterator_<cv::Vec3b> it_in = colorImg.begin<cv::Vec3b>();
	cv::MatConstIterator_<cv::Vec3b> itend_in = colorImg.end<cv::Vec3b>();
	cv::MatIterator_<uchar> it_out = result.begin<uchar>();
	cv::MatIterator_<uchar> itend_out = result.end<uchar>();
	while (it_in != itend_in)
	{
		int diff = distance(*it_in, cv::Vec3b(30, 40, 48));
		if (diff <= low_thred)
		{
			(*it_out) = 200;
		}
		else if (diff > high_thred)
		{
			(*it_out) = 0;
		}
		else
		{
			(*it_out) = 200 + 200 / (low_thred - high_thred) * (diff - low_thred);
		}

		it_in++;
		it_out++;
	}

	return result;
}

void HandDetector::matchTemplateFromBinaryImg(cv::Mat colorImg, cv::Mat binaryTemplate, cv::Point &maxLoc, cv::Point &maxLoc_diangle)
{
	double minVal;
	double maxVal;
	cv::Point minLoc;
	cv::Mat m_result;

	cv::matchTemplate(binary_skin_model(colorImg, 25, 35), binaryTemplate, m_result, cv::TM_CCOEFF); //TM_SQDIFF

	cv::minMaxLoc(m_result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

	maxLoc_diangle = cv::Point2d(maxLoc.x + binaryTemplate.cols, maxLoc.y + binaryTemplate.rows);
}

HandDetector HandDetector::detect()
{
	cv::Point matchLoc, matchLoc_diangle;

	this->cropTemplate(ir_gray.getImg(), binaryTemplate);
	this->matchTemplateFromBinaryImg(ir_color.getImg(), binaryTemplate, matchLoc, matchLoc_diangle);
	
	cv::rectangle(detected_result, matchLoc, matchLoc_diangle, cv::Scalar(0, 155, 0), 2, 8, 0);

	return *this;
}

HandDetector::~HandDetector()
{
}
