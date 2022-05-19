# -*- coding:utf8 -*-

import logging
logging.basicConfig(level=logging.DEBUG, 
                    format="%(asctime)s - %(levelname)s : %(message)s")
import os
import numpy as np
import cv2

if __name__ == "__main__":
  
  image_path = "../images/lena.jpg"
  assert os.path.exists(image_path), \
    "The image file at {} was not found.".format(image_path)

  try:
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    image = np.float32(image)
    
    # do the dft, shape becomes [img_nrow, img_ncol, 2]
    # [:,:,2], 0 for real values and 1 for imaginary values
    img_dft = cv2.dft(image, flags=cv2.DFT_COMPLEX_OUTPUT)

    # do the inverse dft
    img_idft = cv2.idft(img_dft)
    
    # get the magnitude value
    img_idft_magn = cv2.magnitude(img_idft[:,:,0], img_idft[:,:,1])
    
    # next you have to devide the magnitude by the size of the data
    # here the size is the number of total pixel
    kernel = image.shape[0] * image.shape[1]
    img_idft_magn /= kernel
    
    # write out the result
    cv2.imwrite("./img_dft.jpg", img_idft_magn)
    
  except Exception as err:
    logging.error("{}".format(err))
