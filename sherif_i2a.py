#!/usr/bin/env python3
from PIL import Image
import numpy as np 
import shutil 
from colorama import Style
import sys

ascii_chars = "@%#*+=-:. "

max_width = 206
gamma = 2.2
color_output = True

def resize_image(image, new_width=max_width):
    width, height = image.size
    aspect_ratio = height/width
    new_height = int(aspect_ratio * new_width * 0.55)
    resized_image = image.resize((new_width, new_height))
    return resized_image

def convert_toGrayscale(image):
    return image.convert("L")

def gamma_correction(img_pixels):
    normalized = img_pixels / 255.0 #-> normalize it to be between 0 and 1, best when work with image s
    corrected = np.power(normalized, 1/gamma)
    return (corrected*255).astype(np.uint8) #=> *255 to scale it back to 0:255 

def map_brightness(image):
    pixels = np.array(image)
    pixels = gamma_correction(pixels)
    ascii_image = " "
    step = 255 / (len(ascii_chars)-1)
    for row in pixels:
        for pixel in row:
            ascii_image += ascii_chars[int(pixel // step)]
        ascii_image += "\n"
    return ascii_image

def map_colors(image):
    image1 = np.array(image)
    gray = np.dot(image1[..., :3], [0.299, 0.587, 0.114])
    gray = gamma_correction(gray)
    step = 255 / (len(ascii_chars)-1)
    ascii_image = " "
    for row in range(image1.shape[0]):
        for col in range(image1.shape[1]):
            r, g, b = image1[row, col][:3]
            char = ascii_chars[int(gray[row, col] // step)]
            ascii_image += f"\033[38;2;{r};{g};{b}m{char}{Style.RESET_ALL}"
        ascii_image += "\n"
    return ascii_image

def main(image_path):
    try:
        term_width = shutil.get_terminal_size().columns
        new_width = min(max_width, term_width)
        image = Image.open(image_path)
        image = resize_image(image, new_width)
        if color_output:
            ascii_image = map_colors(image)
        else:
            ascii_image = map_brightness(image)
        print(ascii_image)
    except Exception as e:
        print(f"error: {e}")
        sys.exit(1)

if __name__ == "__main__":
        if len(sys.argv) < 2:
            print("You need to specify the image path while trying this: ")
        else:
            main(sys.argv[1])
