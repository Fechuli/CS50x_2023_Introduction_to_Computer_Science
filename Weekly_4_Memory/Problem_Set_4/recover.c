#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return (1);
    }

    FILE *file = fopen(argv[1], "r");

    /*-------------------------------
        Check that the file exist
    -------------------------------*/
    if (file == NULL)
    {
        printf("Impossible to open the file\n");
        return (1);
    }

    /*-----------------------------
        Istance of the 512 array
    -----------------------------*/
    BYTE block[512];
    FILE *img = NULL;
    int count = 0;

    while (fread(block, 512, 1, file))
    {

        /*---------------------------------------------
            Check if the beginning of a JPEG is found
        ---------------------------------------------*/
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {

            /*----------------------------------------
                Close the previous file if it exists
            ----------------------------------------*/
            if (img != NULL)
            {
                fclose(img);
            }

            /*------------------------
                Create a new JPEG
            ------------------------*/
            char filename[8];
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create JPEG.\n");
                return 1;
            }
            count++;
        }

        /*---------------------------------------------------------
            Write the block to the JPEG file if one is open
        ---------------------------------------------------------*/
        if (img != NULL)
        {
            fwrite(block, 512, 1, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    fclose(file);
}