# [Filter]()

Filter is a very interesting exercise that focuses on editing one or more images. 
During the course we realized that each image is made of pixels and each pixel has a color.
These colors are editable and adjustable. Not surprisingly we will have to make filters, the classics to be precise. 
So black and white, sepia, mirror mode and blur

This exercise contained multiple files but the one concerned is helpers.c

The file contains 4 simple functions, one per filter.

Actually there is little to tell, the algorithms by which you change the pixel color can easily be found online. 
It is, however, interesting to look at the prototypes of the functions we are going to use. 
It is from these that we can understand how the mechanism works. 
The functions take as parameters the height, the width and the RGBTRIPLE data structure, which simply represents each individual pixel of the image in question. 

# [Recover]()

The recover exercise, as per its name, has the task of recovering a deleted image.
As a first step, the program checks the number of arguments passed to it. 
If they are other than 2, the program crashes and prints to the console the correct usage. 
Otherwise it moves on.

We open our FILE with the fopen function in read mode.
After that there is a second check for the condition where the file, for whatever reason, is unopenable.

We initialize an array of 512 bytes.
This array checks, byte by byte, whether a .jpg file starts.
If it is found we proceed to create a new .jpg file.