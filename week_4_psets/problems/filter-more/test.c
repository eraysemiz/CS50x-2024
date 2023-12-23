#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int RED = image[i][j].rgbtRed;
            int BLUE = image[i][j].rgbtBlue;
            int GREEN = image[i][j].rgbtGreen;
            BYTE average = (RED + BLUE + GREEN) / 3;

            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int a = 0, b = width ; a < b; a++, b--)
        {
            BYTE tempRed = image[i][a].rgbtRed;
            BYTE tempBlue = image[i][a].rgbtBlue;
            BYTE tempGreen = image[i][a].rgbtGreen;

            image[i][a].rgbtRed = image[i][b].rgbtRed;
            image[i][a].rgbtBlue = image[i][b].rgbtBlue;
            image[i][a].rgbtGreen = image[i][b].rgbtGreen;

            image[i][b].rgbtRed = tempRed;
            image[i][b].rgbtBlue = tempBlue;
            image[i][b].rgbtGreen = tempGreen;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // iterates over rows
    {
        for (int j = 0; j < width; j++) // iterates over columns
        {
            int cellCount = 0; // counts the neighbouring cells
            int avgRed = 0;
            int avgBlue = 0;    // stores average value of colors
            int avgGreen = 0;

            for (int a = -1; a <= 1; a++)
            {                                   // iterates over 3x3 grid around the current pixel
                for(int b = -1; b <= 1; b++)
                {
                    int row = i + a;            // index of the current iteration
                    int col = j + b;
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        avgRed += (int)image[row][col].rgbtRed;
                        avgBlue += (int)image[row][col].rgbtBlue;
                        avgGreen += (int)image[row][col].rgbtGreen;
                        cellCount++;
                    }
                }

            }
            avgRed /= cellCount;
            avgBlue /= cellCount;
            avgGreen /= cellCount;

            image[i][j].rgbtRed = (BYTE)avgRed;
            image[i][j].rgbtBlue = (BYTE)avgBlue;
            image[i][j].rgbtGreen = (BYTE)avgGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx_multiply[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};     // multiplying values for calculating Gx and Gy
    int gy_multiply[9] = {-1, -2, -1, 0, 0, 0, 1, 2 ,1};

    for (int i = 0; i < height; i++) // iterates over rows
    {
        for (int j = 0; j < width; j++) // iterates over columns
        {
            int g_index = 0;
            int gx_red = 0, gx_blue = 0, gx_green = 0;
            int gy_red = 0, gy_blue = 0, gy_green = 0;

            for (int a = -1; a <= 1; a++)
            {                                   // iterates over 3x3 grid around the current pixel
                for(int b = -1; b <= 1; b++)
                {
                    int row = i + a;             // index of the current iteration
                    int col = j + b;
                    if (row < 0 || row > height || col < 0 || col > width)
                    {
                        gx_red += 0;        // if the current index out of bounds count it as a black pixel
                        gx_blue += 0;
                        gx_green += 0;
                        gy_red += 0;
                        gy_blue += 0;
                        gy_green += 0;
                    }
                    else
                    {
                        gx_red += ((int)image[row][col].rgbtRed) * gx_multiply[g_index];
                        gx_blue += ((int)image[row][col].rgbtBlue) * gx_multiply[g_index];
                        gx_green += ((int)image[row][col].rgbtGreen) * gx_multiply[g_index];
                        gy_red += ((int)image[row][col].rgbtRed) * gy_multiply[g_index];
                        gy_blue += ((int)image[row][col].rgbtBlue) * gy_multiply[g_index];
                        gy_green += ((int)image[row][col].rgbtGreen) * gy_multiply[g_index];

                    }

                    g_index++;
                }
            }
            g_index = 0;

            int avg_red = (int)sqrt(gx_red * gx_red + gy_red * gy_red);
            int avg_blue = (int)sqrt(gx_blue * gx_blue + gy_blue *gy_blue);;
            int avg_green = (int)sqrt(gx_green * gx_green + gy_green * gy_green);;

            if (avg_red > 255)
            {
                avg_red = 255;
            }

            if (avg_blue > 255)
            {
                avg_blue = 255;
            }

            if (avg_green > 255)
            {
                avg_green = 255;
            }

            image[i][j].rgbtRed = avg_red;
            image[i][j].rgbtBlue = avg_blue;
            image[i][j].rgbtGreen = avg_green;

        }
    }


    return;
}

// row >= 0 && row < height && col >= 0 && col < width
/*
0,0     0,1     0,2
1,0     1,1     1,2
2,0     2,1     2,2

matrisin 9 elemanının tek tek kırmızı mavi ve yeşil ortalamalarını hesapla ortayan çıkan ortalamları ana elemana yaz
*/
