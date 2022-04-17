#include <iostream>
#include <cstdlib>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;

namespace std {
cv::Mat read_image(string file_path, bool to_gray);
void write_image(string file_path, cv::Mat image);
}