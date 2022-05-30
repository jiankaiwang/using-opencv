#include <iostream>
#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

void set_marks(Mat &masking, Mat& marks) {
  for(int i = 0 ; i < masking.rows; i ++) {
    for(int j = 0 ; j < masking.cols; j++) {
      if(masking.at<uint8_t>(i, j) == 2 || masking.at<uint8_t>(i, j) == 0) {
        marks.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
      } else {
        marks.at<Vec3b>(i, j) = Vec3b(1, 1, 1);
      }
    }
  }
}

int main(int argc, char* args[]) {
  
  string image_path = "../../images/lena.jpg";
  Mat image = read_image(image_path, false);
  if(image.empty()) {
    cerr << "Failed in opening the image." << endl;
    return 1;
  }

  // for masking
  string mask_path = "../../images/lena_mask.jpg";
  Mat mask = read_image(mask_path, false);
  if(mask.empty()) {
    cerr << "Failed in opening the masking image." << endl;
    return 1;
  }  

  Rect rect(15, 13, 155, 187);
  Mat bgdModel, fgdModel;  

  // step.1: use the default, GC_INIT_WITH_RECT
  Mat masking = Mat(mask.size().height, mask.size().width, CV_8U, Scalar(0));
  grabCut(image, masking, rect, bgdModel, fgdModel, 5, GC_INIT_WITH_RECT);
  Vec3b tmp;
  for(int i = 0 ; i < mask.rows; i ++) {
    for(int j = 0 ; j < mask.cols; j++) {
      tmp = mask.at<Vec3b>(i,j);
      if(tmp[0] == 0 && tmp[1] == 0 && tmp[2] == 0) {
        masking.at<uint8_t>(i, j) = 0;
      } else if (tmp[0] == 255 && tmp[1] == 255 && tmp[2] == 255) {
        masking.at<uint8_t>(i, j) = 1;
      }
    }
  }
  Mat marks = Mat(mask.size().height, mask.size().width, CV_8UC3, Scalar(0, 0, 0));
  set_marks(masking, marks);

  Mat rect_tmpl;
  multiply(image, marks, rect_tmpl);
  write_image("../rectangle_template.jpg", rect_tmpl);

  // step.2: use with the mask, GC_INIT_WITH_MASK
  // notice here we combine both GC_INIT_WITH_RECT and GC_INIT_WITH_MASK
  grabCut(image, masking, rect, bgdModel, fgdModel, 5, GC_INIT_WITH_MASK);
  marks = Mat(mask.size().height, mask.size().width, CV_8UC3, Scalar(0, 0, 0));
  set_marks(masking, marks);

  Mat segmentation;
  multiply(image, marks, segmentation);
  write_image("../segmentation.jpg", segmentation);

  return 0;
}