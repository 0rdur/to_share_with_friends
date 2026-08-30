#ifndef IMAGE_H
#define IMAGE_H

/*
    One RGB pixel.
*/
typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;//3 byte dhore rakha magic struct, eta ekta pixel reopresent korej

/*
    Image stored in memory as a top-to-bottom
    array of RGB pixels.
*/
typedef struct
{
    int width;//ei height and width diye viva par kora jabe ig, eta diya rotate ar crop deal kore
    int height;
    Pixel *data;//eta ekta pointer(ba array)jeta pixel data type er so etar ekta element ekta pixel save rakhe
  //etaei amra ss nibo ss ke manipulate korbo
} Image;

Image *load_bmp(const char *filename);//file load kore iup ke dey
int save_bmp(const char *filename, const Image *image);//file save kore

Image *copy_image(const Image *source);//undo er jonne copy create kore ney
void free_image(Image *image);//kaj seshe free kore
//egula image.c are operations.c te defined, and eder parameter gula gui theke input ashe

#endif
