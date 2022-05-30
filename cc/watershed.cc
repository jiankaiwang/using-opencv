#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

void set_mat(Mat &set_mat, int val) {
  for(int i = 0; i < set_mat.rows; i++) {
    for(int j = 0; j < set_mat.cols; j++) {
      if(set_mat.at<int>(i,j) + val <= 255) {
        set_mat.at<int>(i,j) += val;
      } else {
        set_mat.at<int>(i,j) = 255;
      }
    }
  }
}

void set_mat_element_value(Mat &set_mat, Mat &ref_mat, uint8_t val, int set_val) {
  for(int i = 0; i < set_mat.rows; i++) {
    for(int j = 0; j < set_mat.cols; j++) {
      if(ref_mat.at<uint8_t>(i,j) == val) {
        set_mat.at<int>(i,j) = set_val;
      }
    }
  }
}

void set_image_element_value(Mat &set_mat, Mat &ref_mat, int val, Vec3b set_val) {
  for(int i = 0; i < set_mat.rows; i++) {
    for(int j = 0; j < set_mat.cols; j++) {
      if(ref_mat.at<int>(i,j) == val) {
        set_mat.at<Vec3b>(i,j) = set_val;
      }
    }
  }
}


int main(int argc, char* args[]) {

  string image_path = "../../images/water_coins.jpg";
  Mat image = read_image(image_path, false);
  if(image.empty()) {
    cerr << "Failed in opening the image." << endl;
    return 1;
  }
  
  Mat image_gray; 
  cvtColor(image, image_gray, COLOR_BGR2GRAY);

  Mat image_gray_threshold;
  threshold(image_gray, image_gray_threshold, 127, 255, THRESH_BINARY_INV + THRESH_OTSU);

  Mat image_opening;
  float kernels[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  Mat kernel = cv::Mat(3, 3, CV_32F, kernels);
  morphologyEx(image_gray_threshold, image_opening, MORPH_OPEN, kernel);
  write_image("../morph_opening.jpg", image_opening);

  Mat sure_bg;
  dilate(image_opening, sure_bg, kernel, Point(-1, -1), 2);
  write_image("../sure_background.jpg", sure_bg);

  Mat image_dist;
  distanceTransform(image_opening, image_dist, DIST_L2, 5);

  // sure foreground
  Mat sure_fg;
  double maxVal;
  minMaxLoc(image_dist, NULL, &maxVal, NULL, NULL);
  // 0.7 is an experiencing value
  threshold(image_dist, sure_fg, maxVal * 0.7, 255, 0);
  write_image("../sure_foreground.jpg", sure_fg);

  // unknown: Mat<uint8_t>
  Mat unknown;
  sure_bg.convertTo(sure_bg, CV_8UC1);
  sure_fg.convertTo(sure_fg, CV_8UC1);
  subtract(sure_bg, sure_fg, unknown);
  write_image("../unknown.jpg", unknown);

  // connected labelling, markers: Mat<int>
  Mat markers;
  connectedComponents(sure_fg, markers);

  // add 1 to all markers so that the sure background is 1, not 0
  set_mat(markers, 1);
  write_image("../markers.jpg", markers);
  
  // mark the region of unknown with 0
  set_mat_element_value(markers, unknown, 255, 0);
  write_image("../mask_unknown.jpg", markers);

  // watershed, use vec3b to mark with the color
  watershed(image, markers);
  set_image_element_value(image, markers, -1, Vec3b(255, 0, 0));
  write_image("../watershed.jpg", image);

  return 0;
}