#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    // created 1 array with 7 chars to read the number plate and ad line break and null
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];
    
    // point nameofvar command argument mode
    FILE *infile = fopen(argv[1], "r");

    int idx = 0;
    //           some buffer array -- how many -- what size -- from were
    while (fread(buffer, 1, 7, infile) == 7)
    {

        plates[idx] = malloc(sizeof(char)*8);
        // Replace '\n' with '\0'
        buffer[6] = '\0';


        // coppy from buffer to plates array
        strcpy(plates[idx], buffer);

        idx++;
        free(plates[idx]);

    }
   // char *sub = NULL;
    for (int i = 0; i < 8; i++)
    {

        printf("%s\n", plates[i]);
    }

}
