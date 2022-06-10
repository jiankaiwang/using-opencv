# -*- coding:utf8 -*-

import logging
logging.basicConfig(level=logging.INFO, 
                    format="%(asctime)s - %(levelname)s : %(message)s")

import os
import numpy as np
import cv2
logging.info("CV version: {}".format(cv2.__version__))

# In[]
if __name__ == "__main__":

  image_path = "../images/lena.jpg"
  assert os.path.exists(image_path), \
    "The image {} was not found.".format(image_path)

  ori_image = cv2.imread(image_path)
  logging.info("Image shape: {}".format(ori_image.shape))

  image = np.reshape(ori_image, (-1, 3)).astype(np.float32)
  logging.info("New image shape: {}".format(image.shape))
  logging.info("Image dtype: {}".format(image.dtype))

  # create a Kmeans cluster model
  criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)
  num_clusters = 8
  rets, classes, centers = cv2.kmeans(image, num_clusters, None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)
  logging.info("Returns: {}".format(rets))
  logging.info("Classes' shape: {}".format(classes.shape))
  logging.info("Clusters' centers: {}".format(centers))

  classes = np.reshape(classes, (200, 200))

  # draw an new image with new clusters' centers
  container = centers[classes]
  container = container.astype(np.uint8)
  logging.info("Clustered image shape: {}".format(container.shape))

  cv2.imwrite("./kmeans.jpg", container)

