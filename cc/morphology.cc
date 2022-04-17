#include <iostream>
#include <cstdlib>
#include "opencv2/opencv.hpp"
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  string file_path = "../../images/lena.jpg";

  Mat image = read_image(file_path, true);
  if(image.size().height == 0) {
    throw runtime_error("Failed in reading the image.");
  }

  // morphology to get the border
  Mat ret;
  float sobelx_data[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  Mat sobelx = cv::Mat(3, 3, CV_32F, sobelx_data);
  morphologyEx(image, ret, MORPH_TOPHAT, sobelx);
  write_image("../tophat.jpg", ret);

  morphologyEx(image, ret, MORPH_BLACKHAT, sobelx);
  write_image("../blackhat.jpg", ret);  

  return 0;
}