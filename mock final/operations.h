#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "image.h"


void grayscale_image(Image *image);

void invert_image(Image *image);

void flip_horizontal(Image *image);

void flip_vertical(Image *image);

void adjust_brightness(Image *image, int brightness_change);

Image *rotate_image_90(Image *image);

Image *crop_image(Image *image, int crop_x, int crop_y, int crop_w, int crop_h);

void blur_image(Image *image);

void sharpen_image(Image *image);


#endif