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

  Mat ret;
  // 128 for threshold 1 : the weaker threshold
  // 200 for threshold 2 : the stronger threshold
  Canny(image, ret, 128, 200, 3, true);
  write_image("../canny1.jpg", ret);

  Canny(image, ret, 32, 128, 3, true);
  write_image("../canny2.jpg", ret);

  return 0;
}