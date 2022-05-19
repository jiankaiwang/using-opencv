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

void fftshift(cv::Mat& reals, cv::Mat& imags) {
  int row_c = reals.rows / 2;
  int col_c = reals.cols / 2;

  cv::Mat reals_1(reals, cv::Rect(0, 0, row_c, col_c));
  cv::Mat reals_2(reals, cv::Rect(row_c, 0, row_c, col_c));
  cv::Mat reals_3(reals, cv::Rect(0, col_c, row_c, col_c));
  cv::Mat reals_4(reals, cv::Rect(row_c, col_c, row_c, col_c));

  cv::Mat temp;
  
  reals_1.copyTo(temp);
  reals_4.copyTo(reals_1);
  temp.copyTo(reals_4);

  reals_2.copyTo(temp);
  reals_3.copyTo(reals_2);
  temp.copyTo(reals_3);

  cv::Mat imags_1(imags, cv::Rect(0, 0, row_c, col_c));
  cv::Mat imags_2(imags, cv::Rect(row_c, 0, row_c, col_c));
  cv::Mat imags_3(imags, cv::Rect(0, col_c, row_c, col_c));
  cv::Mat imags_4(imags, cv::Rect(row_c, col_c, row_c, col_c));

  imags_1.copyTo(temp);
  imags_4.copyTo(imags_1);
  temp.copyTo(imags_4);

  imags_2.copyTo(temp);
  imags_3.copyTo(imags_2);
  temp.copyTo(imags_2);
}
}