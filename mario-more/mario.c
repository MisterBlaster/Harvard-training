#include <cs50.h>
#include <stdio.h>

int main(void)

{
    //Input number and declaration
    char c = '#';


    //check the input

    int x = get_int("Input your number between 1 and 8 \n");
    while (x <= 0 || x>8)
    {
        x = get_int("Input correct number between 1 and 8 \n");
    }

    //tell the height of piramid
    printf("The height is %i\n", x);

    //assigned var to help with printing
    int h = x;

    //formula for looping
    for(int i = 0 ; i < x; i++)
    {
        //indenting front
        for (int z = 1; z < h; z++)
        {
        printf(" ");
        }
        h--;


        //first stars
        for(int j =0; j <= i; j++)
        {
            printf("%c", c);
        }


        //making space
        printf("  ");

        //second stars
        for(int j =0; j <= i; j++)
        {
            printf("%c", c);
        }

        printf("\n");
    }


}