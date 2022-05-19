# -*- coding:utf8 -*-

import os
import cv2
import numpy as np

if __name__ == "__main__":
  
  img_path = "../images/lena.jpg"
  assert  os.path.exists(img_path), \
    "The image path {} was not found.".format(img_path)
  img = cv2.imread(img_path, 0)
  assert img.ndim == 2

  # do the 2-dim FFT
  img_fft = np.fft.fft2(img)

  # move the frequency 0 from the top and left to the middle of the image
  # just like in signal, move from [0, ts] to [-ts/2, ts/2]
  img_shift = np.fft.fftshift(img_fft)

  # use the abs to get the absolute value of the fft
  img_fft_abs = np.abs(img_shift)

  # you can have a look at the output image
  cv2.imwrite("./fft.jpg", img_fft_abs)

  # reshift first
  img_ifftshift = np.fft.ifftshift(img_shift)

  # reverse the fft
  img_ifft = np.fft.ifft2(img_ifftshift)

  img_ifft_abs = np.abs(img_ifft)

  # this result should be the gray-scaled one from the original image
  cv2.imwrite("./ifft.jpg", img_ifft_abs)


