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

  rows, cols = img.shape
  row_c = int(rows / 2)
  col_c = int(cols / 2)

  # do the 2-dim FFT
  img_fft = np.fft.fft2(img)

  # move the frequency 0 from the top and left to the middle of the image
  # just like in signal, move from [0, ts] to [-ts/2, ts/2]
  img_shift = np.fft.fftshift(img_fft)

  # use the abs to get the absolute value of the fft
  img_fft_abs = np.abs(img_shift)

  cv2.imwrite("./fft.jpg", img_fft_abs)

  # filter out the low frequency parts
  # that means to keep the boundary
  size = 30
  img_shift[row_c-size:row_c+size, col_c-size:col_c+size] = 0.0 + 0.0j

  cv2.imwrite("./fft_hp.jpg", np.abs(img_shift))

  img_ifftshift = np.fft.ifftshift(img_shift)
  img_ifft = np.fft.ifft2(img_ifftshift)
  img_ifft_abs = np.abs(img_ifft)

  cv2.imwrite("./ifft_high_pass.jpg", img_ifft_abs)


