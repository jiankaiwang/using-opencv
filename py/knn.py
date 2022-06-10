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

  file_folder = "../mnist/datasets"
  assert os.path.exists(file_folder), \
    "Can't find the folder at {}.".format(file_folder)
  train_folder = os.path.join(file_folder, "train")
  train_files = next(os.walk(train_folder))[2]
  logging.info("There are {} train files.".format(len(train_files)))

  # data processing and labeling
  kernel_size = (7, 7)
  image_shape = (28, 28)
  num_kernel = (int(image_shape[0]/kernel_size[0]), int(image_shape[1]/kernel_size[1]))
  train_images = np.zeros(
    shape=(len(train_files), num_kernel[0], num_kernel[1]),
    dtype=np.float32)
  train_labels = np.zeros(
    shape=(len(train_files), ), 
    dtype=np.int32)
  
  for i in range(len(train_files)):
    image_name = os.path.basename(train_files[i])
    image_cate, image_index = str(image_name.split('.')[0])
    image_cate = np.int32(image_cate)

    image_path = os.path.join(train_folder, train_files[i])
    image_content = cv2.imread(image_path, cv2.COLOR_BGR2GRAY)
    image_content = cv2.threshold(image_content, 127, 255, cv2.THRESH_BINARY)[1]
    for r in range(0, image_shape[0]):
      for c in range(0, image_shape[1]):
        if image_content[r][c] == 255:
          ri = int(r / kernel_size[0])
          ci = int(c / kernel_size[1])
          train_images[i][ri][ci] += 1
    
    train_labels[i] = image_cate

  # train the model
  knn = cv2.ml.KNearest_create()
  # data transformations
  train_images = train_images.reshape(len(train_files), num_kernel[0] * num_kernel[1])
  knn.train(train_images, cv2.ml.ROW_SAMPLE, train_labels)  

  # evaluate the test image
  test_foler = os.path.join(file_folder, "test")
  test_files = next(os.walk(test_foler))[2]
  logging.info("There are {} test files.".format(len(test_files)))

  test_images = np.zeros(
    shape=(len(test_files), num_kernel[0], num_kernel[1]),
    dtype=np.float32)
  test_labels = np.zeros(
    shape=(len(test_files), ), 
    dtype=np.int32)
  
  for i in range(len(test_files)):
    image_name = os.path.basename(test_files[i])
    image_cate, image_index = str(image_name.split('.')[0])
    image_cate = np.int32(image_cate)

    image_path = os.path.join(test_foler, test_files[i])
    image_content = cv2.imread(image_path, cv2.COLOR_BGR2GRAY)
    image_content = cv2.threshold(image_content, 127, 255, cv2.THRESH_BINARY)[1]
    for r in range(0, image_shape[0]):
      for c in range(0, image_shape[1]):
        if image_content[r][c] == 255:
          ri = int(r / kernel_size[0])
          ci = int(c / kernel_size[1])
          test_images[i][ri][ci] += 1
    
    test_labels[i] = image_cate

  test_images = test_images.reshape(len(test_files), num_kernel[0] * num_kernel[1])

  for i in range(len(test_files)):
    state, result, neighbors, dist = knn.findNearest(test_images[i:i+1], k=5)
    print("----------------------")
    if state:
      print("True Category: {}".format(test_labels[i]))
      print("Predicted Category: {}".format(result))
      print("Neigbor Index: {}".format(neighbors))
      print("Distance: {}".format(dist))
    else:
      print("{}: state {}".format(i, state))
