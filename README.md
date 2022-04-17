# Using OpenCV 

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
- Contour and masking [contour.cc](cc/contour.cc)
  - Get the contours.
  - Get the area and arclength of contours.
  - Matching shapes based on the contour. [shapes.cc](cc/shapes.cc)
  - Fitting shapes based on the contour. [fitshapes.cc](cc/fitshapes.cc)
  - Convex and Hull. [convex.cc](cc/convex.cc)

