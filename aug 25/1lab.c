#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char temp[24];

} BMPInfoHeader;

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef struct
{
    int width;
    int height;
    Pixel *data;
} Image;

#pragma pack(pop)

int main(){ 
    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    FILE *fp = fopen("lena.bmp", "rb");
    if (fp == NULL) {
        printf("Could not open lena.bmp\n");
        return 1;
    }

    int x;
    int y;

    fread(&file_header, sizeof(BMPFileHeader), 1, fp);
    if (file_header.type != 0x4D42){
        printf("This is not a BMP file.\n");
        fclose(fp);
        return 1;
    }

    fread(&info_header, sizeof(BMPInfoHeader), 1, fp);
    if (info_header.bits_per_pixel != 24){
        printf("Only 24-bit BMP files are supported.\n");
        fclose(fp);
        return 1;
    }

    Image *image = malloc(sizeof(Image));
    image->width = info_header.width;
    image->height = info_header.height;

    printf("height %d width %d\n", image->height, image->width);
    image->data = malloc(image->width * image->height * sizeof(Pixel));

    // Calculate row padding (BMP rows must be multiples of 4 bytes)
    int padding = (4 - (image->width * 3) % 4) % 4;

    fseek(fp, file_header.offset, SEEK_SET);

    for (y = image->height - 1; y >= 0; y--){
        for (x = 0; x < image->width; x++){
            unsigned char blue;
            unsigned char green;
            unsigned char red;
            fread(&blue, sizeof(unsigned char), 1, fp);
            fread(&green, sizeof(unsigned char), 1, fp);
            fread(&red, sizeof(unsigned char), 1, fp);

            image->data[y * image->width + x].b = blue;
            image->data[y * image->width + x].g = green;
            image->data[y * image->width + x].r = red;
        }
        fseek(fp, padding, SEEK_CUR); // skip input padding
    }
    fclose(fp);

    fp = fopen("n.bmp", "wb");

    // FIX 1: Correct file headers before writing
    file_header.offset = 54; // Standard 14 + 40 header offset
    file_header.size = 54 + (image->width * 3 + padding) * image->height;
    
    // Clear out compression/junk flags in temp[24] so viewers can open it
    memset(info_header.temp, 0, 24); 

    fwrite(&file_header, sizeof(BMPFileHeader), 1, fp);
    fwrite(&info_header, sizeof(BMPInfoHeader), 1, fp);

    unsigned char padding_byte = 0;

    for (y = image->height - 1; y >= 0; y--){
        for (x = 0; x < image->width; x++){ 
            // FIX 2: Calculate proper gray value and assign equally to all 3 channels
            unsigned char gray = (unsigned char)(
                image->data[y * image->width + x].r * 0.299 +
                image->data[y * image->width + x].g * 0.587 +
                image->data[y * image->width + x].b * 0.114
            );

            image->data[y * image->width + x].b = gray;
            image->data[y * image->width + x].g = gray;
            image->data[y * image->width + x].r = gray;

            fwrite(&image->data[y * image->width + x].b, sizeof(unsigned char), 1, fp);
            fwrite(&image->data[y * image->width + x].g, sizeof(unsigned char), 1, fp);
            fwrite(&image->data[y * image->width + x].r, sizeof(unsigned char), 1, fp);
        }
        // FIX 3: Write required padding bytes per row so file structure isn't corrupted
        for (int p = 0; p < padding; p++) {
            fwrite(&padding_byte, sizeof(unsigned char), 1, fp);
        }
    }

    fclose(fp);
    free(image->data);
    free(image);

    printf("Done! 'n.bmp' generated successfully.\n");
    return 0;
}
