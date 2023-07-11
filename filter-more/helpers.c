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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE Gx[height][width];
    RGBTRIPLE Gy[height][width];
    int treshold = 100;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

            int averageRed = 0;
            int averageGreen = 0;
            int averageBlue = 0;
            int iteratorX = -1;
            int iteratorZ = -1;

            //Main loop 3x3 asigning to Gx

                for(int x = 1; x < 4; x++)
                {

                    for(int z = 1; z < 4;z++)
                    {
                        if (((i + iteratorX) < 0)||((j + iteratorZ) < 0)||((i + iteratorX) > height)||((j + iteratorZ) > width))
                        {
                           iteratorZ++;
                        }
                        else if(x != 2)
                        {
                        averageRed += (image[i + iteratorX][j + iteratorZ].rgbtRed) * iteratorZ;
                        averageBlue += (image[i + iteratorX][j + iteratorZ].rgbtBlue) * iteratorZ;
                        averageGreen += (image[i + iteratorX][j + iteratorZ].rgbtGreen) * iteratorZ;
                        iteratorZ++;
                        }
                        else if( x == 2)
                        {
                        averageRed += (image[i + iteratorX][j + iteratorZ].rgbtRed) * (iteratorZ * 2);
                        averageBlue += (image[i + iteratorX][j + iteratorZ].rgbtBlue) * (iteratorZ * 2);
                        averageGreen += (image[i + iteratorX][j + iteratorZ].rgbtGreen) * (iteratorZ * 2);
                        iteratorZ++;
                        }
                    }
                    iteratorX++;
                    iteratorZ = -1;
            }
            //Round and divide to find the number and check treshold
            if(averageRed < treshold)
            averageRed = 0;
            else if (averageRed < 0 && averageRed > treshold * (-1))
            averageRed = 0;

            if(averageGreen < treshold)
            averageGreen = 0;
            else if (averageGreen < 0 && averageGreen > treshold * (-1))
            averageGreen = 0;

            if(averageBlue < treshold)
            averageBlue = 0;
            else if (averageBlue < 0 && averageBlue > treshold * (-1))
            averageBlue = 0;

            if (averageRed > 255 || averageRed < -255)
            averageRed = 255;
            if (averageGreen > 255 || averageGreen < -255)
            averageGreen = 255;
            if (averageBlue > 255 || averageBlue < -255)
            averageBlue =255;

            //Asigning correct pixel to Gx
            Gx[i][j].rgbtRed = averageRed;
            Gx[i][j].rgbtBlue = averageBlue;
            Gx[i][j].rgbtGreen = averageGreen;

            //finished Gx now practicaly same Gy


             averageRed = 0;
             averageGreen = 0;
             averageBlue = 0;
             iteratorX = -1;
              iteratorZ = -1;

            //Main loop 3x3 asigning to Gy

                for(int x = 1; x < 4; x++)
                {

                    for(int z = 1; z < 4;z++)
                    {
                        if (((i + iteratorX) < 0)||((j + iteratorZ) < 0)||((i + iteratorX) > height)||((j + iteratorZ) > width))
                        {
                           iteratorZ++;
                        }
                        else if(z != 2)
                        {
                        averageRed += (image[i + iteratorX][j + iteratorZ].rgbtRed) * iteratorX;
                        averageBlue += (image[i + iteratorX][j + iteratorZ].rgbtBlue) * iteratorX;
                        averageGreen += (image[i + iteratorX][j + iteratorZ].rgbtGreen) * iteratorX;
                        iteratorZ++;
                        }
                        else if( z == 2)
                        {
                        averageRed += (image[i + iteratorX][j + iteratorZ].rgbtRed) * (iteratorX * 2);
                        averageBlue += (image[i + iteratorX][j + iteratorZ].rgbtBlue) * (iteratorX * 2);
                        averageGreen += (image[i + iteratorX][j + iteratorZ].rgbtGreen) * (iteratorX * 2);
                        iteratorZ++;
                        }
                    }
                    iteratorX++;
                    iteratorZ = -1;
                }
           //Round and divide to find the number and check treshold
            if(averageRed < treshold)
            averageRed = 0;
            else if (averageRed < 0 && averageRed > treshold * (-1))
            averageRed = 0;

            if(averageGreen < treshold)
            averageGreen = 0;
            else if (averageGreen < 0 && averageGreen > treshold * (-1))
            averageGreen = 0;

            if(averageBlue < treshold)
            averageBlue = 0;
            else if (averageBlue < 0 && averageBlue > treshold * (-1))
            averageBlue = 0;

            if (averageRed > 255 || averageRed < -255)
            averageRed = 255;
            if (averageGreen > 255 || averageGreen < -255)
            averageGreen = 255;
            if (averageBlue > 255 || averageBlue < -255)
            averageBlue =255;

            //Asigning correct pixel to Gy
            Gy[i][j].rgbtRed = averageRed;
            Gy[i][j].rgbtBlue = averageBlue;
            Gy[i][j].rgbtGreen = averageGreen;

        }
    }

    //Asigning the numbers tu main image
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {


          image[i][j].rgbtRed = round(sqrt((Gx[i][j].rgbtRed)*(Gx[i][j].rgbtRed))+((Gy[i][j].rgbtRed)*(Gy[i][j].rgbtRed)));
          if (image[i][j].rgbtRed > 255)
          image[i][j].rgbtRed = 255;

          image[i][j].rgbtBlue = round(sqrt((Gx[i][j].rgbtBlue)*(Gx[i][j].rgbtBlue))+((Gy[i][j].rgbtBlue)*(Gy[i][j].rgbtBlue)));
          if (image[i][j].rgbtBlue > 255)
          image[i][j].rgbtBlue = 255;

          image[i][j].rgbtGreen = round(sqrt((Gx[i][j].rgbtGreen)*(Gx[i][j].rgbtGreen))+((Gy[i][j].rgbtGreen)*(Gy[i][j].rgbtGreen)));
          if (image[i][j].rgbtGreen > 255)
          image[i][j].rgbtGreen = 255;

        }
    }





    return;
}
