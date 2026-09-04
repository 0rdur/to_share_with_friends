#include <stdlib.h>

#include "operations.h"

static Image *create_blank_image(int width, int height)
//memory te image er jone jayga allocate kore ar kicchuna,then allocated jaygar adress return kore
{
    Image *image;

    if (width <= 0 || height <= 0)
        return NULL;

    image = (Image *)malloc(sizeof(Image));
    if (image == NULL)
        return NULL;

    image->width = width;//eito change kore dilam local e korsi so original image cng hoyni
    image->height = height;
    image->data = (Pixel *)malloc(
        (size_t)width * (size_t)height * sizeof(Pixel)
    );

    if (image->data == NULL)
    {
        free(image);
        return NULL;
    }

    return image;//eito eta return kore. eta oi allocated space er first element er adress.
  //and eta return koray height width o update hobe
}

static unsigned char clamp_channel(int value)//makes sure je britghtness er value 0 to 255 er moddhe ase
//static karon jeno onno file o eta porte pare
{
    if (value < 0)
        return 0;

    if (value > 255)
        return 255;

    return (unsigned char)value;
}

void grayscale_image(Image *image)
{
    int x;
    int y;

    if (image == NULL || image->data == NULL)
        return;

    for (y = 0; y < image->height; y++)//traverses the image row
    {
        for (x = 0; x < image->width; x++)//column(baki sob gulite x ar y er for loop etai mean kore)
        {
            Pixel *pixel =
                &image->data[y * image->width + x];//targeted pixel ke arekta local variable e save

            int gray =
                (299 * pixel->r +
                 587 * pixel->g +
                 114 * pixel->b) / 1000;//sir er formula apply

            pixel->r = (unsigned char)gray;
            pixel->g = (unsigned char)gray;
            pixel->b = (unsigned char)gray;
        }
    }
}

void adjust_brightness(Image *image, int amount)
{
    int i;
    int total_pixels;

    if (image == NULL || image->data == NULL)
        return;

    total_pixels = image->width * image->height;

    for (i = 0; i < total_pixels; i++)//row and column traverse na kore direct all pixel traverse korse. grayscale eo ei kaj kora jeto
  //2d array er mot represent korte chaisi bole korinai pointer arythmatic 
    {
        image->data[i].r =
            clamp_channel(image->data[i].r + amount);

        image->data[i].g =
            clamp_channel(image->data[i].g + amount);

        image->data[i].b =
            clamp_channel(image->data[i].b + amount);
    }
}

void invert_image(Image *image)
{
    int i;
    int total_pixels;

    if (image == NULL || image->data == NULL)
        return;

    total_pixels = image->width * image->height;

    for (i = 0; i < total_pixels; i++)//same
    {
        image->data[i].r = 255 - image->data[i].r;
        image->data[i].g = 255 - image->data[i].g;
        image->data[i].b = 255 - image->data[i].b;
    }
}

void flip_horizontal(Image *image)
{
    int x;
    int y;

    if (image == NULL || image->data == NULL)
        return;

    for (y = 0; y < image->height; y++)
    {
        for (x = 0; x < image->width / 2; x++)//proti row er majher element fiux rekhe baki gulike  exchange
        {
            int left = y * image->width + x;
            int right =
                y * image->width +
                (image->width - 1 - x);

            Pixel temp = image->data[left];

            image->data[left] = image->data[right];
            image->data[right] = temp;
        }
    }
}

void flip_vertical(Image *image)
{
    int x;
    int y;

    if (image == NULL || image->data == NULL)
        return;

    for (y = 0; y < image->height / 2; y++)//proti column er majher element fix rekhe baki gulike exchange
    {
        for (x = 0; x < image->width; x++)
        {
            int top = y * image->width + x;
            int bottom =
                (image->height - 1 - y) *
                image->width + x;

            Pixel temp = image->data[top];

            image->data[top] = image->data[bottom];
            image->data[bottom] = temp;
        }
    }
}

Image *rotate_image_90(Image *image)//image type return karon different dimension er image create hocche
{
    Image *rotated;
    int new_width;
    int new_height;
    int x;
    int y;

    if (image == NULL || image->data == NULL)
        return NULL;

    new_width = image->height;
    new_height = image->width;

    rotated = create_blank_image(
        new_width,
        new_height
    );//ei blank canvas ta pore original ss ke replace kore,jekhane 
  //height ar wwidht o update hoye jay

    if (rotated == NULL)
        return NULL;

    /*
        Clockwise rotation:
        old(x,y) -> new(height-1-y, x)
    */
    for (y = 0; y < image->height; y++)
    {
        for (x = 0; x < image->width; x++)
        {
            int new_x = image->height - 1 - y;
            int new_y = x;

            rotated->data[
                new_y * new_width + new_x
            ] =
                image->data[
                    y * image->width + x
                ];
        }
    }

    return rotated;//with updated height width,notun ekta image er first adress ta return kortese
}

Image *crop_image(
    Image *image,
    int x,
    int y,
    int width,
    int height
)// etar type diff karon eta original ss ke change kore na ,notun ss banay oita return kore(once again different dimension)
{
    Image *cropped;
    int cx;
    int cy;

    if (image == NULL || image->data == NULL)
        return NULL;

    /*
        The selected rectangle must remain completely
        inside the current image.
    */
    if (x < 0 || y < 0 ||
        width <= 0 || height <= 0 ||
        x + width > image->width ||
        y + height > image->height)//check kore selected area image er vitore ase naki
    {
        return NULL;
    }

    cropped = create_blank_image(width, height);//crop image er size chnage kore tai notun kore different
    //dimension er jayga allocate kora lage
  //and eta widht ar height ke change kore dey
  //check create_blank_space func
    if (cropped == NULL)
        return NULL;

    for (cy = 0; cy < height; cy++)//notun allocated jaygay original ss er designated(cropped) part ta dhukay
    {
        for (cx = 0; cx < width; cx++)
        {
            cropped->data[
                cy * width + cx
            ] =
                image->data[
                    (y + cy) * image->width +
                    (x + cx)
                ];
        }
    }

    return cropped;//with updated height width
}

void blur_image(Image *image)// etate amra original ss edit na kore oita theke value niye 
//oitake manipulate kore temporary space e rakhi. then oi temporary space diye original ke rewrite kori
{
    Image *output;
    int x;
    int y;

    if (image == NULL || image->data == NULL)
        return;

    output = create_blank_image(
        image->width,
        image->height
    );//temporarary space declare

    if (output == NULL)
        return;

  // ei dui loop diye original file er datar value ke change kore temp e rakha hoy. since 3x3 matrix niye kaj kortesi, 
  // value change korle main ss eo value chng hoye jabe, jeta next pixel er calculation ke hamper korbe
  // so we create the blur value for the selected pixel and keep it inside the newly created blank space(this time the dimension is same, still we need blank space)
    for (y = 0; y < image->height; y++)
    {
        for (x = 0; x < image->width; x++)//traverses the pixels in original
        {
            int nx;
            int ny;
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;
            int count = 0;

            for (ny = y - 1; ny <= y + 1; ny++)
            {
                for (nx = x - 1; nx <= x + 1; nx++)//traverses the 3x3 total 9 pixel around the selected image
                {
                    if (nx >= 0 && nx < image->width &&
                        ny >= 0 && ny < image->height)//cehck kore edge or corner e ase kina,thakle oi value guli neyna
                    {
                        Pixel p =
                            image->data[
                                ny * image->width + nx
                            ];//temp ekta variable e orignal image er data guli nilam

                        sum_r += p.r;
                        sum_g += p.g;
                        sum_b += p.b;
                        count++;//total koyta value nisi dekhe
                    }
                }
            }

            output->data[
                y * image->width + x
            ].r = (unsigned char)(sum_r / count);//(red value)faka space e bairer x y looper pixel coordinate wise blurred value dhukay dilam

            output->data[
                y * image->width + x
            ].g = (unsigned char)(sum_g / count);//(green)

            output->data[
                y * image->width + x
            ].b = (unsigned char)(sum_b / count);//(blue)
        }//data ke manipulate kore faka space e rakha done
    }
  //total faka space blurred value diye popoulate kora done

    for (y = 0; y < image->height; y++)
    {
        for (x = 0; x < image->width; x++)
        {
            image->data[
                y * image->width + x
            ] =
                output->data[
                    y * image->width + x
                ];
        }
    }//original ss er pixel ke blurred pixel diye replace korlam

    free_image(output);//temp re faka jayga baniyechilam dlete korlam
}

void sharpen_image(Image *image)//exactly...exactly same as blur. same line to line explanation
{
    Image *output;
    int kernel[3][3] = {
        { 0, -1,  0 },
        {-1,  5, -1 },
        { 0, -1,  0 }
    };
    int x;
    int y;

    if (image == NULL || image->data == NULL)
        return;

    output = create_blank_image(
        image->width,
        image->height
    );

    if (output == NULL)
        return;

    for (y = 0; y < image->height; y++)
    {
        for (x = 0; x < image->width; x++)
        {
            int kx;
            int ky;
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;

            for (ky = -1; ky <= 1; ky++)
            {
                for (kx = -1; kx <= 1; kx++)
                {
                    int nx = x + kx;
                    int ny = y + ky;

                    /*
                        Clamp coordinates at image boundaries.
                    */
                    if (nx < 0) nx = 0;
                    if (nx >= image->width) nx = image->width - 1;
                    if (ny < 0) ny = 0;
                    if (ny >= image->height) ny = image->height - 1;

                    {
                        Pixel p =
                            image->data[
                                ny * image->width + nx
                            ];

                        int weight =
                            kernel[ky + 1][kx + 1];

                        sum_r += p.r * weight;
                        sum_g += p.g * weight;
                        sum_b += p.b * weight;
                    }
                }
            }

            output->data[
                y * image->width + x
            ].r = clamp_channel(sum_r);

            output->data[
                y * image->width + x
            ].g = clamp_channel(sum_g);

            output->data[
                y * image->width + x
            ].b = clamp_channel(sum_b);
        }
    }

    for (y = 0; y < image->height; y++)
    {
        for (x = 0; x < image->width; x++)
        {
            image->data[
                y * image->width + x
            ] =
                output->data[
                    y * image->width + x
                ];
        }
    }

    free_image(output);
}
