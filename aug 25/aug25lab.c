#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)

typedef struct
{
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPFileHeader;

typedef struct
{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint8_t temp[24];
} BMPInfoHeader;

typedef struct
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
} Pixel;

#pragma pack(pop)

int main() {
    FILE *fp = fopen("lena.bmp", "rb");
    FILE *fo = fopen("n.bmp", "wb");

    if (fp == NULL || fo == NULL) {
        if (fp) fclose(fp);
        if (fo) fclose(fo);
        return 1;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    if (fread(&fileHeader, sizeof(BMPFileHeader), 1, fp) != 1 ||
        fread(&infoHeader, sizeof(BMPInfoHeader), 1, fp) != 1) {
        fclose(fp);
        fclose(fo);
        return 1;
    }

    if (fileHeader.type != 0x4D42) {
        printf("Not a bmp\n");
        fclose(fp);
        fclose(fo);
        return 1;
    }

    if (infoHeader.bits_per_pixel != 24) {
        printf("not 24 bit");
        fclose(fp);
        fclose(fo);
        return 1;
    }

    printf("width: %d\n", infoHeader.width);
    printf("height: %d\n", infoHeader.height);

    fwrite(&fileHeader, sizeof(BMPFileHeader), 1, fo);
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, fo);

    Pixel pixel;
    while (fread(&pixel, sizeof(Pixel), 1, fp) == 1) {
        int gray = (int)(0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b);
        if (gray > 255) gray = 255;
        if (gray < 0) gray = 0;

        pixel.r = gray;
        pixel.g = gray;
        pixel.b = gray;

        fwrite(&pixel, sizeof(Pixel), 1, fo);
    }

    fclose(fp);
    fclose(fo);
    return 0;
}
