#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int convert(string input);
int subforint = 0;
int converted = 0;
int answer = 0;
int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }
    subforint = strlen(input);
    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{

    subforint--;
    if(subforint < 0)
    {
       return answer;
    }
    converted = converted*10 +((int)input[subforint]-'0');
    convert(input);

         answer = (answer*10+(converted % 10));
         converted = converted/10;

    return answer;

}