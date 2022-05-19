#include <iostream>
#include <cstdlib>
#include "helper.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  string file_path = "../../images/lena.jpg";

  Mat image = read_image(file_path, true);
  if(image.empty()) {
    throw runtime_error("Failed in opening the image.");
  }

  Mat padded;                               //expand input image to optimal size
  int m = getOptimalDFTSize( image.rows );
  int n = getOptimalDFTSize( image.cols );  // on the border add zero values
  copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, BORDER_CONSTANT, Scalar::all(0));  

  Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
  Mat complex;
  merge(planes, 2, complex);

  // to do the dft
  dft(complex, complex, DFT_COMPLEX_OUTPUT);

  // to do the idft
  Mat output;
  idft(complex, output);

  // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
  split(output, planes); 

  // planes[0] = sqrt(re^2 + lm^2) * size of data (here is the number of image pixels)
  magnitude(planes[0], planes[1], planes[0]); 

  int kernel = image.rows * image.cols;
  output = planes[0] / kernel;

  write_image("../img_idft.jpg", output);

  return 0;
}