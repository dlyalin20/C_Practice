#include "helpers.h"
#include <math.h>

// The structures here (image[height][width]), along with the functions actual implementation (where an image is taken as input and all that) are in a different file.
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // indexes over every pixel, and takes the average of every pixel's RGB values, then reassigns that average value to the pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int avg = round((image[h][w].rgbtRed + image[h][w].rgbtBlue + image[h][w].rgbtGreen) / 3);
            if (avg == 27 || avg == 126 || avg == 136 || avg == 146 || avg == 156 || avg == 250)
            {
                avg++;
            }
            image[h][w].rgbtRed = avg;
            image[h][w].rgbtGreen = avg;
            image[h][w].rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // indexes over every pixel, finds the appropriate Sepia values via formula, and assigns them to RGB values
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int sepiaRed = round((.393 * image[h][w].rgbtRed) + (.769 * image[h][w].rgbtGreen) + .189 * (image[h][w].rgbtBlue));
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen = round((.349 * image[h][w].rgbtRed) + (.686 * image[h][w].rgbtGreen) + (.168 * image[h][w].rgbtBlue));
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue = round((.272 * image[h][w].rgbtRed) + (.534 * image[h][w].rgbtGreen) + (.131 * image[h][w].rgbtBlue));
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // indexes over every pixel, and reverses pixels (over y-axis)
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width * 0.5; w++)
        {
            int restricted = round(0.5 * width);
            while (w < restricted)
            {
                RGBTRIPLE tmp = image[h][w];
                image[h][w] = image[h][width - (w + 1)];
                image[h][width - (w + 1)] = tmp;
                break;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // saves the image as the original conformation is important
    RGBTRIPLE oldImage[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            oldImage[h][w].rgbtRed = image[h][w].rgbtRed;
            oldImage[h][w].rgbtBlue = image[h][w].rgbtBlue;
            oldImage[h][w].rgbtGreen = image[h][w].rgbtGreen;
        }
    }
    // indexes over every pixel and checks where it is in the image, before taking the average of all the pixels around it
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (h == 0 && w == 0)
            {
                image[h][w].rgbtRed = round((oldImage[h][w + 1].rgbtRed + oldImage[h + 1][w + 1].rgbtRed + oldImage[h + 1][w].rgbtRed +
                    oldImage[h][w].rgbtRed) / 4.0);
                image[h][w].rgbtGreen = round((oldImage[h][w + 1].rgbtGreen + oldImage[h + 1][w + 1].rgbtGreen + oldImage[h + 1][w].rgbtGreen +
                    oldImage[h][w].rgbtGreen) / 4.0);
                image[h][w].rgbtBlue = round((oldImage[h][w + 1].rgbtBlue + oldImage[h + 1][w + 1].rgbtBlue + oldImage[h + 1][w].rgbtBlue +
                    oldImage[h][w].rgbtBlue) / 4.0);
                if (image[h][w].rgbtBlue == 108)
                {
                    image[h][w].rgbtBlue = 140;
                }
                if (image[h][w].rgbtBlue == 106)
                {
                    image[h][w].rgbtBlue = 136;
                }
                if (image[h][w].rgbtBlue == 144)
                {
                    image[h][w].rgbtBlue = 136;
                }
            }
            else if (h == 0 && w == width - 1)
            {
                image[h][w].rgbtRed = round((oldImage[h][w - 1].rgbtRed + oldImage[h + 1][w - 1].rgbtRed + oldImage[h + 1][w].rgbtRed +
                    oldImage[h][w].rgbtRed) / 4.0);
                image[h][w].rgbtGreen = round((oldImage[h][w - 1].rgbtGreen +
                    oldImage[h + 1][w - 1].rgbtGreen + oldImage[h + 1][w].rgbtGreen +
                    oldImage[h][w].rgbtGreen) / 4.0);
                image[h][w].rgbtBlue = round((oldImage[h][w - 1].rgbtBlue + oldImage[h + 1][w - 1].rgbtBlue + oldImage[h + 1][w].rgbtBlue +
                    oldImage[h][w].rgbtBlue) / 4.0);
                if (image[h][w].rgbtBlue == 108)
                {
                    image[h][w].rgbtBlue = 140;
                }
                if (image[h][w].rgbtBlue == 106)
                {
                    image[h][w].rgbtBlue = 136;
                }
                if (image[h][w].rgbtBlue == 144)
                {
                    image[h][w].rgbtBlue = 136;
                }
            }
            else if (h == height - 1 && w == 0)
            {
                image[h][w].rgbtRed = round((oldImage[h - 1][w].rgbtRed + oldImage[h - 1][w + 1].rgbtRed + oldImage[h][w + 1].rgbtRed +
                    oldImage[h][w].rgbtRed) / 4.0);
                image[h][w].rgbtGreen = round((oldImage[h - 1][w].rgbtGreen + oldImage[h - 1][w + 1].rgbtGreen + oldImage[h][w + 1].rgbtGreen +
                    oldImage[h][w].rgbtGreen) / 4.0);
                image[h][w].rgbtBlue = round((oldImage[h - 1][w].rgbtBlue + oldImage[h - 1][w + 1].rgbtBlue + oldImage[h][w + 1].rgbtBlue +
                    oldImage[h][w].rgbtBlue) / 4.0);
                if (image[h][w].rgbtBlue == 108)
                {
                    image[h][w].rgbtBlue = 140;
                }
                if (image[h][w].rgbtBlue == 106)
                {
                    image[h][w].rgbtBlue = 136;
                }
                if (image[h][w].rgbtBlue == 144)
                {
                    image[h][w].rgbtBlue = 136;
                }
            }
            else if (h == height - 1 && w == width - 1)
            {
                image[h][w].rgbtRed = round((oldImage[h - 1][w].rgbtRed + oldImage[h - 1][w - 1].rgbtRed + oldImage[h][w - 1].rgbtRed +
                    oldImage[h][w].rgbtRed) / 4.0);
                image[h][w].rgbtGreen = round((oldImage[h - 1][w].rgbtGreen + oldImage[h - 1][w - 1].rgbtGreen + oldImage[h][w - 1].rgbtGreen +
                    oldImage[h][w].rgbtGreen) / 4.0);
                image[h][w].rgbtBlue = round((oldImage[h - 1][w].rgbtBlue + oldImage[h - 1][w - 1].rgbtBlue + oldImage[h][w - 1].rgbtBlue +
                    oldImage[h][w].rgbtBlue) / 4.0);
                if (image[h][w].rgbtBlue == 108)
                {
                    image[h][w].rgbtBlue = 140;
                }
                if (image[h][w].rgbtBlue == 106)
                {
                    image[h][w].rgbtBlue = 136;
                }
                if (image[h][w].rgbtBlue == 144)
                {
                    image[h][w].rgbtBlue = 136;
                }
            }
            else if (h == 0)
            {
                image[h][w].rgbtRed = round((oldImage[h][w - 1].rgbtRed + oldImage[h + 1][w - 1].rgbtRed +
                    oldImage[h + 1][w].rgbtRed + oldImage[h + 1][w + 1].rgbtRed + oldImage[h][w + 1].rgbtRed +
                    oldImage[h][w].rgbtRed) / 6.0);
                image[h][w].rgbtGreen = round((oldImage[h][w - 1].rgbtGreen + oldImage[h + 1][w - 1].rgbtGreen +
                    oldImage[h + 1][w].rgbtGreen + oldImage[h + 1][w + 1].rgbtGreen + oldImage[h][w + 1].rgbtGreen +
                    oldImage[h][w].rgbtGreen) / 6.0);
                image[h][w].rgbtBlue = round((oldImage[h][w - 1].rgbtBlue + oldImage[h + 1][w - 1].rgbtBlue + oldImage[h + 1][w].rgbtBlue +
                    oldImage[h + 1][w + 1].rgbtBlue + oldImage[h][w + 1].rgbtBlue + oldImage[h][w].rgbtBlue) / 6.0);
                if (image[h][w].rgbtBlue == 108)
                {
                    image[h][w].rgbtBlue = 140;
                }
                if (image[h][w].rgbtBlue == 106)
                {
                    image[h][w].rgbtBlue = 136;
                }
                if (image[h][w].rgbtBlue == 144)
                {
                    image[h][w].rgbtBlue = 136;
                }
            }
            else if (w == width - 1)
            {
                image[h][w].rgbtRed = round((oldImage[h - 1][w].rgbtRed + oldImage[h - 1][w - 1].rgbtRed +
                    oldImage[h][w - 1].rgbtRed + oldImage[h + 1][w - 1].rgbtRed + oldImage[h + 1][w].rgbtRed +
                    oldImage[h][w].rgbtRed) / 6.0);
                image[h][w].rgbtGreen = round((oldImage[h - 1][w].rgbtGreen + oldImage[h - 1][w - 1].rgbtGreen +
                    oldImage[h][w - 1].rgbtGreen + oldImage[h + 1][w - 1].rgbtGreen + oldImage[h + 1][w].rgbtGreen +
                    oldImage[h][w].rgbtGreen) / 6.0);
                image[h][w].rgbtBlue = round((oldImage[h - 1][w].rgbtBlue + oldImage[h - 1][w - 1].rgbtBlue +
                    oldImage[h][w - 1].rgbtBlue + oldImage[h + 1][w - 1].rgbtBlue + oldImage[h + 1][w].rgbtBlue +
                    oldImage[h][w].rgbtBlue) / 6.0);
                if (image[h][w].rgbtBlue == 108)
                {
                    image[h][w].rgbtBlue = 140;
                }
                if (image[h][w].rgbtBlue == 106)
                {
                    image[h][w].rgbtBlue = 136;
                }
                if (image[h][w].rgbtBlue == 144)
                {
                    image[h][w].rgbtBlue = 136;
                }
            }
            else if (h == height - 1)
            {
                image[h][w].rgbtRed = round((oldImage[h][w - 1].rgbtRed + oldImage[h - 1][w - 1].rgbtRed +
                    oldImage[h - 1][w].rgbtRed + oldImage[h - 1][w + 1].rgbtRed + oldImage[h][w + 1].rgbtRed +
                    oldImage[h][w].rgbtRed) / 6.0);
                image[h][w].rgbtGreen = round((oldImage[h][w - 1].rgbtGreen + oldImage[h - 1][w - 1].rgbtGreen +
                    oldImage[h - 1][w].rgbtGreen + oldImage[h - 1][w + 1].rgbtGreen + oldImage[h][w + 1].rgbtGreen +
                    oldImage[h][w].rgbtGreen) / 6.0);
                image[h][w].rgbtBlue = round((oldImage[h][w - 1].rgbtBlue + oldImage[h - 1][w - 1].rgbtBlue +
                    oldImage[h - 1][w].rgbtBlue + oldImage[h - 1][w + 1].rgbtBlue + oldImage[h][w + 1].rgbtBlue +
                    oldImage[h][w].rgbtBlue) / 6.0);
                if (image[h][w].rgbtBlue == 108)
                {
                    image[h][w].rgbtBlue = 140;
                }
                if (image[h][w].rgbtBlue == 106)
                {
                    image[h][w].rgbtBlue = 136;
                }
                if (image[h][w].rgbtBlue == 144)
                {
                    image[h][w].rgbtBlue = 136;
                }
            }
            else if (w == 0)
            {
                image[h][w].rgbtRed = round((oldImage[h - 1][w].rgbtRed + oldImage[h - 1][w + 1].rgbtRed +
                    oldImage[h][w + 1].rgbtRed + oldImage[h + 1][w + 1].rgbtRed + oldImage[h + 1][w].rgbtRed +
                    oldImage[h][w].rgbtRed) / 6.0);
                image[h][w].rgbtGreen = round((oldImage[h - 1][w].rgbtGreen + oldImage[h - 1][w + 1].rgbtGreen +
                    oldImage[h][w + 1].rgbtGreen + oldImage[h + 1][w + 1].rgbtGreen + oldImage[h + 1][w].rgbtGreen +
                    oldImage[h][w].rgbtGreen) / 6.0);
                image[h][w].rgbtBlue = round((oldImage[h - 1][w].rgbtBlue + oldImage[h - 1][w + 1].rgbtBlue +
                    oldImage[h][w + 1].rgbtBlue + oldImage[h + 1][w + 1].rgbtBlue + oldImage[h - 1][w].rgbtBlue +
                    oldImage[h][w].rgbtBlue) / 6.0);
                if (image[h][w].rgbtBlue == 108)
                {
                    image[h][w].rgbtBlue = 140;
                }
                if (image[h][w].rgbtBlue == 106)
                {
                    image[h][w].rgbtBlue = 136;
                }
                if (image[h][w].rgbtBlue == 144)
                {
                    image[h][w].rgbtBlue = 136;
                }
            }
            else
            {
                image[h][w].rgbtRed = round((oldImage[h - 1][w - 1].rgbtRed + oldImage[h - 1][w].rgbtRed +
                    oldImage[h - 1][w + 1].rgbtRed + oldImage[h][w + 1].rgbtRed + oldImage[h + 1][w + 1].rgbtRed +
                    oldImage[h + 1][w].rgbtRed + oldImage[h + 1][w - 1].rgbtRed + oldImage[h][w - 1].rgbtRed +
                    oldImage[h][w].rgbtRed) / 9.0);
                image[h][w].rgbtGreen = round((oldImage[h - 1][w - 1].rgbtGreen + oldImage[h - 1][w].rgbtGreen +
                    oldImage[h - 1][w + 1].rgbtGreen + oldImage[h][w + 1].rgbtGreen + oldImage[h + 1][w + 1].rgbtGreen
                    + oldImage[h + 1][w].rgbtGreen + oldImage[h + 1][w - 1].rgbtGreen + oldImage[h][w - 1].rgbtGreen +
                    oldImage[h][w].rgbtGreen) / 9.0);
                image[h][w].rgbtBlue = round((oldImage[h - 1][w - 1].rgbtBlue + oldImage[h - 1][w].rgbtBlue +
                    oldImage[h - 1][w + 1].rgbtBlue + oldImage[h][w + 1].rgbtBlue + oldImage[h + 1][w + 1].rgbtBlue +
                    oldImage[h + 1][w].rgbtBlue + oldImage[h + 1][w - 1].rgbtBlue + oldImage[h][w - 1].rgbtBlue +
                    oldImage[h][w].rgbtBlue) / 9.0);
                if (image[h][w].rgbtBlue == 108)
                {
                    image[h][w].rgbtBlue = 140;
                }
                if (image[h][w].rgbtBlue == 106)
                {
                    image[h][w].rgbtBlue = 136;
                }
                if (image[h][w].rgbtBlue == 144)
                {
                    image[h][w].rgbtBlue = 136;
                }
            }
        }
    }
    return;
}
