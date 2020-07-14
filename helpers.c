#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            RGBTRIPLE px = image[i][j];
            int average = (int)round((float)(px.rgbtRed + px.rgbtGreen + px.rgbtBlue) / 3);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }

    return;
}

int cap(int px_val)
{
    return (px_val > 255 ? 255 : px_val);
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // int sepiaRed, sepiaGreen, sepiaBlue;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE px = image[i][j];
            int red = px.rgbtRed;
            int green = px.rgbtGreen;
            int blue = px.rgbtBlue;


            image[i][j].rgbtRed  = cap((int)round(.393 * red + .769 * green + .189 * blue));
            image[i][j].rgbtGreen = cap((int)round(.349 * red + .686 * green + .168 * blue));
            image[i][j].rgbtBlue = cap((int)round(.272 * red + .534 * green + .131 * blue));

            // image[i][j].rgbtRed = cap(sepiaRed);
            // image[i][j].rgbtGreen = cap(sepiaGreen);
            // image[i][j].rgbtBlue = cap(sepiaBlue);
        }
    }


    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // RGBTRIPLE image_cpy[height][width];
    int stop_idx = width / 2; //integer division will return 2 i.e. int 5/ int 2 = 2

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < stop_idx; j++)
        {
            // RGBTRIPLE(*image_tmp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
            RGBTRIPLE image_tmp;
            image_tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = image_tmp;
        }
    }


    return;
}


bool isValidPixel(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}

RGBTRIPLE get_blurred_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE px_tmp;


    int sumRed = 0;
    int sumGreen = 0;
    int sumBlue = 0;
    int px_cnt = 0;
    int kernel_size = 3;

    for (int row = -1; row < kernel_size - 1; row++)
    {
        for (int col = -1; col < kernel_size - 1; col++)
        {
            // int new_i = i + row;
            // int new_j = j + col;

            if (isValidPixel(i+row, j+col, height, width))
            // if (i+row > 0 && i < )
            {
                px_cnt++;

                sumRed += image[i + row][j + col].rgbtRed;
                sumGreen += image[i + row][j + col].rgbtGreen;
                sumBlue += image[i + row][j + col].rgbtBlue;

                // printf("Surrounding pixel count: %i\n", px_cnt);
                // printf("Sum of pixel values : %i", )
            }
        }
    }

    px_tmp.rgbtRed = round((float)sumRed / px_cnt);
    px_tmp.rgbtGreen = round((float)sumGreen / px_cnt);
    px_tmp.rgbtBlue = round((float)sumBlue / px_cnt);

    return px_tmp;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_new[height][width];
    //establish
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            image_new[i][j] = get_blurred_pixel(i, j, height, width, image);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++ )
        {
            image[i][j] = image_new[i][j];
        }
    }

    return;
}
