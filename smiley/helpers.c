#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate true the canvass
    for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                if (image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00 && image[i][j].rgbtRed == 0x00)
                image[i][j].rgbtGreen = 0xff;
                else if (image[i][j].rgbtGreen == 0xff && image[i][j].rgbtBlue == 0xff && image[i][j].rgbtRed == 0xff)
                {
                    image[i][j].rgbtGreen = 0xDD;
                    image[i][j].rgbtBlue = 0xDD;
                    image[i][j].rgbtRed = 0xDD;
                }
            }
        }
}
