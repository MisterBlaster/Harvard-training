// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    char buffer[HEADER_SIZE];

    if(fread(buffer, 1, HEADER_SIZE, input) != 44)
    {
        printf("failed to read header file \n");
        return 1;
    }

    if(fwrite(buffer, 1, HEADER_SIZE, output) != 44)
    {
        printf("Failed to write the header\n");
        return 1;
    }


    // TODO: Read samples from input file and write updated data to output file




    int16_t testing;

    while(fread(&testing, sizeof(int16_t),1 ,input))
    {
        testing *= factor;

        fwrite(&testing, sizeof(int16_t), 1, output);
    }



    // Close files
    fclose(input);
    fclose(output);
}
