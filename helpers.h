#include "bmp.h"
// #include <stdbool.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]);

// // Sepia helper function to cap any RGB value at 255
// int cap(int px_val);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

//Blur helper function to calculate avg of surrounding including center px
// RGBTRIPLE get_blurred_pixel(int i , int j, int height, int width, RGBTRIPLE image[height][width]);

//Blur helper function to check if pixel is within image boundary
// bool isValidPixel(int i, int j, int height, int width);