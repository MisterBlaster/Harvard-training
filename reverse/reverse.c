#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("The input was incorrect \n ");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1],"rb");
    if(input == NULL)
    {
        printf("wrong file \n");
        return 1;
    }

    // Read header
    WAVHEADER header;
    if (fread(&header,sizeof(WAVHEADER),1,input) != 1)
    {
        printf("Didn't read the WAVE header \n ");
        fclose(input);
        return 1;
    }

    // Use check_format to ensure WAV format
    if(!check_format(header))
    {
        fclose(input);
        return 1;
    }


    // Open output file for writing
    FILE *output = fopen(argv[2],"wb");
    if(output == NULL)
    {
        printf("didnt open properly \n");
        return 1;
    }

    // Write header to file
    fwrite(&header,sizeof(WAVHEADER),1,output);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file

    // First seek to the end of file
    if(fseek(input, HEADER_SIZE, SEEK_END))
    return 1;

    BYTE AudioArr[block_size];
    while(ftell(input) - block_size > sizeof(header))
    {
        if(fseek(input, - 2 * block_size, SEEK_CUR))
        {
            return 1;
        }
        fread(AudioArr, block_size, 1, input);
        fwrite(AudioArr, block_size, 1 ,output);
    }



    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{

    if (memcmp(header.format, "WAVE", 4) != 0)
    {
        printf("it's not wav file\n");
        return 0;
    }
    //returns 1 if it is wav file
    return 1;
}

int get_block_size(WAVHEADER header)
{
    int bytesPerSample = header.bitsPerSample / 8;
    int numChannels = header.numChannels;

    return bytesPerSample * numChannels;
}