#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BLOCK_SIZE = 512;
int jpeg_count = 0;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid input\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
    {
        printf("Couldn't open the file\n");
        return 1;
    }

    unsigned char data[BLOCK_SIZE];
    FILE *jpeg = NULL;

    while (fread(data, 1, BLOCK_SIZE, f) == BLOCK_SIZE)
    {
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && (data[3] & 0xf0) == 0xe0)
        {
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }

            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_count);
            jpeg_count++;

            jpeg = fopen(filename, "w");
        
        }

        if (jpeg != NULL)
        {
            fwrite(data, 1, BLOCK_SIZE, jpeg);
        }
    }

    fclose(f);

    if (jpeg != NULL)
    {
        fclose(jpeg);
    }

    return 0;
}
