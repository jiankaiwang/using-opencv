#include <iostream>
#include <cstdlib>
#include "helper.hpp"
#include <opencv2/opencv.hpp>

// https://blog.csdn.net/zhaitianbao/article/details/117955380

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  string file_path = "../../images/lena.jpg";
  Mat image = read_image(file_path, true);
  if(image.empty()) {
    throw runtime_error("Failed in opening the image file.");
  }

  Mat padded;
  int r = getOptimalDFTSize( image.rows );
  int c = getOptimalDFTSize( image.cols );
  copyMakeBorder(image, padded, 0, r - image.rows, 0, c - image.cols, BORDER_CONSTANT, Scalar::all(0));

  Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
  Mat complex;
  merge(planes, 2, complex);
  // cout << "Complex size: " << complex.size() << ", channel: " << complex.channels() << endl;

  // do the dft
  dft(complex, complex, DFT_COMPLEX_OUTPUT);

  // do the fftshift
  split(complex, planes);
  fftshift(planes[0], planes[1]);

  // create a high pass filter
  Mat mask = Mat(image.cols, image.rows, CV_32F, 1.0);
  for(int i = image.rows / 2 - 30; i < image.rows / 2 + 30 ; i++ ) {
    for(int j = image.cols / 2 - 30; j < image.cols / 2 + 30 ; j++ ) {
      mask.at<double>(i, j) = 0.0;
    }
  }
  planes[0] = (planes[0]).mul(mask);
  planes[1] = (planes[1]).mul(mask);

  // do the inverse fftshift
  fftshift(planes[0], planes[1]);
  merge(planes, 2, complex);

  // do the inverse dft
  Mat output;
  idft(complex, output);

  // calculate the magnitude
  split(output, planes);
  magnitude(planes[0], planes[1], output);

  int kernels = image.rows * image.cols;
  output /= kernels;

  // write out the image
  write_image("../image_idft_filter.jpg", output); 

  return 0;
}