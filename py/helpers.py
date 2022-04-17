# -*- coding:utf8 -*-

import logging
import os
import numpy as np
import cv2

# In[]

def read_image(image_path, 
               to_RGB=False, 
               to_HSV=False,
               resize=None,
               to_gray=False):
  try:
    img_mode = 0 if to_gray else 1
    img = cv2.imread(image_path, img_mode)
    if resize is not None and type(resize) in [list, tuple]:
      img = cv2.resize(img, (resize))
    if to_RGB:
      img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    elif to_HSV:
      img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    return img
  except Exception as err:
    logging.error("Failed in readin the image at {}. {}".format(image_path, err))
    return None

def write_image(image_path, image_array):
  try:
    cv2.imwrite(image_path, image_array)
    return True
  except Exception as err:
    logging.error("Failed in writing out the image at {}. {}".format(image_path, err))
    return False
