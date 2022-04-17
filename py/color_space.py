# -*- coding:utf8 -*-

"""
The color space is helpful for the different systems, and for attribute analyses.
The basic idea behind extracting human skin is by converting among color spaces.
The human skin in HSV color space, its H value is in the range [5, 170] and its
saturation is in the range [25, 166].
"""

import logging
logging.basicConfig(level=logging.INFO, 
                    format="%(asctime)s - %(levelname)s : %(message)s")

import os
import numpy as np
import cv2
import helpers as h

# In[]

def extract_on_hs(image_numpy_array):
  try:
    h, s, v = cv2.split(image_numpy_array)
    minHue, maxHue = 5, 170
    h_mask = cv2.inRange(h, minHue, maxHue)
    minSat, maxSat = 25, 166
    s_mask = cv2.inRange(s, minSat, maxSat)
    mask = cv2.bitwise_and(h_mask, s_mask)
    extracted_image = cv2.bitwise_and(image_numpy_array, image_numpy_array, mask=mask)
    return extracted_image
  except Exception as err:
    logging.error("Failed in converting the image to the HSV color space. {}".format(err))
    return None

def increase_brightness(image_numpy_array):
  try:
    h, s, v = cv2.split(image_numpy_array)
    v[:,:] = 255
    return cv2.merge([h, s, v])
  except Exception as err:
    logging.error("Failed in converting the image to the HSV color space. {}".format(err))
    return None  

# In[]

if __name__ == "__main__":
  
  file_path = os.path.join("..", "images", "lena.jpg")
  assert os.path.exists(file_path), \
    "Failed in finding the image at {}.".format(file_path)

  # for reproduction
  np.random.seed(0)

  img = h.read_image(file_path, to_HSV=True)
  assert img is not None

  extracted_img = increase_brightness(img)
  assert extracted_img is not None
  extracted_img = cv2.cvtColor(extracted_img, cv2.COLOR_HSV2BGR)
  _ = h.write_image("./test.jpg", extracted_img)


