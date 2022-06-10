# Using OpenCV 

![](https://img.shields.io/static/v1?label=OpenCV&message=4.5.5&color=blue)

The repository demonstrates how to use OpenCV.

## Environment

If you use Python, you can install the package by using `pip3 install opencv-python`.

```sh
python3 -m virtualenv -p python3 env
source ./env/bin/activate
pip3 install opencv-python
```

If you use C++, you can build up the OpenCV library first. After building the library, you can setup the OpenCV path to the `CMakeLists.txt` under the `cc` path.

```sh
git clone https://github.com/opencv/opencv.git
cd ./opencv
mkdir ./build
cmake ..
cmake --build .
```

## Topics

- XOR bitwise operation for encrypting images: [bitwise.py](py/bitwise.py)
- BGR to HSV convertion for converting among color spaces: [color_space.py](py/color_space.py)
- Do the transforms on the image. [transforms.py](py/transforms.py)
- Threshold (/w adaptive) on the image. [threshold.py](py/threshold.py)
- Image blurring [blurring.cc](cc/blurring.cc)
- Image morphology for border [morphology.cc](cc/morphology.cc)
- Image gradient by using Sobel, Scharr, and Laplacian. [gradient.cc](cc/gradient.cc)
- Canny for border [canny.cc](cc/canny.cc)
- Down- and up-sampling of image [pyramids.cc](cc/pyramids.cc)
- Contour and masking 
  - Get the contours. [contour.cc](cc/contour.cc)
  - Get the area and arclength of contours. [contour.cc](cc/contour.cc)
  - Matching shapes based on the contour. [shapes.cc](cc/shapes.cc)
  - Fitting shapes based on the contour. [fitshapes.cc](cc/fitshapes.cc)
  - Convex and Hull. [convex.cc](cc/convex.cc)
  - Fit ellipse. [ellipse.cc](cc/ellipse.cc)
- Fast Fourier Transformation
  - The numpy version. [image_fft.py](py/image_fft.py)
  - The high-pass filter. [fft_high_pass.py](py/fft_high_pass.py)
  - The OpenCV version. [image_dft.cc](cc/image_dft.cc), [image_dft.py](py/image_dft.py)
  - Building filters in OpenCV. [dft_filters.cc](cc/dft_filters.cc)
- Matching template: [cc/matching_template.cc](cc/matching_template.cc)
- Hough Transformation. [cc/hough_transformation.cc](cc/hough_transformation.cc)
- Image Segmentation.
  - Watershed. [cc/watershed.cc](cc/watershed.cc)g
  - GrabCut. [cc/grabcut.cc](cc/grabcut.cc)
- Video
  - Capturing the video, and writing it. [cc/videorw.cc](cc/videorw.cc)
  - Multiple cameras. [cc/multicamera.cc](cc/multicamera.cc)
- Image Classification
  - K Nearest Neighbor (KNN) [py/knn.py](py/knn.py)
  - Support Vector Machine (SVM) [py/svm.py](py/svm.py)
  - K means [py/kmeans.py](py/kmeans.py)