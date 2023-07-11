#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int storer = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            storer = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3;
            if ((storer % 10) >= 5)
            storer++;

            storer = storer - (storer % 10);

            image[i][j].rgbtRed = storer;
            image[i][j].rgbtBlue = storer;
            image[i][j].rgbtGreen =storer;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
     int storer = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
          float sepiaRed = 0.0;
          float sepiaBlue = 0.0;
          float sepiaGreen = 0.0;

        //Doing main multiplication
        sepiaRed = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);
        sepiaBlue = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);
        sepiaGreen = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);

        //Checking if not more then 255
        if(sepiaRed > 255)
        sepiaRed = 255;
        if(sepiaGreen > 255)
        sepiaGreen = 255;
        if(sepiaBlue > 255)
        sepiaBlue = 255;

        //Round up
        sepiaRed = (int)round(sepiaRed);
        sepiaBlue = (int)round(sepiaBlue);
        sepiaGreen = (int)round(sepiaGreen);

        //Asighn the colours
        image[i][j].rgbtRed = sepiaRed;
        image[i][j].rgbtBlue = sepiaBlue;
        image[i][j].rgbtGreen = sepiaGreen;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Find mid
    int mid = width/2;
    int swap = 0;

    //Main loop
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < mid; j++)
        {
            swap = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j].rgbtRed;
            image[i][width - j].rgbtRed = swap;

            swap = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j].rgbtBlue;
            image[i][width - j].rgbtBlue = swap;

            swap = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j].rgbtGreen;
            image[i][width - j].rgbtGreen = swap;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // main one
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width;j++)
        {
            int averageRed = 0;
            int averageGreen = 0;
            int averageBlue = 0;
            int cornerCount = 0;
            int iteratorX = -1;
            int iteratorZ = -1;

            //Main loop 3x3

                for(int x = 1; x < 4; x++)
                {

                    for(int z = 1; z < 4;z++)
                    {
                        if (((i + iteratorX) < 0)||((j + iteratorZ) < 0)||((i + iteratorX) > height)||((j + iteratorZ) > width))
                        {
                           iteratorZ++;
                        }
                        else
                        {
                        averageRed += image[i + iteratorX][j + iteratorZ].rgbtRed;
                        averageBlue += image[i + iteratorX][j + iteratorZ].rgbtBlue;
                        averageGreen += image[i + iteratorX][j + iteratorZ].rgbtGreen;
                        iteratorZ++;
                        cornerCount++;
                        }
                    }
                    iteratorX++;
                    iteratorZ = -1;
                }

            //Round and divide to find the number
            averageRed = round(averageRed/cornerCount);
            averageGreen = round(averageGreen/cornerCount);
            averageBlue = round(averageBlue/cornerCount);



            //Asigning correct pixel to copy
            copy[i][j].rgbtRed = averageRed;
            copy[i][j].rgbtBlue = averageBlue;
            copy[i][j].rgbtGreen = averageGreen;


        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width;j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
        }
    }

    return;
}
