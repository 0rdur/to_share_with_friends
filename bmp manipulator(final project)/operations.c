#include "operations.h"
#include <stddef.h>
#include <stdlib.h>


static Image *create_blank_image(int width, int height)
{
    Image *img;

    if (width <= 0 || height <= 0)
        return NULL;

    img = (Image *)malloc(sizeof(Image));
    if (img == NULL)
        return NULL;

    img->width = width;
    img->height = height;
    img->data = (Pixel *)malloc(sizeof(Pixel) * width * height);

    if (img->data == NULL)
    {
        free(img);
        return NULL;
    }

    return img;
}


void grayscale_image(Image *image)
{
    int x;
    int y;

    if (image == NULL)
        return;

    for (y = 0; y < image->height; y++)
    {
        for (x = 0; x < image->width; x++)
        {
            Pixel *pixel = &image->data[y * image->width + x];

            int gray = (299 * pixel->r +
                        587 * pixel->g +
                        114 * pixel->b) / 1000;

            pixel->r = (unsigned char)gray;
            pixel->g = (unsigned char)gray;
            pixel->b = (unsigned char)gray;
        }
    }
}


void invert_image(Image *image)
{
    int x;
    int y;

    if (image == NULL)
        return;

    for (y = 0; y < image->height; y++)
    {
        for (x = 0; x < image->width; x++)
        {
            Pixel *pixel = &image->data[y * image->width + x];

            pixel->r = 255 - pixel->r;
            pixel->g = 255 - pixel->g;
            pixel->b = 255 - pixel->b;
        }
    }
}


void flip_horizontal(Image *image)
{
    int x;
    int y;

    if (image == NULL)
        return;

    for (y = 0; y < image->height; y++)
    {
        for (x = 0; x < image->width / 2; x++)
        {
            int left_index = y * image->width + x;
            int right_index = y * image->width + (image->width - 1 - x);

            Pixel temp = image->data[left_index];
            image->data[left_index] = image->data[right_index];
            image->data[right_index] = temp;
        }
    }
}


void flip_vertical(Image *image)
{
    int x;
    int y;

    if (image == NULL)
        return;

    for (y = 0; y < image->height / 2; y++)
    {
        for (x = 0; x < image->width; x++)
        {
            int top_index = y * image->width + x;
            int bottom_index = (image->height - 1 - y) * image->width + x;

            Pixel temp = image->data[top_index];
            image->data[top_index] = image->data[bottom_index];
            image->data[bottom_index] = temp;
        }
    }
}


void adjust_brightness(Image *image, int brightness_change)
{
    int i;
    int total_pixels;

    if (image == NULL)
        return;

    total_pixels = image->width * image->height;

    for (i = 0; i < total_pixels; i++)
    {
        int r = image->data[i].r + brightness_change;
        int g = image->data[i].g + brightness_change;
        int b = image->data[i].b + brightness_change;

        /* Clamp values to valid range [0, 255] */
        image->data[i].r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
        image->data[i].g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
        image->data[i].b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));
    }
}


Image *rotate_image_90(Image *image)
{
    int x;
    int y;
    int new_w;
    int new_h;
    Image *new_img;

    if (image == NULL)
        return NULL;

    new_w = image->height;
    new_h = image->width;

    new_img = create_blank_image(new_w, new_h);
    if (new_img == NULL)
        return NULL;

    for (y = 0; y < image->height; y++)
    {
        for (x = 0; x < image->width; x++)
        {
            int new_x = image->height - 1 - y;
            int new_y = x;

            new_img->data[new_y * new_w + new_x] =
                image->data[y * image->width + x];
        }
    }

    return new_img;
}


Image *crop_image(Image *image, int crop_x, int crop_y, int crop_w, int crop_h)
{
    int x;
    int y;
    Image *cropped;

    if (image == NULL)
        return NULL;

    if (crop_x < 0 || crop_y < 0 || crop_w <= 0 || crop_h <= 0 ||
        (crop_x + crop_w) > image->width || (crop_y + crop_h) > image->height)
    {
        return NULL;
    }

    cropped = create_blank_image(crop_w, crop_h);
    if (cropped == NULL)
        return NULL;

    for (y = 0; y < crop_h; y++)
    {
        for (x = 0; x < crop_w; x++)
        {
            cropped->data[y * crop_w + x] =
                image->data[(crop_y + y) * image->width + (crop_x + x)];
        }
    }

    return cropped;
}


void blur_image(Image *image)
{
    int x;
    int y;
    int w;
    int h;
    int i;
    Image *temp;

    if (image == NULL)
        return;

    w = image->width;
    h = image->height;

    temp = create_blank_image(w, h);
    if (temp == NULL)
        return;

    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)//goes through the original image pixels
        {
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;
            int count = 0;

            int ny;
            int nx;

            for (ny = y - 1; ny <= y + 1; ny++)
            {
                for (nx = x - 1; nx <= x + 1; nx++)//traverses the 3x3 around the selected pixelk using coordinate geometry
                {
                    if (nx >= 0 && nx < w && ny >= 0 && ny < h)
                    {
                        Pixel p = image->data[ny * w + nx];
                        sum_r += p.r;
                        sum_g += p.g;
                        sum_b += p.b;
                        count++;
                    }
                }
            }

            temp->data[y * w + x].r = (unsigned char)(sum_r / count);
            temp->data[y * w + x].g = (unsigned char)(sum_g / count);
            temp->data[y * w + x].b = (unsigned char)(sum_b / count);
        }
    }

    for (i = 0; i < w * h; i++)//since the image dimension is same we rewrite the original by the blur
    {
        image->data[i] = temp->data[i];
    }

    free_image(temp);
}


void sharpen_image(Image *image)//exact same as blur
{
    int x;
    int y;
    int w;
    int h;
    int i;
    Image *temp;

    int kernel[3][3] = {
        { 0, -1,  0},
        {-1,  5, -1},
        { 0, -1,  0}
    };

    if (image == NULL)
        return;

    w = image->width;
    h = image->height;

    temp = create_blank_image(w, h);
    if (temp == NULL)
        return;

    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;

            int ky;
            int kx;

            for (ky = -1; ky <= 1; ky++)
            {
                for (kx = -1; kx <= 1; kx++)
                {
                    int nx = x + kx;
                    int ny = y + ky;

                    if (nx < 0) nx = 0;
                    if (nx >= w) nx = w - 1;
                    if (ny < 0) ny = 0;
                    if (ny >= h) ny = h - 1;

                    Pixel p = image->data[ny * w + nx];
                    int weight = kernel[ky + 1][kx + 1];

                    sum_r += p.r * weight;
                    sum_g += p.g * weight;
                    sum_b += p.b * weight;
                }
            }

            temp->data[y * w + x].r = (unsigned char)(sum_r < 0 ? 0 : (sum_r > 255 ? 255 : sum_r));
            temp->data[y * w + x].g = (unsigned char)(sum_g < 0 ? 0 : (sum_g > 255 ? 255 : sum_g));
            temp->data[y * w + x].b = (unsigned char)(sum_b < 0 ? 0 : (sum_b > 255 ? 255 : sum_b));
        }
    }

    for (i = 0; i < w * h; i++)
    {
        image->data[i] = temp->data[i];
    }

    free_image(temp);
}
