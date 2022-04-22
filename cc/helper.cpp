#include <iostream>
#include <cstdlib>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;

namespace std {
enum {
  CV_LOAD_IMAGE_UNCHANGED = 1, 
  CV_LOAD_IMAGE_GRAYSCALED = 0,
  CV_LOAD_IMAGE_COLOR = 1
};


cv::Mat read_image(string file_path, bool to_gray) {
  // read the image by using cv2
  try {
    int state = to_gray ? CV_LOAD_IMAGE_GRAYSCALED : CV_LOAD_IMAGE_COLOR;
    cv::Mat image = cv::imread(file_path, state);
    return image;
  } catch (exception e) {
    cerr << "Failed in opening the image." << e.what() << endl;
    return cv::Mat();
  }
}

void write_image(string file_path, cv::Mat image) {
  // write out the image
  try {
    cv::imwrite(file_path, image);
  } catch (exception e) {
    cerr << "Failed in writing the image out." << e.what() << endl;
  }
}

int get_max_area_contour_index(vector<vector<cv::Point> > &contours) {
  int max_idx = 0;
  float max_area = 0.0f;

  for(int i = 0 ; i < contours.size(); i++) {
    if(cv::contourArea(contours[i]) > max_area) {
      max_idx = i;
    }
  }

  return max_idx;
}
}