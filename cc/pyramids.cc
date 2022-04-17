#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  string file_path = "../../images/lena.jpg";

  Mat image = read_image(file_path, false);
  if(image.size().height == 0) {
    throw runtime_error("Failed in opening the image.");
  }

  stringstream ss;  

  // down sampling, default size is 1/2
  Mat down;
  pyrDown(image, down);
  ss << "../down_" <<  down.size().height << "x" << down.size().width << ".jpg";
  write_image(ss.str(), down);
  ss.clear();

  // up sampling, default size is 2
  Mat up;
  pyrUp(down, up);
  ss << "../up_from_1_" <<  up.size().height << "x" << up.size().width << ".jpg";
  write_image(ss.str(), up); 
  ss.str(""); 

  pyrDown(down, down);
  ss << "../down_" <<  down.size().height << "x" << down.size().width << ".jpg";
  write_image(ss.str(), down);
  ss.str(""); 

  pyrUp(down, up);
  ss << "../up_from_2_" <<  up.size().height << "x" << up.size().width << ".jpg";
  write_image(ss.str(), up);
  ss.str(""); 

  pyrUp(up, up);
  ss << "../up_from_2_2_" <<  up.size().height << "x" << up.size().width << ".jpg";
  write_image(ss.str(), up);  
  ss.str(""); 

  return 0;
}