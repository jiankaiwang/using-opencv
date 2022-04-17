#include <iostream>
#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

int get_max_contour(vector<vector<Point> > &contours) {
  int max_idx = 0;
  double max_area = 0.0, tmp_area = 0.0;
  for(int i = 0 ; i < contours.size() ; i++) {
    tmp_area = contourArea(contours[i]);
    if(tmp_area > max_area) {
      max_area = tmp_area;
      max_idx = i;
    }
  }
  cout << "Max index: " << max_idx << ", its area: " << max_area << endl;
  return max_idx;
}

void smallest_rect(string& rotated_path) {
  Mat rotated = read_image(rotated_path, true);
  if(rotated.size().height == 0) {
    cerr << "Failed in opening the rotated image." << endl;
    return;
  }

  Mat img_bin;
  threshold(rotated, img_bin, 127, 255, THRESH_BINARY);

  vector<vector<Point> > contours;
  findContours(img_bin, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

  // get the largest contour
  cout << "There are " << contours.size() << " contours." << endl;

  int max_idx = get_max_contour(contours);

  // min rect area
  RotatedRect results = minAreaRect(contours[max_idx]);

  cout << "The angle: " << results.angle << endl;
  
  vector<Point2f> boxPts(4);
  vector<Point> boxPts_not_f;  // in order to explictly transform from Point2f to Point
  results.points(boxPts.data());
  cout << "The number of points: " << boxPts.size() << endl;
  for(int i = 0 ; i < boxPts.size() ; i++) {
    cout << "index " << i << " : " << boxPts[i] << endl;
    boxPts_not_f.push_back(boxPts[i]);  // for using drawContour
  }

  // // draw rect
  vector<vector<Point> > boxRes;
  boxRes.push_back(boxPts_not_f);
  drawContours(rotated, boxRes, 0, Scalar(255, 255, 255), 1);
  write_image("../minRectArea.jpg", rotated);
}

void find_ellipse(string &rotated_path) {
  Mat rotated = read_image(rotated_path, true);
  if(rotated.size().height == 0) {
    cerr << "Failed in opening the rotated image." << endl;
    return;
  }

  Mat img_bin;
  threshold(rotated, img_bin, 127, 255, THRESH_BINARY);

  vector<vector<Point> > contours;
  findContours(img_bin, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

  int max_idx = get_max_contour(contours);

  // find the parameters for ellipse
  RotatedRect ellipse_res = fitEllipse(contours[max_idx]);

  // draw the ellipse
  ellipse(rotated, ellipse_res, Scalar(255, 255, 255), 1);

  write_image("../ellipse.jpg", rotated);
}

void fit_poly_dp(string &rotated_path) {
  Mat rotated = read_image(rotated_path, true);
  if(rotated.size().height == 0) {
    cerr << "Failed in opening the rotated image." << endl;
    return;
  }

  Mat img_bin;
  threshold(rotated, img_bin, 127, 255, THRESH_BINARY);

  vector<vector<Point> > contours;
  findContours(img_bin, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

  int max_idx = get_max_contour(contours);

  // calculate the epsilson for the threshold
  double contour_length = arcLength(contours[max_idx], true);
  double epsillon = 0.02 * contour_length;
  cout << "The epsillon is " << epsillon << "." << endl;

  // get the approx information
  vector<Point> results;
  approxPolyDP(contours[max_idx], results, epsillon, true);
  cout << "There are " << results.size() << " points." << endl;

  // draw contour
  vector<vector<Point> > res;
  res.push_back(results);
  drawContours(rotated, res, 0, Scalar(255, 0, 0), 2);

  write_image("../approx_dp.jpg", rotated);

}

int main(int argc, char* args[]) {

  string rotated_path = "../../images/cloud.jpg";
  smallest_rect(rotated_path);
  find_ellipse(rotated_path);
  fit_poly_dp(rotated_path);

  return 0;
}