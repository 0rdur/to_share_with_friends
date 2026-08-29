#include <stdio.h>

#include <iup.h>

#include "gui.h"
#include "image.h"
#include "operations.h"


/*
    Current image being edited.
*/
Image *current_image = NULL;


/*
    Previous image for one-level Undo.
*/
Image *undo_image = NULL;


/*
    IUP image display.
*/
Ihandle *image_display;


/*
    Main window.
*/
Ihandle *main_dialog;


/*
    Current IUP image.
*/
Ihandle *current_iup_image;


/*
    Function declarations.
*/
void display_image(Image *image);

void save_undo(void);

int open_image_callback(Ihandle *self);
int save_image_callback(Ihandle *self);

int grayscale_callback(Ihandle *self);
int invert_callback(Ihandle *self);

int flip_horizontal_callback(Ihandle *self);
int flip_vertical_callback(Ihandle *self);

int brightness_callback(Ihandle *self);
int rotate_callback(Ihandle *self);
int crop_callback(Ihandle *self);
int blur_callback(Ihandle *self);
int sharpen_callback(Ihandle *self);

int undo_callback(Ihandle *self);


/*
    ====================================================
    SAVE UNDO
    ====================================================
*/

void save_undo(void)
{
    free_image(undo_image);

    undo_image = NULL;

    if (current_image != NULL)
    {
        undo_image = copy_image(current_image);
    }
}


/*
    ====================================================
    DISPLAY IMAGE
    ====================================================
*/

void display_image(Image *image)
{
    Ihandle *new_iup_image;

    if (image == NULL)
        return;

    new_iup_image = IupImageRGB(
        image->width,
        image->height,
        (unsigned char *)image->data
    );

    if (new_iup_image == NULL)
    {
        printf("ERROR: Could not create IUP image.\n");
        return;
    }

    if (current_iup_image != NULL)
    {
        IupDestroy(current_iup_image);
    }

    current_iup_image = new_iup_image;

    IupSetAttributeHandle(
        image_display,
        "IMAGE",
        current_iup_image
    );

    IupUpdate(image_display);
}


/*
    ====================================================
    OPEN IMAGE
    ====================================================
*/

int open_image_callback(Ihandle *self)
{
    Ihandle *file_dialog;
    char *filename;
    Image *new_image;

    file_dialog = IupFileDlg();

    IupSetAttribute(file_dialog, "DIALOGTYPE", "OPEN");
    IupSetAttribute(file_dialog, "FILTER", "*.bmp");
    IupSetAttribute(file_dialog, "FILTERINFO", "24-bit BMP files");
    IupSetAttribute(file_dialog, "TITLE", "Open BMP Image");

    IupPopup(file_dialog, IUP_CENTER, IUP_CENTER);

    if (IupGetInt(file_dialog, "STATUS") == 0)
    {
        filename = IupGetAttribute(file_dialog, "VALUE");

        new_image = load_bmp(filename);

        if (new_image != NULL)
        {
            free_image(current_image);
            current_image = new_image;

            free_image(undo_image);
            undo_image = NULL;

            display_image(current_image);
        }
        else
        {
            IupMessage("Error", "Could not load this BMP image.");
        }
    }

    IupDestroy(file_dialog);
    return IUP_DEFAULT;
}


/*
    ====================================================
    GRAYSCALE
    ====================================================
*/

int grayscale_callback(Ihandle *self)
{
    if (current_image == NULL)
    {
        IupMessage("Grayscale", "No image is loaded.");
        return IUP_DEFAULT;
    }

    save_undo();
    grayscale_image(current_image);
    display_image(current_image);

    return IUP_DEFAULT;
}


/*
    ====================================================
    INVERT
    ====================================================
*/

int invert_callback(Ihandle *self)
{
    if (current_image == NULL)
    {
        IupMessage("Invert", "No image is loaded.");
        return IUP_DEFAULT;
    }

    save_undo();
    invert_image(current_image);
    display_image(current_image);

    return IUP_DEFAULT;
}


/*
    ====================================================
    HORIZONTAL FLIP
    ====================================================
*/

int flip_horizontal_callback(Ihandle *self)
{
    if (current_image == NULL)
    {
        IupMessage("Flip Horizontal", "No image is loaded.");
        return IUP_DEFAULT;
    }

    save_undo();
    flip_horizontal(current_image);
    display_image(current_image);

    return IUP_DEFAULT;
}


/*
    ====================================================
    VERTICAL FLIP
    ====================================================
*/

int flip_vertical_callback(Ihandle *self)
{
    if (current_image == NULL)
    {
        IupMessage("Flip Vertical", "No image is loaded.");
        return IUP_DEFAULT;
    }

    save_undo();
    flip_vertical(current_image);
    display_image(current_image);

    return IUP_DEFAULT;
}


/*
    ====================================================
    BRIGHTNESS
    ====================================================
*/

int brightness_callback(Ihandle *self)
{
    int brightness = 0;

    if (current_image == NULL)
    {
        IupMessage("Brightness", "No image is loaded.");
        return IUP_DEFAULT;
    }

    if (IupGetParam("Brightness Adjustment", NULL, NULL,
                    "Value (-255 to 255): %i[-255,255]\n",
                    &brightness, NULL))
    {
        save_undo();
        adjust_brightness(current_image, brightness);
        display_image(current_image);
    }

    return IUP_DEFAULT;
}


/*
    ====================================================
    ROTATE 90 DEGREES
    ====================================================
*/

int rotate_callback(Ihandle *self)
{
    Image *rotated;

    if (current_image == NULL)
    {
        IupMessage("Rotate", "No image is loaded.");
        return IUP_DEFAULT;
    }

    save_undo();

    rotated = rotate_image_90(current_image);
    if (rotated != NULL)
    {
        free_image(current_image);
        current_image = rotated;
        display_image(current_image);
    }
    else
    {
        IupMessage("Error", "Could not rotate image.");
    }

    return IUP_DEFAULT;
}


/*
    ====================================================
    CROP
    ====================================================
*/

int crop_callback(Ihandle *self)
{
    int x = 0;
    int y = 0;
    int w;
    int h;
    Image *cropped;

    if (current_image == NULL)
    {
        IupMessage("Crop", "No image is loaded.");
        return IUP_DEFAULT;
    }

    w = current_image->width;
    h = current_image->height;

    if (IupGetParam("Crop Image", NULL, NULL,
                    "X Coordinate: %i\n"
                    "Y Coordinate: %i\n"
                    "Width: %i\n"
                    "Height: %i\n",
                    &x, &y, &w, &h, NULL))
    {
        cropped = crop_image(current_image, x, y, w, h);
        if (cropped != NULL)
        {
            save_undo();
            free_image(current_image);
            current_image = cropped;
            display_image(current_image);
        }
        else
        {
            IupMessage("Error", "Invalid crop region or parameters out of bounds.");
        }
    }

    return IUP_DEFAULT;
}


/*
    ====================================================
    BLUR
    ====================================================
*/

int blur_callback(Ihandle *self)
{
    if (current_image == NULL)
    {
        IupMessage("Blur", "No image is loaded.");
        return IUP_DEFAULT;
    }

    save_undo();
    blur_image(current_image);
    display_image(current_image);

    return IUP_DEFAULT;
}


/*
    ====================================================
    SHARPEN
    ====================================================
*/

int sharpen_callback(Ihandle *self)
{
    if (current_image == NULL)
    {
        IupMessage("Sharpen", "No image is loaded.");
        return IUP_DEFAULT;
    }

    save_undo();
    sharpen_image(current_image);
    display_image(current_image);

    return IUP_DEFAULT;
}


/*
    ====================================================
    UNDO
    ====================================================
*/

int undo_callback(Ihandle *self)
{
    Image *temp;

    if (undo_image == NULL)
    {
        IupMessage("Undo", "Nothing to undo.");
        return IUP_DEFAULT;
    }

    temp = current_image;
    current_image = undo_image;
    undo_image = temp;

    free_image(undo_image);
    undo_image = NULL;

    display_image(current_image);

    return IUP_DEFAULT;
}


/*
    ====================================================
    SAVE
    ====================================================
*/

int save_image_callback(Ihandle *self)
{
    const char *filename = "edited_image.bmp";

    if (current_image == NULL)
    {
        IupMessage("Save", "No image is loaded.");
        return IUP_DEFAULT;
    }

    if (save_bmp(filename, current_image))
    {
        IupMessage("Save", "Saved as edited_image.bmp");
    }
    else
    {
        IupMessage("Error", "Could not save image.");
    }

    return IUP_DEFAULT;
}


/*
    ====================================================
    START GUI
    ====================================================
*/

void start_gui(int argc, char **argv)
{
    Ihandle *open_button;
    Ihandle *save_button;

    Ihandle *gray_button;
    Ihandle *invert_button;

    Ihandle *flip_h_button;
    Ihandle *flip_v_button;

    Ihandle *bright_button;
    Ihandle *rotate_button;
    Ihandle *crop_button;
    Ihandle *blur_button;
    Ihandle *sharpen_button;

    Ihandle *undo_button;

    Ihandle *row1;
    Ihandle *row2;

    Ihandle *button_area;
    Ihandle *layout;

    IupOpen(&argc, &argv);

    open_button = IupButton("Open Image", NULL);
    IupSetCallback(open_button, "ACTION", (Icallback)open_image_callback);

    save_button = IupButton("Save", NULL);
    IupSetCallback(save_button, "ACTION", (Icallback)save_image_callback);

    gray_button = IupButton("Grayscale", NULL);
    IupSetCallback(gray_button, "ACTION", (Icallback)grayscale_callback);

    invert_button = IupButton("Invert", NULL);
    IupSetCallback(invert_button, "ACTION", (Icallback)invert_callback);

    flip_h_button = IupButton("Flip Horizontal", NULL);
    IupSetCallback(flip_h_button, "ACTION", (Icallback)flip_horizontal_callback);

    flip_v_button = IupButton("Flip Vertical", NULL);
    IupSetCallback(flip_v_button, "ACTION", (Icallback)flip_vertical_callback);

    bright_button = IupButton("Brightness", NULL);
    IupSetCallback(bright_button, "ACTION", (Icallback)brightness_callback);

    rotate_button = IupButton("Rotate 90°", NULL);
    IupSetCallback(rotate_button, "ACTION", (Icallback)rotate_callback);

    crop_button = IupButton("Crop", NULL);
    IupSetCallback(crop_button, "ACTION", (Icallback)crop_callback);

    blur_button = IupButton("Blur", NULL);
    IupSetCallback(blur_button, "ACTION", (Icallback)blur_callback);

    sharpen_button = IupButton("Sharpen", NULL);
    IupSetCallback(sharpen_button, "ACTION", (Icallback)sharpen_callback);

    undo_button = IupButton("Undo", NULL);
    IupSetCallback(undo_button, "ACTION", (Icallback)undo_callback);

    /* Row 1 Layout */
    row1 = IupHbox(
        open_button,
        save_button,
        undo_button,
        gray_button,
        invert_button,
        NULL
    );
    IupSetAttribute(row1, "GAP", "5");
    IupSetAttribute(row1, "ALIGNMENT", "ACENTER");

    /* Row 2 Layout */
    row2 = IupHbox(
        flip_h_button,
        flip_v_button,
        bright_button,
        rotate_button,
        crop_button,
        blur_button,
        sharpen_button,
        NULL
    );
    IupSetAttribute(row2, "GAP", "5");
    IupSetAttribute(row2, "ALIGNMENT", "ACENTER");

    button_area = IupVbox(row1, row2, NULL);
    IupSetAttribute(button_area, "GAP", "5");
    IupSetAttribute(button_area, "ALIGNMENT", "ACENTER");

    {
        unsigned char pixel[3] = {255, 255, 255};
        current_iup_image = IupImageRGB(1, 1, pixel);
    }

    image_display = IupLabel(NULL);
    IupSetAttributeHandle(image_display, "IMAGE", current_iup_image);
    IupSetAttribute(image_display, "ALIGNMENT", "ACENTER:ACENTER");
    IupSetAttribute(image_display, "RASTERSIZE", "700x500");
    IupSetAttribute(image_display, "MAXSIZE", "700x500");
    IupSetAttribute(image_display, "EXPAND", "NO");

    layout = IupVbox(image_display, button_area, NULL);
    IupSetAttribute(layout, "GAP", "10");
    IupSetAttribute(layout, "MARGIN", "10x10");
    IupSetAttribute(layout, "ALIGNMENT", "ACENTER");

    main_dialog = IupDialog(layout);
    IupSetAttribute(main_dialog, "TITLE", "BMP Image Editor");
    IupSetAttribute(main_dialog, "RASTERSIZE", "900x700");

    IupShowXY(main_dialog, IUP_CENTER, IUP_CENTER);

    IupMainLoop();

    free_image(current_image);
    free_image(undo_image);

    if (current_iup_image != NULL)
    {
        IupDestroy(current_iup_image);
    }

    IupDestroy(main_dialog);
    IupClose();
}