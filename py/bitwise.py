# -*- coding:utf8 -*-

"""
The basic idea behind encrypting an image is to do the bitwise operation of XOR to the image.
The above process is called encrypting. On the other hand, do the XOR to the encrypted image 
to get the original image, called decrypting.
"""

import logging
logging.basicConfig(level=logging.INFO, 
                    format="%(asctime)s - %(levelname)s : %(message)s")

import os
import numpy as np
import cv2
import helpers as h

# In[]

def xor_on_image(image_numpy_array, key):
  try:
    return cv2.bitwise_xor(image_numpy_array, key)
  except Exception as err:
    logging.error("Failed in doing the XOR operation. {}".format(err))


# In[]

if __name__ == "__main__":
  
  file_path = os.path.join("..", "images", "lena.jpg")
  assert os.path.exists(file_path), \
    "Failed in finding the image at {}.".format(file_path)

  # for reproduction
  np.random.seed(0)

  img = h.read_image(file_path)
  assert img.ndim == 3

  key_path = os.path.join(".", "key.jpg")
  if not os.path.exists(key_path):
    key = np.random.randint(0, 255, size=img.shape, dtype=np.uint8)
    _ = h.write_image(key_path, key)
  else:
    key = h.read_image(key_path)
    assert key is not None

  encrypted_path = os.path.join(".", "encrypted.jpg")
  if not os.path.exists(encrypted_path):
    img_encrypted = xor_on_image(img, key)
    h.write_image(encrypted_path, img_encrypted)
  else:
    img_encrypted = h.read_image(encrypted_path)
    assert img_encrypted is not None
  
  decrypted_path = os.path.join(".", "decrypted.jpg")
  if not os.path.exists(decrypted_path):
    img_decrypted = xor_on_image(img_encrypted, key)
    h.write_image(decrypted_path, img_decrypted)
    logging.info("Write out the original image successfully.")

