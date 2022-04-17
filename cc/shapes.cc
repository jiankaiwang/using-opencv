#include <iostream>
#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  string type1_path = "../../images/match1.jpg";
  Mat type1 = read_image(type1_path, true);
  if(type1.size().height == 0) {
    cerr << "Failed in opening the type1 image." << endl;
    return 1;
  }

  string type2_path = "../../images/match2.jpg";
  Mat type2 = read_image(type2_path, true);
  if(type2.size().height == 0) {
    cerr << "Failed in opening the type2 image." << endl;
    return 1;
  }

  string type3_path = "../../images/match3.jpg";
  Mat type3 = read_image(type3_path, true);
  if(type3.size().height == 0) {
    cerr << "Failed in opening the type image." << endl;
    return 1;
  }

  Mat type1_bin, type2_bin, type3_bin;
  threshold(type1, type1_bin, 127, 255, THRESH_BINARY);
  threshold(type2, type2_bin, 127, 255, THRESH_BINARY);
  threshold(type3, type3_bin, 127, 255, THRESH_BINARY);

  vector<vector<Point> > type1_contour, type2_contour, type3_contour;
  findContours(type1_bin, type1_contour, RETR_LIST, CHAIN_APPROX_SIMPLE);
  findContours(type2_bin, type2_contour, RETR_LIST, CHAIN_APPROX_SIMPLE);
  findContours(type3_bin, type3_contour, RETR_LIST, CHAIN_APPROX_SIMPLE);

  double t1_1, t1_2;
  t1_1 = matchShapes(type1_contour[0], type1_contour[0], CONTOURS_MATCH_I2, 0.0);
  t1_2 = matchShapes(type1_contour[0], type2_contour[0], CONTOURS_MATCH_I2, 0.0);

  cout << "MatchShapes between type1 and type1: " << t1_1 << endl;
  cout << "MatchShapes between type1 and type2: " << t1_2 << endl;

  return 0;
}