# -*- coding:utf8 -*-

import logging
logging.basicConfig(level=logging.INFO, 
                    format="%(asctime)s - %(levelname)s : %(message)s")
import os
import time
import numpy as np
import cv2

from sklearn.metrics import confusion_matrix

# In[]
def read_image(image_path):
  try:
    img = cv2.imread(image_path)
    img = cv2.resize(img, (200, 200))
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    return img
  except Exception as err:
    logging.error("Error at {} with {}.".format(image_path, err))
    return None

def get_image_label(path, idx, is_train=True):
  if is_train:
    path = os.path.join(path, "frontal")
  else:
    path = os.path.join(path, "profile")
  all_image = next(os.walk(path))[2]
  all_image = [image for image in all_image if image.split(".")[-1] in ["jpg", "jpeg", "png"]]
  all_image_content, all_id = [], []
  for image in all_image:
    img = read_image(os.path.join(path, image))
    if img is not None:
      all_image_content.append(img)
      all_id.append(idx)
  return all_image_content, all_id

# In[]
if __name__ == "__main__":

  image_folder = "../cfp"
  assert os.path.exists(image_folder), \
    "The path {} was not found.".format(image_folder)
  
  all_id = next(os.walk(image_folder))[1]
  logging.info("There are {} people.".format(len(all_id)))

  map_pid_id, map_id_pid = {}, {}
  all_train_image, all_train_label = [], []
  for idx in range(len(all_id)):
    pid = all_id[idx]
    map_pid_id[pid] = idx
    map_id_pid[idx] = pid
    
    path = os.path.join(image_folder, pid)
    train_image, train_label = get_image_label(path, idx)
    logging.info("There are {} images at PID {} (id: {}).".format(\
      len(train_label), pid, idx))

    all_train_image.extend(train_image)
    all_train_label.extend(train_label)
  logging.info("There are {} images in total.".format(len(all_train_label)))

  all_test_image, all_test_label = [], []
  for idx in range(len(all_id)):
    pid = all_id[idx]
    path = os.path.join(image_folder, pid)
    test_image, test_label = get_image_label(path, idx, is_train=False)
    logging.info("There are {} test images at PID {} (id: {}).".format(\
      len(test_label), pid, map_pid_id[pid]))

    all_test_image.extend(test_image)
    all_test_label.extend(test_label)
  logging.info("There are {} images in total.".format(len(all_test_label)))  

  for model_type in ["lbph", "eigen", "fisher"]:

    print("--------------------------------------")
    print("Model Type: {}".format(model_type))

    if model_type == "lbph":
      model = cv2.face_LBPHFaceRecognizer().create()
    elif model_type == "eigen":
      # num_components: 80%
      model = cv2.face_EigenFaceRecognizer(num_components=80).create()
    elif model_type == "fisher":
      model = cv2.face_FisherFaceRecognizer(num_components=80).create()
    else:
      raise ValueError("The model_type {} was not supported.".format(model_type))

    # train it
    transformed_label = np.array([all_train_label])
    model.train(all_train_image, transformed_label)

    # test the data
    prediction = []
    for test_image in all_test_image:
      predicted, distince = model.predict(test_image)
      prediction.append(predicted)
    print("Labeling:   {}".format(all_test_label))
    print("Prediction: {}".format(prediction))

    print(confusion_matrix(all_test_label, prediction))
