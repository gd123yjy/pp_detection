#include "ImageReader.h"
#include "HandDetector.h"

#include "math.h"
#include "opencv2/opencv.hpp"

using namespace cv;

int distance(Vec3b a, Vec3b b)
{
	return sqrt(pow((a[0] - b[0]), 2) + pow((a[1] - b[1]), 2) + pow((a[2] - b[2]), 2));
}

Mat binary(Mat colorImg, int low_thred, int high_thred)
{
	Mat result;

	result.create(colorImg.size(), CV_8U);
	assert(high_thred >= low_thred);

	//binary basing on skin color model
	//bgr(58,89,108)~bgr(20,26,30) mid(39,57,69)
	MatConstIterator_<Vec3b> it_in = colorImg.begin<Vec3b>();
	MatConstIterator_<Vec3b> itend_in = colorImg.end<Vec3b>();
	MatIterator_<uchar> it_out = result.begin<uchar>();
	MatIterator_<uchar> itend_out = result.end<uchar>();
	while (it_in != itend_in)
	{
		int diff = distance(*it_in, Vec3b(36, 52, 66));
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

int main(int args, char **argv)
{
	const string img_load_base = "/media/yjy/DATA1/VSProject/palmprint_dectection/data/input/";
	const string img_save_base = "/media/yjy/DATA1/VSProject/palmprint_dectection/data/output/";
	const string file_name_color = argv[1]; //"IMG_0129_004_RRR_019_104";
	const string file_name_gray = argv[2];  //"IMG_0129_004_RRR_020_104";
	const string out_file_name = file_name_color.substr(0, file_name_color.find_first_of(".bmp"));

	ImageReader ir_color(img_load_base + file_name_color);
	ImageReader ir_gray(img_load_base + file_name_gray);

	HandDetector hd(ir_gray.binary(), ir_color);

	hd.detect();

	Mat binaryTemplate = hd.getBinaryTemplate();
	Mat detected_result = hd.getResult();

	cv::imwrite(img_save_base + out_file_name + "-output.png", detected_result);

	cv::imshow("binary color Img", binary(ir_color.getImg(), 25, 35));
	cv::imshow("binary Template Img", binaryTemplate);
	cv::imshow("result", detected_result);
	cv::waitKey(0);

	return 0;
}
