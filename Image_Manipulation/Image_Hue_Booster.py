import cv2 as cv
import os
import numpy as np

cfg_file_path = "Hue_Booster_Config.txt"

os.chdir(os.path.dirname(__file__))  # Makes working directory as .py file

cfg_file = open(cfg_file_path, 'r')
r_cfg_file = cfg_file.readlines()

input_folder = r_cfg_file[0]
input_folder = input_folder[:-1]  # Deleting '\0' character in the line.
change_operation = r_cfg_file[1]
change_operation = change_operation[:-1]  # Deleting '\0' character in the line.
output_folder = r_cfg_file[2]
output_folder = output_folder[:-1]  # Deleting '\0' character in the line.

if os.path.exists(input_folder):
    for (dirpath, dirnames, filenames) in os.walk(input_folder):
        for file in filenames:
            image = cv.imread(dirpath + '\\' + file)
            image = cv.cvtColor(image, cv.COLOR_BGR2HSV)
            if change_operation == '0':
                image[..., 1] = 255
            elif change_operation == '1':
                image[..., 1] = np.where(image[..., 1] > 127, 255, image[..., 1] + image[..., 1])
            elif change_operation == '2':
                image[..., 1] = np.where(image[..., 1] > 25, 255, image[..., 1])
            image = cv.cvtColor(image, cv.COLOR_HSV2BGR)
            if not os.path.exists(output_folder):
                os.mkdir(output_folder)
            cv.imwrite(output_folder + '\\' + file, image)
