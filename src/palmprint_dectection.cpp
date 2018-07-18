#include "ImageReader.h"
#include "HandDetector.h"

#include "opencv2/opencv.hpp"

cv::Mat binary(cv::Mat colorImg)
{
	cv::Mat grayImg,result;

	//todo: binary basing on skin color model
	cv::cvtColor(colorImg, grayImg,cv::COLOR_BGR2GRAY);
	cv::threshold(grayImg, result, 30, 200.0, cv::THRESH_BINARY);
	//cv::imshow("binary Img", result);
	//cv::waitKey();
	return result;
}

void matchTemplateFromBinaryImg(cv::Mat colorImg,cv::Mat binaryTemplate)
{
	//const string input_path = "/media/yjy/DATA1/VSProject/palmprint_dectection/data/input";
	const string output_path = "/media/yjy/DATA1/VSProject/palmprint_dectection/data/output/";
	const string file_name = "IMG_0272_002_LLL_015_107";

	double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
	cv::Mat result;

	cv::imshow("binary color Img", binary(colorImg));
	cv::imshow("binary Template Img", binaryTemplate);
	cv::waitKey();

	cv::matchTemplate(binary(colorImg), binaryTemplate, result,cv::TM_CCOEFF);//TM_SQDIFF

	cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
	cv::rectangle(colorImg, minLoc, cv::Point(minLoc.x + binaryTemplate.cols, minLoc.y + binaryTemplate.rows), cv::Scalar::all(0), 2, 8, 0);

	cv::imwrite(output_path + file_name + "-output.png", colorImg);
	cv::imshow("result", colorImg);
	cv::waitKey(0);
}


int main()
{
	const string img_load_base = "/media/yjy/DATA1/VSProject/palmprint_dectection/data/input/";
	const string img_save_base = "/media/yjy/DATA1/VSProject/palmprint_dectection/data/output/";
	const string file_name = "IMG_0272_002_LLL_015_107";

	cv::Mat colorImg = cv::imread(img_load_base + file_name + "-color.bmp");

	ImageReader ir(img_load_base + file_name +"-gray.bmp");
	//ir.loadImg();
	HandDetector hd(ir);

	matchTemplateFromBinaryImg(colorImg,hd.detect().getBinaryTemplate());

    return 0;
}

