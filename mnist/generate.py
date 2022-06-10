# -*- coding:utf8 -*-

import logging
logging.basicConfig(level=logging.INFO, 
                    format="%(asctime)s - %(levelname)s : %(message)s")

import os
import numpy as np

import cv2
logging.info("OpenCV version: {}".format(cv2.__version__))

import tensorflow as tf
logging.info("Tensorflow version: {}".format(tf.__version__))
logging.info("GPU is{} available.".format(\
  "" if tf.config.list_physical_devices("GPU") else " not"))

import tensorflow.keras as keras

# In[]

def selected_images(dataset, label, total_class=list(range(0, 10)), num_per_class=50):
  """Select the first N images whose IDs are identical."""
  try:
    cate_ids = np.array([], dtype=np.int32)
    label_ids = np.array([], dtype=np.int32)
    for cate in total_class:
      all_ids = np.where(label == cate)[0]
      selected_ids = all_ids[:num_per_class]
      cate_ids = np.concatenate([cate_ids, selected_ids])
      label_ids = np.concatenate([label_ids, np.repeat(cate, num_per_class)])
    all_imgs = dataset[cate_ids]
    return all_imgs, label_ids
  except Exception as err:
    logging.error("Failed in preparing the images. {}".format(err))
    return [], []

def generate_images(imgs, lbls, sub_path):
  """Try to generate the image to the local."""
  assert imgs.shape[0] == lbls.shape[0], \
    "The number of images is not equal to the one of labels."
  for lbl_idx in range(0, len(lbls.tolist())):
    try:
      lbl = lbls[lbl_idx]
      img = imgs[lbl_idx]
      file_path = os.path.join(sub_path, \
                    "{}{}.jpg".format(lbl, lbl_idx % 10))
      # print(file_path, img.shape)
      cv2.imwrite(file_path, img)
    except Exception as err:
      logging.error("Failed in generating the image. {}".format(file_path))

# In[]
if __name__ == "__main__":
  
  # get keras dataset
  mnist_folder = os.path.join('.', 'datasets')
  if not os.path.exists(mnist_folder):
    os.mkdir(mnist_folder)
    logging.warning("Created a folder at {}.".format(mnist_folder))

  # dataset: [N, 28, 28], label: [N]
  (train_dataset, train_label), (test_dataset, test_label) \
    = keras.datasets.mnist.load_data(mnist_folder)
  
  num_per_class = 20

  # for training set
  train_imgs, train_lbls = selected_images(\
    train_dataset, train_label, num_per_class=num_per_class)
  logging.info("Train image shape: {}, label shape: {}".format(\
    train_imgs.shape, train_lbls.shape))

  # for testing set
  test_imgs, test_lbls = selected_images(\
    test_dataset, test_label, num_per_class=1)
  logging.info("Test image shape: {}, label shape: {}".format(\
    test_imgs.shape, test_lbls.shape))
  
  # create folders
  paths = ['train', 'test']
  for path in paths:
    sub_path = os.path.join(mnist_folder, path)
    if not os.path.exists(sub_path):
      os.mkdir(sub_path, mode=777)
      logging.warning("Created a folder at {}.".format(sub_path))
  
    # write images
    if path == "train":
      generate_images(train_imgs, train_lbls, sub_path)
    else:
      generate_images(test_imgs, test_lbls, sub_path)
