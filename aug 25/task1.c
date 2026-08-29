#include <stdio.h>
#include <stdlib.h>

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
  FILE *fp=fopen("lena.bmp","rb");
    int x;
    int y;
fread(&file_header,sizeof(BMPFileHeader),1,fp);

    if (file_header.type != 0x4D42){
        printf("This is not a BMP file.\n");
        fclose(fp);
        return 1;
    }


    fread(&info_header,sizeof(BMPInfoHeader),1,fp);
    if (info_header.bits_per_pixel != 24){
        printf("Only 24-bit BMP files are supported.\n");
        fclose(fp);
        return 1;
    }

Image *image = malloc(sizeof(Image));
image->width = info_header.width;

image->height = info_header.height;

printf("height %d width %d",image->width,image->height);
image->data = malloc(image->width * image->height * sizeof(Pixel));
fseek(fp,file_header.offset,SEEK_SET);
for (y = image->height - 1;y >= 0;y--){
        for (x = 0;x < image->width;x++){
            unsigned char blue;
            unsigned char green;
            unsigned char red;
            fread(&blue,sizeof(unsigned char),1,fp);
            fread(&green,sizeof(unsigned char),1,fp);
            fread(&red,sizeof(unsigned char),1,fp);


            image->data[y * image->width + x].b = blue;
            image->data[y * image->width + x].g = green;
            image->data[y * image->width + x].r = red;
        }
  }
fclose(fp);
fp=fopen("n.bmp","wb");

fwrite(&file_header,sizeof(BMPFileHeader),1,fp);
fwrite(&info_header,sizeof(BMPInfoHeader),1,fp);


for (y = image->height - 1;y >= 0;y--){
        for (x = 0;x < image->width;x++){ 
            image->data[y * image->width + x].b *=0.114;
            image->data[y * image->width + x].g *=0.587;
            image->data[y * image->width + x].r *=0.299;
            fwrite(&image->data[y * image->width + x].b, sizeof(unsigned char), 1, fp);
            fwrite(&image->data[y * image->width + x].g, sizeof(unsigned char), 1, fp);
            fwrite(&image->data[y * image->width + x].r, sizeof(unsigned char), 1, fp);
        }
  }

free(image->data);
fclose(fp);
return 0;
}
