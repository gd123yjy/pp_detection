#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fstream>

#include "opencv2/opencv.hpp"
#include "HandDetector.h"

using namespace cv;
using namespace std;

int main(int args, char **argv)
{
    int bbox[4] = {0};
    const string img_load_base_color = "/home/yjy/dataset/palmprint_dectection/palmprint/";
    const string img_load_base_gray = "/home/yjy/dataset/palmprint_dectection/palmvein/";
    const string bbox_save_base = "/home/yjy/dataset/palmprint_dectection/output/";
    string file_name_color;
    string file_name_gray;
    int length;
    HandDetector *hd;
    DIR *dir = opendir(img_load_base_color.c_str());
    ofstream txt("bbox_save_base" + "bbox.txt");

    while ((filename = readdir(dir)) != NULL)
    {
        if (strcmp(filename->d_name, ".") == 0 ||
            strcmp(filename->d_name, "..") == 0)
            continue;

        file_name_color = filename->d_name;
        length = file_name_color.length();
        file_name_gray = file_name_color.substr(0, length - 7);

        //detect & return bbox
        ImageReader ir_color(img_load_base_color + file_name_color);
        ImageReader ir_gray(img_load_base_gray + file_name_gray);
        hd = new HandDetector(ir_gray.binary(), ir_color);
        hd->detect();
        hd->getDetectedBox(bbox);

        //write to txt
        txt << file_name_gray + " " + bbox[0] + " " + bbox[1] + " " + bbox[2] + " " + bbox[3] + "\n";
    }

    txt.close();
    delete dir;
    delete hd;

    return 0;
}
