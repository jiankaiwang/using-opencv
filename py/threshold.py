# -*- coding:utf-8 -*-

import logging
logging.basicConfig(level=logging.INFO, \
                    format="%(asctime)s - %(levelname)s : %(message)s")

import os
import cv2
logging.info("CV version: {}".format(cv2.__version__))

import helpers as h

# In[]

def adaptive_threshold(image_path):
  try:
    img_gray = h.read_image(file_path, to_gray=True)
    assert img_gray is not None

    img_adaptive_threshold = cv2.adaptiveThreshold(
      img_gray,                      # must be gray image
      255,                           # max value
      cv2.ADAPTIVE_THRESH_MEAN_C,    # adaptive type
      cv2.THRESH_BINARY,             # threshold type
      5,                             # block size, e.g. 3, 5, ..., etc.
      5)
    assert img_adaptive_threshold is not None
    h.write_image("./adaptive.jpg", img_adaptive_threshold)
  except Exception as err:
    logging.error("Failed in the adaptive threshold. {}".format(err))

def threshold_otsu(image_path):
  try:
    image = h.read_image(file_path, to_gray=True)
    assert image is not None

    state, image_otsu_threshold = cv2.threshold(
      image, 
      0,
      255,
      cv2.THRESH_BINARY + cv2.THRESH_OTSU
    )
    assert state

    h.write_image("./threshold.jpg", image_otsu_threshold)    
  except Exception as err:
    logging.error("Failed in thresholdng the image. {}".format(err))

# In[]

if __name__ == "__main__":
  
  file_path = os.path.join("..", "images", "lena.jpg")
  assert os.path.exists(file_path), \
    "Failed in finding the image at {}.".format(file_path)

  adaptive_threshold(file_path)
  threshold_otsu(file_path)
  