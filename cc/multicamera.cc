#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  VideoCapture cap1(0);
  if(! cap1.isOpened()) {
    cerr << "Can't open the 1st camera." << endl;
    return 1;
  }

  VideoCapture cap2(1);
  if(! cap2.isOpened()) {
    cerr << "Can't open the 2nd camera." << endl;
    return 1;
  }

  Mat img1, img2;
  int key;
  while(cap1.isOpened() && cap2.isOpened()) {
    cap1.read(img1);
    cap2.read(img2);

    // for border
    cvtColor(img1, img1, COLOR_BGR2GRAY);
    Canny(img1, img1, 100, 200, 3);

    imshow("CAP1", img1);
    imshow("CAP2", img2);

    key = waitKey(5);
    if(key == 27) {
      break;
    }
  }

  cap1.release();
  cap2.release();
  destroyAllWindows();

  return 0;
}