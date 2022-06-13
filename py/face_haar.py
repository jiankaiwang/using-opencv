# -*- coding:utf8 -*-

import logging
logging.basicConfig(level=logging.INFO, 
                    format="%(asctime)s - %(levelname)s : %(message)s")
import os
import time
import numpy as np
import cv2

# In[]
if __name__ == "__main__":

  image_path = "../images/lena.jpg"
  image = cv2.imread(image_path, cv2.IMREAD_UNCHANGED)
  assert image.ndim == 3, \
    "Failed in reading the image at {}.".format(image_path)

  frontalface_xml = "../opencv/data/haarcascades/haarcascade_frontalface_default.xml"
  assert os.path.exists(frontalface_xml), \
    "The file {} was not found.".format(frontalface_xml)

  # create a Haar cascade classifier
  detector = cv2.CascadeClassifier(frontalface_xml)

  # detect a face
  scaled_factor = 1.5
  min_neighbor = 5
  min_size = (50, 50)
  start = time.perf_counter()
  objects = detector.detectMultiScale(image, scaled_factor, min_neighbor, 0, min_size)
  peroid = time.perf_counter() - start
  logging.info("Number of faces detected: {} in {:.4f} ms".format(
    len(objects), peroid))

  # draw faces on image
  for i in range(len(objects)):
    x, y, w, h = objects[i]
    x2, y2 = x + w, y + h
    line_width = ((i) % 5) + 1
    cv2.rectangle(image, (x, y), (x2, y2), (0, 0, 0), line_width)
  cv2.imwrite("./haar_face.jpg", image)

