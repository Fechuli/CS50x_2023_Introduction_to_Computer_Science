// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    /*--------------------------------
        Check command-line arguments
    --------------------------------*/
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return (1);
    }

    /*-------------------------------------------
        Open files and determine scaling factor
    -------------------------------------------*/
    /*---------
       Input
    ----------*/
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Could not open file.\n");
        return (1);
    }

    /*---------
       Output
    ----------*/
    FILE *output = fopen(argv[2], "w");

    if (output == NULL)
    {
        printf("Could not open file.\n");
        return (1);
    }

    /*-----------------------------------------------------------------
       Converts the third argument of the main function in float (vol)
    -----------------------------------------------------------------*/
    float factor = atof(argv[3]);
    /*--------------------------------------------------------
       We make sure that the header is readable and writable
    --------------------------------------------------------*/
    uint8_t header[HEADER_SIZE];

    if (fread(header, sizeof(uint8_t), HEADER_SIZE, input) != HEADER_SIZE)
    {
        printf("Impossible to read header\n");
        fclose(input);
        fclose(output);
        return (1);
    }

    if (fwrite(header, sizeof(uint8_t), HEADER_SIZE, output) != HEADER_SIZE)
    {
        printf("Impossible to write header\n");
        fclose(input);
        fclose(output);
        return (1);
    }

    /*---------
       Samples
    ----------*/
    int16_t buffer;

    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        if (fwrite(&buffer, sizeof(int16_t), 1, output) != 1)
        {
            printf("Impossible to write data to output file.\n");
            fclose(input);
            fclose(output);
            return (1);
        }
    }

    /*--------------
       Close files
    --------------*/
    fclose(input);
    fclose(output);

    return (0);
}
