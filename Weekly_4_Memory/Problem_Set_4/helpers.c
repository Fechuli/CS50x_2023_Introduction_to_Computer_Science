#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int f = 0; f < width; f++)
        {
            RGBTRIPLE px = image[i][f];
            int gray = round((px.rgbtRed + px.rgbtGreen + px.rgbtBlue) / 3.0);

            image[i][f].rgbtRed = gray;
            image[i][f].rgbtGreen = gray;
            image[i][f].rgbtBlue = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int f = 0; f < width; f++)
        {
            RGBTRIPLE px = image[i][f];

            int originalRed = px.rgbtRed;
            int originalGreen = px.rgbtGreen;
            int originalBlue = px.rgbtBlue;

            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            image[i][f].rgbtRed = fmin(255, sepiaRed);
            image[i][f].rgbtGreen = fmin(255, sepiaGreen);
            image[i][f].rgbtBlue = fmin(255, sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int f = 0; f < width / 2; f++)
        {
            RGBTRIPLE px = image[i][f];
            image[i][f] = image[i][width - f - 1];
            image[i][width - f - 1] = px;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /*----------------------------------
        Istance of the new image
    ----------------------------------*/
    RGBTRIPLE new_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int f = 0; f < width; f++)
        {

            /*-----------------------------
                Initialize color sums to 0
            -----------------------------*/
            float rSum = 0, gSum = 0, bSum = 0;
            int count = 0;

            /*------------------------------------------
                Sum up the colors of surrounding pixels
            ------------------------------------------*/
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    int new_x = i + dx, new_y = f + dy;

                    if (new_x >= 0 && new_x < height && new_y >= 0 && new_y < width)
                    {
                        rSum += image[new_x][new_y].rgbtRed;
                        gSum += image[new_x][new_y].rgbtGreen;
                        bSum += image[new_x][new_y].rgbtBlue;
                        count++;
                    }
                }
            }
            /*---------------------------------------------------
                Calculate average color and set new pixel value
            ---------------------------------------------------*/
            new_image[i][f].rgbtRed = round(rSum / count);
            new_image[i][f].rgbtGreen = round(gSum / count);
            new_image[i][f].rgbtBlue = round(bSum / count);
        }
    }

    /*-------------------------
        Update original image
    -------------------------*/
    for (int i = 0; i < height; i++)
    {
        for (int f = 0; f < width; f++)
        {
            image[i][f] = new_image[i][f];
        }
    }
    return;
}
