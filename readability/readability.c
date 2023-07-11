#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Got user input
    string userinput = get_string("Type your sentence here\n");

    // Got string lenght
    int lenght = strlen(userinput);
    printf("%i\n", lenght);

    // Got number of words
    int space = 1;
    for(int i = 0;userinput[i] != '\0';i++)
    {
        if(isblank(userinput[i]))
        {
            space++;
        }
    }
    
    int sentence = 0;
    // Got number of sentences
    for(int i = 0;userinput[i] != '\0';i++)
    {
        if(userinput[i] =='.' || userinput[i] == '!' || userinput[i] == '?')
        {
            sentence++;
        }
    }


    // Average words length
    float L = 0.0;
    L = ((float)lenght/space*100);


    // Average lenght and sentence
    float S = 0.0;
    S = (((float)sentence/space)*100);


    // Counting coleman index
    float index = 0.0;
    index = ((0.0588 * L) - (0.296 * S) - 15.8);
    if (index >= 1 && index <=16)
    {
    printf("Grade level is %i\n", (int) round(index));
    }
    else if(index < 1)
    {
        printf("Below grade 1 \n");
    }
    else
    {
        printf("Above grade 16 \n");
    }
}

