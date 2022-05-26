#include <iostream>
#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  string image_path = "../../images/symbol.jpg";
  Mat image = read_image(image_path, false);
  if(image.empty()) {
    cerr << "Can't open the image." << endl;
    return 1;
  }

  Mat image_gray;
  cvtColor(image, image_gray, COLOR_BGR2GRAY);

  // detecting the edge
  Mat image_edge;
  Canny(image, image_edge, 50, 200, 3);

  vector<Vec4i> linesP;
  HoughLinesP(image_edge, linesP, 1, CV_PI/180, 1, 100, 10);
  cout << linesP.size() << endl;

  for(size_t i = 0 ; i < linesP.size(); i ++) {
    Vec4i l = linesP[i];
    line(image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, LINE_AA);
  }

  write_image("../houghline.jpg", image);

  return 0;
}