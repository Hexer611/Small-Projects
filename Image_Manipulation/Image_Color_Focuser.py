import cv2 as cv
import os
import numpy as np

cfg_file_path = "Color_Focuser_Config.txt"

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
            image_gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
            image_hsv = cv.cvtColor(image, cv.COLOR_BGR2HSV)
            if change_operation == 'red':
                lower_blue_value = 160
                upper_blue_value = 20
                _smooth_lbv = lower_blue_value / 10 - 1
                _smooth_ubv = upper_blue_value / 10 + 1
                smooth = 10
                blue_mask = cv.inRange(image_hsv, (lower_blue_value, 10, 10), (180, 255, 255)) | cv.inRange(image_hsv, (0, 10, 10), (upper_blue_value, 255, 255))
                lower_blue_mask = cv.inRange(image_hsv, (lower_blue_value - smooth, 10, 10), (lower_blue_value, 255, 255))
                upper_blue_mask = cv.inRange(image_hsv, (upper_blue_value, 10, 10), (upper_blue_value + smooth, 255, 255))

                image[..., 0] = np.where(blue_mask, image[..., 0],
                                         np.where(lower_blue_mask, image_gray * (lower_blue_value / 10 - image_hsv[..., 0] / 10) + image[..., 0] * (image_hsv[..., 0] / 10 - _smooth_lbv),
                                                  np.where(upper_blue_mask, image_gray * (image_hsv[..., 0] / 10 - upper_blue_value / 10) + image[..., 0] * (_smooth_ubv - image_hsv[..., 0] / 10),
                                                           image_gray)))
                image[..., 1] = np.where(blue_mask, image[..., 1],
                                         np.where(lower_blue_mask, image_gray * (lower_blue_value / 10 - image_hsv[..., 0] / 10) + image[..., 1] * (image_hsv[..., 0] / 10 - _smooth_lbv),
                                                  np.where(upper_blue_mask, image_gray * (image_hsv[..., 0] / 10 - upper_blue_value / 10) + image[..., 1] * (_smooth_ubv - image_hsv[..., 0] / 10),
                                                           image_gray)))
                image[..., 2] = np.where(blue_mask, image[..., 2],
                                         np.where(lower_blue_mask, image_gray * (lower_blue_value / 10 - image_hsv[..., 0] / 10) + image[..., 2] * (image_hsv[..., 0] / 10 - _smooth_lbv),
                                                  np.where(upper_blue_mask, image_gray * (image_hsv[..., 0] / 10 - upper_blue_value / 10) + image[..., 2] * (_smooth_ubv - image_hsv[..., 0] / 10),
                                                           image_gray)))
            elif change_operation == 'blue':
                lower_blue_value = 90
                upper_blue_value = 120
                _smooth_lbv = lower_blue_value / 10 - 1
                _smooth_ubv = upper_blue_value / 10 + 1
                smooth = 10
                blue_mask = cv.inRange(image_hsv, (lower_blue_value, 10, 10), (upper_blue_value, 255, 255))
                lower_blue_mask = cv.inRange(image_hsv, (lower_blue_value - smooth, 10, 10), (lower_blue_value, 255, 255))
                upper_blue_mask = cv.inRange(image_hsv, (upper_blue_value, 10, 10), (upper_blue_value + smooth, 255, 255))

                image[..., 0] = np.where(blue_mask, image[..., 0],
                                         np.where(lower_blue_mask, image_gray * (lower_blue_value / 10 - image_hsv[..., 0] / 10) + image[..., 0] * (image_hsv[..., 0] / 10 - _smooth_lbv),
                                         np.where(upper_blue_mask, image_gray * (image_hsv[..., 0] / 10 - upper_blue_value / 10) + image[..., 0] * (_smooth_ubv - image_hsv[..., 0] / 10),
                                                  image_gray)))
                image[..., 1] = np.where(blue_mask, image[..., 1],
                                         np.where(lower_blue_mask, image_gray * (lower_blue_value / 10 - image_hsv[..., 0] / 10) + image[..., 1] * (image_hsv[..., 0] / 10 - _smooth_lbv),
                                         np.where(upper_blue_mask, image_gray * (image_hsv[..., 0] / 10 - upper_blue_value / 10) + image[..., 1] * (_smooth_ubv - image_hsv[..., 0] / 10),
                                                  image_gray)))
                image[..., 2] = np.where(blue_mask, image[..., 2],
                                         np.where(lower_blue_mask, image_gray * (lower_blue_value / 10 - image_hsv[..., 0] / 10) + image[..., 2] * (image_hsv[..., 0] / 10 - _smooth_lbv),
                                         np.where(upper_blue_mask, image_gray * (image_hsv[..., 0] / 10 - upper_blue_value / 10) + image[..., 2] * (_smooth_ubv - image_hsv[..., 0] / 10),
                                                  image_gray)))
            elif change_operation == 'green':
                lower_blue_value = 45
                upper_blue_value = 75
                _smooth_lbv = lower_blue_value / 10 - 1
                _smooth_ubv = upper_blue_value / 10 + 1
                smooth = 10
                blue_mask = cv.inRange(image_hsv, (lower_blue_value, 10, 10), (upper_blue_value, 255, 255))
                lower_blue_mask = cv.inRange(image_hsv, (lower_blue_value - smooth, 10, 10), (lower_blue_value, 255, 255))
                upper_blue_mask = cv.inRange(image_hsv, (upper_blue_value, 10, 10), (upper_blue_value + smooth, 255, 255))

                image[..., 0] = np.where(blue_mask, image[..., 0],
                                         np.where(lower_blue_mask, image_gray * (lower_blue_value / 10 - image_hsv[..., 0] / 10) + image[..., 0] * (image_hsv[..., 0] / 10 - _smooth_lbv),
                                                  np.where(upper_blue_mask, image_gray * (image_hsv[..., 0] / 10 - upper_blue_value / 10) + image[..., 0] * (_smooth_ubv - image_hsv[..., 0] / 10),
                                                           image_gray)))
                image[..., 1] = np.where(blue_mask, image[..., 1],
                                         np.where(lower_blue_mask, image_gray * (lower_blue_value / 10 - image_hsv[..., 0] / 10) + image[..., 1] * (image_hsv[..., 0] / 10 - _smooth_lbv),
                                                  np.where(upper_blue_mask, image_gray * (image_hsv[..., 0] / 10 - upper_blue_value / 10) + image[..., 1] * (_smooth_ubv - image_hsv[..., 0] / 10),
                                                           image_gray)))
                image[..., 2] = np.where(blue_mask, image[..., 2],
                                         np.where(lower_blue_mask, image_gray * (lower_blue_value / 10 - image_hsv[..., 0] / 10) + image[..., 2] * (image_hsv[..., 0] / 10 - _smooth_lbv),
                                                  np.where(upper_blue_mask, image_gray * (image_hsv[..., 0] / 10 - upper_blue_value / 10) + image[..., 2] * (_smooth_ubv - image_hsv[..., 0] / 10),
                                                           image_gray)))
            # image = cv.cvtColor(image, cv.COLOR_HSV2BGR)
            if not os.path.exists(output_folder):
                os.mkdir(output_folder)
            cv.imwrite(output_folder + '\\' + file, image)
