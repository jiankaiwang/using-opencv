#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argv, char* args[]) {

  string file_path = "../../images/lena.jpg";

  Mat image = read_image(file_path, true);
  if(image.size().height == 0) {
    cerr << "Failed in reading the image." << endl;
  }

  // sobel operations for image gradients
  Mat sobel_x, sobel_y, sobel_grad;
  Sobel(image, sobel_x, CV_64F, 1, 0);  // G_x
  Sobel(image, sobel_y, CV_64F, 0, 1);  // G_y
  convertScaleAbs(sobel_x, sobel_x);
  convertScaleAbs(sobel_y, sobel_y);
  addWeighted(sobel_x, 0.5, sobel_y, 0.5, 0, sobel_grad);
  write_image("../sobel.jpg", sobel_grad);

  // scharr operations for image gradients
  Mat scharr_x, scharr_y, scharr_grad;
  Scharr(image, scharr_x, CV_64F, 1, 0);
  Scharr(image, scharr_y, CV_64F, 0, 1);
  convertScaleAbs(scharr_x, scharr_x);
  convertScaleAbs(scharr_y, scharr_y);
  addWeighted(scharr_x, 0.5, scharr_y, 0.5, 0, scharr_grad);
  write_image("../scharr.jpg", scharr_grad);

  // laplacian operations for image gradients
  Mat laplacian_grad;
  Laplacian(image, laplacian_grad, CV_64F);
  convertScaleAbs(laplacian_grad, laplacian_grad);
  write_image("../laplacian.jpg", laplacian_grad);

  return 0;
}