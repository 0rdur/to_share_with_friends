#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "image.h"

/*
    BMP file headers.
    The assignment only requires uncompressed 24-bit BMP.
*/
#pragma pack(push, 1)

typedef struct
{
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;//eta lagbe pore skip korte pixel e
} BMPFileHeader;//header file er 14byte

typedef struct
{
    uint32_t size;
    int32_t width;//lageb
    int32_t height;//lahbe
    uint16_t planes;
    uint16_t bits_per_pixel;//lahgbe
    uint32_t compression;//lagbe
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t important_colors;
} BMPInfoHeader;//info header er 40 byte
//total 54 bit uselss,so ei type er variable e read kore rekhe dibo

#pragma pack(pop)

Image *load_bmp(const char *filename)//filename oi mouse diyue choose kora file tar nam return kore 
{
    FILE *file;
    BMPFileHeader file_header;//eito 14 byte
    BMPInfoHeader info_header;//eito 40 byet
    Image *image;
    unsigned char *row;//image read korte lagbe
    int width;
    int height;
    int bottom_up;
    int row_size;//padding skip korte lagbe
    int x;
    int y;

    if (filename == NULL)
        return NULL;

    file = fopen(filename, "rb");
    if (file == NULL)
        return NULL;

    if (fread(&file_header, sizeof(file_header), 1, file) != 1 ||
        fread(&info_header, sizeof(info_header), 1, file) != 1)
    {
        fclose(file);
        return NULL;
    }// 54 byte data save korlam

    if (file_header.type != 0x4D42 ||
        info_header.size < 40 ||
        info_header.planes != 1 ||
        info_header.bits_per_pixel != 24 ||
        info_header.compression != 0 ||
        info_header.width <= 0 ||
        info_header.height == 0)
    {
        fclose(file);
        return NULL;
    }//sir je info guli check korte bolse oigula korlam

    width = info_header.width;

    if (info_header.height < 0)
    {
        height = -info_header.height;
        bottom_up = 0;
    }
    else
    {
        height = info_header.height;
        bottom_up = 1;
    }//height ultani naki dekhlam

    image = (Image *)malloc(sizeof(Image));//image er jonne jayga dilam
    if (image == NULL)
    {
        fclose(file);
        return NULL;
    }

    image->width = width;
    image->height = height;
    image->data = (Pixel *)malloc(
        (size_t)width * (size_t)height * sizeof(Pixel)
    );//image er ss ta neyar jonne jayga dilam

    if (image->data == NULL)
    {
        free(image);
        fclose(file);
        return NULL;
    }

    row_size = ((width * 3 + 3) / 4) * 4;//padding soho nilam

    row = (unsigned char *)malloc((size_t)row_size);//row nibo ekta ekta kore jayga dilam
    if (row == NULL)
    {
        free_image(image);
        fclose(file);
        return NULL;
    }

    if (fseek(file, (long)file_header.offset, SEEK_SET) != 0)//oito..lagbe bolsilam skip korlam pixel porjnto
  //fseek( kon file, kotokhani,kotha theke) kotha theke=seekset mane file er shure theke
    {
        free(row);
        free_image(image);
        fclose(file);
        return NULL;
    }

    for (y = 0; y < height; y++)
    {
        int destination_y;

        if (fread(row, 1, (size_t)row_size, file) != (size_t)row_size)//ekta row read korlam
        {
            free(row);
            free_image(image);
            fclose(file);
            return NULL;
        }


      if (bottom_up)
      {
       destination_y = height - 1 - y;
        }
      else
      {
        destination_y = y;}

        for (x = 0; x < width; x++)
        {
            Pixel *pixel = &image->data[
                destination_y * width + x
            ];//3 byte rakha pixel data type e pixel type er main ss er ekta pixel er adress dilam

            /* BMP stores BGR, while the program stores RGB. */
            pixel->b = row[x * 3 + 0];
            pixel->g = row[x * 3 + 1];
            pixel->r = row[x * 3 + 2];
           //oi adress e as in oi main ss e (same shit) rgb soja row order kore nilam
        }
    }

    free(row);
    fclose(file);
   //ss neya sesh
    return image;//ss firot dilam
}

int save_bmp(const char *filename, const Image *image)
{
    FILE *file;
    BMPFileHeader file_header;
    BMPInfoHeader info_header;
    unsigned char *row;
    int row_size;
    int x;
    int y;

    if (filename == NULL ||
        image == NULL ||
        image->data == NULL ||
        image->width <= 0 ||
        image->height <= 0)
    {
        return 0;
    }

    file = fopen(filename, "wb");
    if (file == NULL)
        return 0;

    row_size = ((image->width * 3 + 3) / 4) * 4;

    row = (unsigned char *)malloc((size_t)row_size);
    if (row == NULL)
    {
        fclose(file);
        return 0;
    }
     //value sob hardcode korlam
    file_header.type = 0x4D42;
    file_header.size =
        (uint32_t)(sizeof(BMPFileHeader) +
                   sizeof(BMPInfoHeader) +
                   row_size * image->height);
    file_header.reserved1 = 0;
    file_header.reserved2 = 0;
    file_header.offset =
        sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    info_header.size = sizeof(BMPInfoHeader);
    info_header.width = image->width;//rotate and crop e change hole 
    info_header.height = image->height;//same
    info_header.planes = 1;
    info_header.bits_per_pixel = 24;
    info_header.compression = 0;
    info_header.image_size =
        (uint32_t)(row_size * image->height);
    info_header.x_pixels_per_meter = 0;
    info_header.y_pixels_per_meter = 0;
    info_header.colors_used = 0;
    info_header.important_colors = 0;

    if (fwrite(&file_header, sizeof(file_header), 1, file) != 1 ||
        fwrite(&info_header, sizeof(info_header), 1, file) != 1)//header info header write korlam
    {
        free(row);
        fclose(file);
        return 0;
    }

    /*
        Internal image is top-to-bottom.
        BMP is written bottom-to-top.
    */
    for (y = image->height - 1; y >= 0; y--)
  //same sytem row niye row pad kore total ta dhukabo ulta kore
    {
        for (x = 0; x < image->width; x++)
        {
            Pixel pixel =
                image->data[y * image->width + x];

            row[x * 3 + 0] = pixel.b;
            row[x * 3 + 1] = pixel.g;
            row[x * 3 + 2] = pixel.r;
        }//bgr fix

        /* Clear the row padding bytes. */
        for (x = image->width * 3; x < row_size; x++)
            row[x] = 0;

        if (fwrite(row, 1, (size_t)row_size, file) !=
            (size_t)row_size)//write korlam
        {
            free(row);
            fclose(file);
            return 0;
        }
    }

    free(row);
    fclose(file);

    return 1;
}

Image *copy_image(const Image *source)//undo korar jonne image er copy rekhe dicchi
{
    Image *copy;
    size_t total_pixels;

    if (source == NULL ||
        source->data == NULL ||
        source->width <= 0 ||
        source->height <= 0)
    {
        return NULL;
    }

    copy = (Image *)malloc(sizeof(Image));//jayga allocate korlam
    if (copy == NULL)
        return NULL;

    copy->width = source->width;
    copy->height = source->height;

    total_pixels =
        (size_t)source->width * (size_t)source->height;

    copy->data =
        (Pixel *)malloc(total_pixels * sizeof(Pixel));

    if (copy->data == NULL)
    {
        free(copy);
        return NULL;
    }

    for (size_t i = 0; i < total_pixels; i++)
        copy->data[i] = source->data[i];

    return copy;//copy kora seshe undor jonne copy kora oi ss ta firot dilam(space er adress ta actually,but you get me)
}

void free_image(Image *image)//kaj seshe main image er space ke free korlam
{
    if (image == NULL)
        return;

    free(image->data);
    free(image);
    
}
