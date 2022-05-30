#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "helper.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

  // open the camera
  int video_id = 1;
  VideoCapture cap(video_id);
  if(! cap.isOpened()) {
    cerr << "Failed in opening the camera." << endl;
  }
  
  // get the camera's properities
  int frame_width = cap.get(CAP_PROP_FRAME_WIDTH), 
      frame_height = cap.get(CAP_PROP_FRAME_HEIGHT), 
      fps = cap.get(CAP_PROP_FPS);
  cout << "FPS: " << fps << endl;
  cout << "W x H: " << frame_width << " x " << frame_height << endl;
  cout << "Brightness: " << cap.get(CAP_PROP_BRIGHTNESS) << endl;
  cout << "Focus: " << cap.get(CAP_PROP_FOCUS) << endl;
  cout << "Encoding: " << cap.get(CAP_PROP_FOURCC) << endl;
  cout << "Exposure: " << cap.get(CAP_PROP_EXPOSURE) << endl;
  cout << "White balancing (blue_u): " << cap.get(CAP_PROP_WHITE_BALANCE_BLUE_U) << endl;
  cout << "White balancing (red_v): " << cap.get(CAP_PROP_WHITE_BALANCE_RED_V) << endl;

  // read and write the camera streaming
  bool success;
  Mat capture;
  int key;
  VideoWriter out;
  out.open("../border001.avi", 
           VideoWriter::fourcc('M', 'J', 'P', 'G'),
           fps, 
           Size(frame_width, frame_height), 
           true);
  if(! out.isOpened()) {
    cerr << "Failed in opening the output file." << endl;
  }
  while(cap.isOpened() && out.isOpened()) {
    success = cap.read(capture);
    if(success) {
      imshow("capture", capture);
      out.write(capture);
    }
    // 5 for 5ms for waiting the key
    key = waitKey(5);
    if(key == 27) {
      // ESC
      break;
    }
  }

  cap.release();
  out.release();
  destroyAllWindows();

  return 0;
}