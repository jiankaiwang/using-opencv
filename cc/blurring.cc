#include <iostream>
#include <cstdlib>
#include "opencv2/opencv.hpp"
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {
  string file_path = "../../images/lena.jpg";

  Mat image = read_image(file_path, false);
  if(image.size().height == 0) {
    throw runtime_error("Failed in opening the image file.");
  }

  // image blurring
  Mat ret;
  blur(image, ret, Size(5, 5));
  write_image("../test_5.jpg", ret);

  blur(image, ret, Size(30, 30));
  write_image("../test_30.jpg", ret);  

  // box blurring
  // normalize = 0
  boxFilter(image, ret, -1, Size(2, 2), Point(-1, -1), 0);
  write_image("../box.jpg", ret);

  // gaussian blurring
  // sigmaX = 0 , sigmaY = 0
  GaussianBlur(image, ret, Size(5, 5), 0, 0);
  write_image("../gaussian.jpg", ret);

  // bilateral blurring
  // pixel distance = 5
  // sigma color = 8
  // sigma space = 5
  bilateralFilter(image, ret, 5, 8, 5);
  write_image("../bilateral.jpg", ret);
  
  return 0;
}