#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

namespace std {
cv::Mat read_image(string file_path, bool to_gray);
void write_image(string file_path, cv::Mat image);
int get_max_area_contour_index(vector<vector<cv::Point> > &contours);
}