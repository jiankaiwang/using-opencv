# -*- coding:utf8 -*-

"""
In the following, we demo several useful examples for manipulating the image.
"""

import logging
logging.basicConfig(level=logging.INFO, 
                    format="%(asctime)s - %(levelname)s : %(message)s")

import os
import numpy as np
import cv2
import helpers as h

# In[]

def image_filp(image_numpy_array, 
               flip_type='h'):
  try:
    assert flip_type in ['h', 'v']
    if flip_type == 'h':
      f_type = 1
    elif flip_type == 'v':
      f_type = 0
    elif flip_type == 'a':
      f_type = -1
    else:
      raise ValueError("{} is not supported.".format(flip_type))
    return cv2.flip(image_numpy_array, f_type)
  except Exception as err:
    logging.error("Failed in do the flip on the image. {}".format(err))
    return None

def image_resize(image_numpy_array, 
                 size=None):
  try:
    if type(size) not in [list, tuple]:
      raise ValueError("One of list or tuple is only allowed for size. ({})".format(type(size)))
    if len(size) != 2:
      raise ValueError("The number of dimension of size must be equal to 2. ({})".format(len(size)))
    return cv2.resize(image_numpy_array, size)
  except Exception as err:
    logging.error("Failed in resizing the image. {}".format(err))
    return None

def image_rotate(image_numpy_array, 
                 center=None, 
                 angle=None, 
                 scale=None):
  try:
    if angle is None:
      raise ValueError("The angle can't be None.")
    h, w, _ = image_numpy_array.shape      
    if center is None:
      center_x, center_y = w / 2.0, h / 2.0
    if scale is None:
      scale = 1.0
    rotMat = cv2.getRotationMatrix2D((center_x, center_y), angle, scale)
    return cv2.warpAffine(image_numpy_array, rotMat, (w, h))
  except Exception as err:
    logging.error("Failed in rotating the image. {}".format(err))
    return None

def image_perspective(image_numpy_array, 
                      src_coord=None, 
                      dst_coord=None):
  try:
    if src_coord is None or dst_coord is None:
      raise ValueError("The src_coord and dst_coord must be a list or tuple.")
    h, w, _ = image_numpy_array.shape
    perMat = cv2.getPerspectiveTransform(src_coord, dst_coord)
    return cv2.warpPerspective(image_numpy_array, perMat, (w, h))
  except Exception as err:
    logging.error("Failed in do the perspective operation on the image.")
    return None

# In[]

if __name__ == "__main__":
  
  file_path = os.path.join("..", "images", "lena.jpg")
  assert os.path.exists(file_path), \
    "Failed in finding the image at {}.".format(file_path)

  # for reproduction
  np.random.seed(0)

  image = h.read_image(file_path)
  assert image is not None

  h_image = image_filp(image, 'h')
  assert h_image is not None
  _ = h.write_image("image_h.jpg", h_image)

  v_image = image_filp(image, 'v')
  assert v_image is not None
  resized_image = image_resize(v_image, (100, 100))
  _ = h.write_image("ver_resize_test.jpg", resized_image)

  r_image = image_rotate(image, center=None, angle=60, scale=1.0)
  assert r_image is not None
  _ = h.write_image("rotated.jpg", r_image)

  # notice the coordinates on perspective are [h, w]
  src_coord = np.array([[0,0], [200, 0], [200, 200], [0, 200]], dtype=np.float32)
  dst_coord = np.array([[75, 50], [125, 50], [200, 150], [0, 150]], dtype=np.float32)
  p_image = image_perspective(image, src_coord, dst_coord)
  assert p_image is not None
  _ = h.write_image("perspective.jpg", p_image)
