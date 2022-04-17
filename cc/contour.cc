#include <iostream>
#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  string file_path = "../../images/symbol.jpg";

  Mat image = read_image(file_path, true);
  if(image.size().height == 0) {
    throw runtime_error("Failed in opening the image.");
  }

  Mat threshold_image;
  threshold(image, threshold_image, 127, 255, THRESH_BINARY);

  // find contour
  // Mat contours, hierarchy;
  // RETR_EXTERNAL only for the outline
  // CHAIN_APPROX_TC89_KCOS: approximation approach
  vector<vector<Point> > contours;
  findContours(threshold_image, contours, RETR_LIST, CHAIN_APPROX_TC89_KCOS);

  // blank image
  Mat blank = Mat(image.size().height, image.size().width, CV_64F, 0.0);

  // draw contour
  // -1 for all contours
  // Scalar(100,100,100) for color
  // 1 for thickness
  drawContours(blank, contours, -1, Scalar(255,255,255), 1);
  write_image("../drawContour.jpg", blank);

  // calculate the contour's area and length
  cout << "There are " << contours.size() << " contours." << endl;
  stringstream ss;
  for(int i = 0 ; i < contours.size() ; i++) {
    Moments mnt = moments(contours[i]);
    if(contourArea(contours[i]) > 1000) {
      cout << "  Contour " << i << "'s area: " << mnt.m00 << " , area: "<< contourArea(contours[i]);
      cout << "  , length: " << arcLength(contours[i], true) << endl;
      
      blank = Mat(image.size().height, image.size().width, CV_64F, 0.0);
      vector<vector<Point> > contoursList;
      contoursList.push_back(contours[i]);
      drawContours(blank, contoursList, -1, Scalar(255,255,255), 1);

      ss.str("");
      ss << "../drawContour_" << i << ".jpg";
      write_image(ss.str(), blank);
    }
  }

  return 0;
}