#include <math.h>

#include "helpers.h"

#define MAX_VALUE 255 // Maximum possible value for a color channel
#define AVERAGE(R, G, B, TOTAL)                                                                    \
    (((R) + (G) + (B)) / (TOTAL)) // Compute average for grayscale conversion
#define SEPIA_RED(R, G, B) (.393 * (R) + .769 * (G) + .189 * (B))   // Compute sepia red value
#define SEPIA_GREEN(R, G, B) (.349 * (R) + .686 * (G) + .168 * (B)) // Compute sepia green value
#define SEPIA_BLUE(R, G, B) (.272 * (R) + .534 * (G) + .131 * (B))  // Compute sepia blue value
#define CONVERT(RESULT)                                                                            \
    ((int) round((RESULT))) // Convert a floating-point result to a rounded integer
#define CLAMP(VALUE)                                                                               \
    ((VALUE) > MAX_VALUE ? MAX_VALUE                                                               \
                         : ((VALUE) < 0 ? 0 : (VALUE))) // Clamp a value between 0 and MAX_VALUE
#define BLUR(SUM, TOTAL)                                                                           \
    ((BYTE) round((float) (SUM) / (TOTAL))) // Calculate the average for blur filtering

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE avg_pixel;
    float colorChannel = 3;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of red, green, and blue
            avg_pixel = CONVERT(AVERAGE(image[i][j].rgbtRed, image[i][j].rgbtGreen,
                                        image[i][j].rgbtBlue, colorChannel));
            // Update pixel values
            image[i][j].rgbtRed = avg_pixel;
            image[i][j].rgbtGreen = avg_pixel;
            image[i][j].rgbtBlue = avg_pixel;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Use the sepia color formulas to compute new color intensities
            sepiaRed = CONVERT(
                SEPIA_RED(image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue));
            sepiaGreen = CONVERT(
                SEPIA_GREEN(image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue));
            sepiaBlue = CONVERT(
                SEPIA_BLUE(image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue));

            // Clamp them to valid ranges and
            // Apply a sepia tone effect to the image by modifying each pixel's RGB values.
            image[i][j].rgbtRed = (BYTE) CLAMP(sepiaRed);
            image[i][j].rgbtGreen = (BYTE) CLAMP(sepiaGreen);
            image[i][j].rgbtBlue = (BYTE) CLAMP(sepiaBlue);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE tmpR, tmpG, tmpB;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Store the pixel value of left half temporarily
            tmpR = image[i][j].rgbtRed;
            tmpG = image[i][j].rgbtGreen;
            tmpB = image[i][j].rgbtBlue;

            // Swap the pixel at column j with the pixel at column (width - j - 1)
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = tmpR;
            image[i][width - j - 1].rgbtGreen = tmpG;
            image[i][width - j - 1].rgbtBlue = tmpB;
        }
    }

    return;
}

// Determine the valid neighboring boundaries for a given index in an image.
void calculate_bounds(int index, int max, int *start, int *end)
{
    // Ensure that the calculated start and end indices do not exceed the image bounds.
    *start = (index > 0) ? index - 1 : index;
    *end = (index < max - 1) ? index + 1 : index;
}

// Create a copy of image
void duplicate(int height, int width, RGBTRIPLE src[height][width], RGBTRIPLE dst[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            dst[i][j] = src[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    duplicate(height, width, image, copy);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;
            int startRow, endRow, startCol, endCol;

            // Fetch boundaries based on index
            calculate_bounds(i, height, &startRow, &endRow);
            calculate_bounds(j, width, &startCol, &endCol);

            // Get total number of neighbors and sum of pixel values
            for (int r = startRow; r <= endRow; r++)
            {
                for (int c = startCol; c <= endCol; c++)
                {
                    sumRed += copy[r][c].rgbtRed;
                    sumGreen += copy[r][c].rgbtGreen;
                    sumBlue += copy[r][c].rgbtBlue;
                    count++;
                }
            }

            // Calculate average and blur image
            image[i][j].rgbtRed = BLUR(sumRed, count);
            image[i][j].rgbtGreen = BLUR(sumGreen, count);
            image[i][j].rgbtBlue = BLUR(sumBlue, count);
        }
    }

    return;
}
