the basic flow is main>gui>calls functions from operations.c according to the buttons pressed(saves a copy for undo),displays the image,saves and frees the memories

the input is taken by the gui,through the dialogue box which takes the "value"

at first we take header and info header and use the offset to get to the pixel data(Image and Pixel structs are in image.h)

the image is then taken into a local variable called current_image which is Image type data, where the width and height is saved and a pointer(array) of pixel type data takes in all the pixel value in rgb order.(image.c)

gray,flip and brightness work by manipulating the existing memory pixels that was read and sorted in rgb in image->data

but rotate and crop require new width and height so it requires a new blank image(there is a func for that,it also changes the header and info header variables for 
height and width so the image is saved(save function) as a proper bmp(the height and width gets adjusted by the create_blank_image func in operations.c)

blur needs the 9 pixel values including the one in the middle to be averaged . but the change only applies to the middle pixel(0,0). to make sure rest of them are not 
changed ,we once again create a blank image to populate the blurred middle pixel. but the rest of them are taken from the original image. else, the 2nd pixels avg
value will be effected by the blurred one, we dont want it. it also accounts for pixels with missing neighbouring pixel in that 3x3 grid

sharpen takes the exact same approach just takes the weighted avg(using the karnel given by sir(Fuad sir))

crop creates a new blank space, populates a 2d array of pixel type in that space with the pixel from the starting point and uptil the new height





