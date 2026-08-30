#include <stdio.h>
#include <stdlib.h>

#include "image.h"


#pragma pack(push, 1)

typedef struct
{
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;

} BMPFileHeader;


typedef struct
{
    unsigned int size;

    int width;
    int height;

    unsigned short planes;
    unsigned short bits_per_pixel;

    unsigned int compression;
    unsigned int image_size;

    int x_pixels_per_meter;
    int y_pixels_per_meter;

    unsigned int colors_used;
    unsigned int important_colors;

} BMPInfoHeader;

#pragma pack(pop)


Image *load_bmp(const char *filename)
{
    FILE *file;

    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    Image *image;

    int x;
    int y;

    int padding;


    /* Open file */

    file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("Could not open file.\n");
        return NULL;
    }


    /* Read BMP file header */

    fread(
        &file_header,
        sizeof(BMPFileHeader),
        1,
        file
    );


    /* Check BMP signature */

    if (file_header.type != 0x4D42)
    {
        printf("This is not a BMP file.\n");

        fclose(file);

        return NULL;
    }


    /* Read BMP information header */

    fread(
        &info_header,
        sizeof(BMPInfoHeader),
        1,
        file
    );


    /* We only support 24-bit BMP */

    if (info_header.bits_per_pixel != 24)
    {
        printf(
            "Only 24-bit BMP files are supported.\n"
        );

        fclose(file);

        return NULL;
    }


    /* We only support uncompressed BMP */

    if (info_header.compression != 0)
    {
        printf(
            "Compressed BMP files are not supported.\n"
        );

        fclose(file);

        return NULL;
    }


    /*
        Create our Image structure.
    */

    image = malloc(sizeof(Image));

    if (image == NULL)
    {
        fclose(file);

        return NULL;
    }


    image->width =
        info_header.width;

    image->height =
        info_header.height;


    /*
        BMP normally stores rows from bottom to top.
        For now, we assume a normal positive height.
    */

    if (image->height < 0)
    {
        image->height =
            -image->height;
    }


    /*
        Allocate memory for all pixels.
    */

    image->data =
        malloc(
            image->width *
            image->height *
            sizeof(Pixel)
        );


    if (image->data == NULL)
    {
        free(image);

        fclose(file);

        return NULL;
    }


    /*
        Calculate BMP row padding.

        Every BMP row must occupy a multiple of
        4 bytes.
    */

    padding =
        (4 - (image->width * 3) % 4) % 4;


    /*
        Jump to pixel data.
    */

    fseek(
        file,
        file_header.offset,
        SEEK_SET
    );


    /*
        Read pixels.
    */

    for (y = image->height - 1;
         y >= 0;
         y--)
    {
        for (x = 0;
             x < image->width;
             x++)
        {
            unsigned char blue;
            unsigned char green;
            unsigned char red;


            /*
                BMP stores BGR.
            */

            fread(
                &blue,
                sizeof(unsigned char),
                1,
                file
            );

            fread(
                &green,
                sizeof(unsigned char),
                1,
                file
            );

            fread(
                &red,
                sizeof(unsigned char),
                1,
                file
            );


            /*
                We store RGB.
            */

            image->data[
                y * image->width + x
            ].r = red;

            image->data[
                y * image->width + x
            ].g = green;

            image->data[
                y * image->width + x
            ].b = blue;
        }


        /*
            Skip row padding.
        */

        fseek(
            file,
            padding,
            SEEK_CUR
        );
    }


    fclose(file);


    return image;
}
Image *copy_image(const Image *source)
{
    Image *copy;

    int total_pixels;
    int i;


    if (source == NULL)
        return NULL;


    copy = malloc(sizeof(Image));

    if (copy == NULL)
        return NULL;


    copy->width = source->width;
    copy->height = source->height;


    total_pixels =
        source->width * source->height;


    copy->data =
        malloc(
            total_pixels * sizeof(Pixel)
        );


    if (copy->data == NULL)
    {
        free(copy);
        return NULL;
    }


    for (i = 0; i < total_pixels; i++)
    {
        copy->data[i] =
            source->data[i];
    }


    return copy;
}int save_bmp(
    const char *filename,
    const Image *image
)
{
    FILE *file;

    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    int x;
    int y;
    int padding;

    unsigned char zero[3] = {0, 0, 0};


    if (image == NULL)
        return 0;


    file =
        fopen(filename, "wb");


    if (file == NULL)
        return 0;


    padding =
        (4 - (image->width * 3) % 4) % 4;


    unsigned int row_size =
        image->width * 3 + padding;


    unsigned int image_size =
        row_size * image->height;


    /*
        FILE HEADER
    */

    file_header.type = 0x4D42;

    file_header.size =
        sizeof(BMPFileHeader) +
        sizeof(BMPInfoHeader) +
        image_size;

    file_header.reserved1 = 0;
    file_header.reserved2 = 0;

    file_header.offset =
        sizeof(BMPFileHeader) +
        sizeof(BMPInfoHeader);


    /*
        INFO HEADER
    */

    info_header.size =
        sizeof(BMPInfoHeader);

    info_header.width =
        image->width;

    info_header.height =
        image->height;

    info_header.planes =
        1;

    info_header.bits_per_pixel =
        24;

    info_header.compression =
        0;

    info_header.image_size =
        image_size;

    info_header.x_pixels_per_meter = 0;
    info_header.y_pixels_per_meter = 0;

    info_header.colors_used = 0;
    info_header.important_colors = 0;


    /*
        Write headers.
    */

    fwrite(
        &file_header,
        sizeof(BMPFileHeader),
        1,
        file
    );


    fwrite(
        &info_header,
        sizeof(BMPInfoHeader),
        1,
        file
    );


    /*
        BMP stores rows bottom-to-top.
    */

    for (y = image->height - 1;
         y >= 0;
         y--)
    {
        for (x = 0;
             x < image->width;
             x++)
        {
            Pixel pixel;


            pixel =
                image->data[
                    y * image->width + x
                ];


            /*
                BMP wants BGR,
                while our Pixel is RGB.
            */

            fwrite(
                &pixel.b,
                sizeof(unsigned char),
                1,
                file
            );


            fwrite(
                &pixel.g,
                sizeof(unsigned char),
                1,
                file
            );


            fwrite(
                &pixel.r,
                sizeof(unsigned char),
                1,
                file
            );
        }


        /*
            BMP row padding.
        */

        fwrite(
            zero,
            1,
            padding,
            file
        );
    }


    fclose(file);

    return 1;
}

void free_image(Image *image)
{
    if (image == NULL)
        return;


    free(image->data);

    free(image);
}
