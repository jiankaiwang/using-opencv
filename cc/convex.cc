#include <iostream>
#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  string image_path = "../../images/cloud.jpg";
  Mat image = read_image(image_path, true);
  if(image.size().height == 0) {
    cerr << "Failed in reading the image." << endl;
  }

  Mat img_bin;
  threshold(image, img_bin, 127, 255, THRESH_BINARY);

  vector<vector<Point> > contours;
  findContours(img_bin, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

  // find the convex points
  Mat hull;
  convexHull(contours[0], hull);

  // draw lines by points
  polylines(image, hull, true, Scalar(255, 255, 255));
  write_image("../convex.jpg", image);

  // calculate the distance to the convex
  float dist1 = pointPolygonTest(hull, Point2f(300, 150), true);
  cout << "Distince from " << Point2f(300, 150) << " to the convex is " << dist1 << "." << endl;

  putText(image, "A", Point2f(300, 150), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), true);
  write_image("../convex_A.jpg", image);

  return 0;
}