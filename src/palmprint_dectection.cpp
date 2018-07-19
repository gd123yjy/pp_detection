#include "ImageReader.h"
#include "HandDetector.h"

#include "math.h"
#include "opencv2/opencv.hpp"

using namespace cv;

int distance(Vec3b a, Vec3b b)
{
	return sqrt(pow((a[0] - b[0]), 2) + pow((a[1] - b[1]), 2) + pow((a[2] - b[2]), 2));
}

Mat binary(Mat colorImg)
{
	Mat result;

	result.create(colorImg.size(), CV_8U);

	//binary basing on skin color model
	//bgr(38,55,71)~bgr(20,26,30) mid(29,40,50)
	MatConstIterator_<Vec3b> it_in = colorImg.begin<Vec3b>();
	MatConstIterator_<Vec3b> itend_in = colorImg.end<Vec3b>();
	MatIterator_<uchar> it_out = result.begin<uchar>();
	MatIterator_<uchar> itend_out = result.end<uchar>();
	while (it_in != itend_in)
	{
		if (distance(*it_in, Vec3b(29, 40, 50)) < 28)
		{
			(*it_out) = 200;
		}
		else
		{
			(*it_out) = 0;
		}

		it_in++;
		it_out++;
	}

	return result;
}

void matchTemplateFromBinaryImg(cv::Mat colorImg, cv::Mat binaryTemplate, Point &maxLoc, Point &maxLoc_diangle)
{
	double minVal;
	double maxVal;
	cv::Point minLoc;
	cv::Mat result;

	cv::matchTemplate(binary(colorImg), binaryTemplate, result, cv::TM_CCOEFF); //TM_SQDIFF

	cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

	maxLoc_diangle = Point2d(maxLoc.x + binaryTemplate.cols, maxLoc.y + binaryTemplate.rows);
}

int main()
{
	const string img_load_base = "/media/yjy/DATA1/VSProject/palmprint_dectection/data/input/";
	const string img_save_base = "/media/yjy/DATA1/VSProject/palmprint_dectection/data/output/";
	const string file_name = "IMG_0272_002_LLL_015_107";

	cv::Point maxLoc, maxLoc_diangle;
	cv::Mat colorImg = cv::imread(img_load_base + file_name + "-color.bmp");

	ImageReader ir(img_load_base + file_name + "-gray.bmp");
	//ir.loadImg();
	HandDetector hd(ir);

	Mat binaryTemplate = hd.detect().getBinaryTemplate();
	matchTemplateFromBinaryImg(colorImg, binaryTemplate, maxLoc, maxLoc_diangle);
	cv::rectangle(colorImg, maxLoc, maxLoc_diangle, cv::Scalar(0, 155, 0), 2, 8, 0);

	cv::imwrite(img_save_base + file_name + "-output.png", colorImg);

	cv::imshow("binary color Img", binary(colorImg));
	cv::imshow("binary Template Img", binaryTemplate);
	cv::imshow("result", colorImg);
	cv::waitKey(0);

	return 0;
}
