#include <iostream>
#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  string file_path = "../../images/rotated.jpg";
  Mat image = read_image(file_path, true);
  if(image.size().height == 0) {
    throw runtime_error("Failed to read the image at " + file_path + ".");
  }

  Mat thres_image;
  threshold(image, thres_image, 127, 255, THRESH_BINARY);

  vector<vector<Point> > contours;
  findContours(thres_image, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

  // fit the ellipse
  int max_area_index = get_max_area_contour_index(contours);
  RotatedRect rect;
  rect = fitEllipse(contours[max_area_index]);

  cout << "center:" << rect.center << endl;
  cout << "size:" << rect.size << endl;
  cout << "angle:" << rect.angle << endl;

  // draw the image
  ellipse(image, rect, Scalar(255, 255, 255), 2);
  write_image("../fitellipse.jpg", image);

  return 0;
}
