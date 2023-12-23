#include "helpers.h"
#include <math.h>

// check50 cs50/problems/2023/x/filter/more
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int RED = image[i][j].rgbtRed;
            int BLUE = image[i][j].rgbtBlue;
            int GREEN = image[i][j].rgbtGreen;
            int average = round((RED + BLUE + GREEN) / (float) 3);

            temp[i][j].rgbtRed = average;
            temp[i][j].rgbtBlue = average;
            temp[i][j].rgbtGreen = average;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int a = 0, b = width - 1; a < b; a++, b--)
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
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++) // iterates over rows
    {
        for (int j = 0; j < width; j++) // iterates over columns
        {
            int cellCount = 0; // counts the neighbouring cells
            int avgRed = 0;
            int avgBlue = 0; // stores average value of colors
            int avgGreen = 0;

            for (int a = -1; a <= 1; a++)
            {
                for (int b = -1; b <= 1; b++) // iterates over 3x3 grid around the current pixel
                {
                    int row = i + a; // index of the current iteration
                    int col = j + b;
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        avgRed += image[row][col].rgbtRed;
                        avgBlue += image[row][col].rgbtBlue;
                        avgGreen += image[row][col].rgbtGreen;
                        cellCount++;
                    }
                }
            }
            avgRed = round(avgRed / (float) cellCount);
            avgBlue = round(avgBlue / (float) cellCount);
            avgGreen = round(avgGreen / (float) cellCount);

            temp[i][j].rgbtRed = avgRed;
            temp[i][j].rgbtBlue = avgBlue;
            temp[i][j].rgbtGreen = avgGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++) // iterates over rows 0
    {
        for (int j = 0; j < width; j++) // iterates over columns 0
        {
            int total_red = 0;
            int total_blue = 0;
            int total_green = 0;
            int gx_red = 0, gx_blue = 0, gx_green = 0;
            int gy_red = 0, gy_blue = 0, gy_green = 0;

            for (int a = -1, r = 0; a <= 1; a++, r++) // iterates over 3x3 grid around the current pixel
            {
                for (int b = -1, c = 0; b <= 1; b++, c++)
                {
                    int row = i + a; // index of the current iteration
                    int col = j + b;
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        gx_red += (image[row][col].rgbtRed * Gx[r][c]);
                        gx_blue += (image[row][col].rgbtBlue * Gx[r][c]);
                        gx_green += (image[row][col].rgbtGreen * Gx[r][c]);

                        gy_red += (image[row][col].rgbtRed * Gy[r][c]);
                        gy_blue += (image[row][col].rgbtBlue * Gy[r][c]);
                        gy_green += (image[row][col].rgbtGreen * Gy[r][c]);
                    }
                    else
                    {
                        gx_red += 0;
                        gx_blue += 0;
                        gx_green += 0;

                        gy_red += 0;
                        gy_blue += 0;
                        gy_green += 0;
                    }
                }
            }
            total_red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            total_blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));
            total_green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            if (total_red > 255)
            {
                total_red = 255;
            }
            if (total_blue > 255)
            {
                total_blue = 255;
            }
            if (total_green > 255)
            {
                total_green = 255;
            }

            temp[i][j].rgbtRed = total_red;
            temp[i][j].rgbtBlue = total_blue;
            temp[i][j].rgbtGreen = total_green;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
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
