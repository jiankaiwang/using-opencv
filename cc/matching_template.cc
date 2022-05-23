#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  string image_path = "../../images/lena.jpg";
  Mat image = read_image(image_path, false);
  if(image.empty()) {
    cerr << "The image, " << image_path <<  ", can't be loaded." << endl;
    return 1;
  }

  string template_path = "../../images/face.jpg";
  Mat tpl = read_image(template_path, false);
  if(tpl.empty()) {
    cerr << "The image, " << template_path <<  ", can't be loaded." << endl;
    return 1;
  }

  // blur the template first
  Mat tpl_blur;
  blur(tpl, tpl_blur, Size(5, 5));
  // write_image("../tpl_blur.jpg", tpl_blur);

  // use the blurring image to search the pattern in the image
  Mat result;
  matchTemplate(image, tpl_blur, result, TM_CCOEFF_NORMED);
  cout << "Total size of the compare: " << result.size() << endl;

  // find the the best one
  double minVal = 0, maxVal = 0;
  Point minLoc, maxLoc;
  minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
  cout << "Max similarity: " << maxVal << endl;
  cout << "Min similarity: " << minVal << endl;
  cout << "Best Loc: " << maxLoc << endl;
  cout << "Worst Loc: " << minLoc << endl;

  // plot the best one
  Point rect2;
  rect2.x = maxLoc.x + tpl_blur.cols;
  rect2.y = maxLoc.y + tpl_blur.rows;
  rectangle(image, maxLoc, rect2, Scalar(255, 0, 0), 2);
  write_image("../matching.jpg", image);

  return 0;
}