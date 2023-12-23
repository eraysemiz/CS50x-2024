#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtBlue == 0x00 && image[i][j].rgbtGreen == 0x00)
            {
                image[i][j].rgbtRed = 0xff;
                image[i][j].rgbtBlue = 0x00;
                image[i][j].rgbtGreen = 0xff;
            }
        }
    }
}

/*
RGBTRIPLE pixel = image[0][0];
    if (pixel.rgbtRed == 0x00 && pixel.rgbtBlue == 0x00 && pixel.rgbtGreen == 0x00)
    {
        pixel.rgbtRed = 0xff;
    }

*/
