#include <cs50.h>
#include <stdio.h>


    string checkcard(void);
    string validation(void);
    int count(void);
    int maincount(void);

// info american express uses 15 mastercard 16 visa 13 or 16
// visa starts with 4 amex 34 37 mastercard 51 52 53 54 55
// example visa 4003600000000014
// take all second starting from 1 numbers multiply by two if there is two digit number divide by 10 and ad 1
// all other numbers add them together
// and add everything together and should be able devide by 10 without decimal point


    long input;
    long first;
    int numbers = 0;
    long subforinput;
    long backnumber = 0;

 int main(void)
{
    long check = 1000000000000;

    // checking for how many numbers entered
    do
    {
       input = get_long("Input correct card number\n");
       first = input / check;
    }
    while(first< 4||first> 5599);

    // Main function
    maincount();


    // Check if the card is valid
    printf("%s", validation());

    // Check wich card is used and print
    printf("%s\n", checkcard());
}



int maincount(void)
{
    int n = 0;
    long multinumber = 0;

    // Subbing input so don't lose it
    subforinput = input;

    // Creating a loop that devides by 10
    do
    {
        subforinput = subforinput/10;
        numbers++;
    }
    while(subforinput > 1);

    // Extract numbers from input
    subforinput = input;

    // If there is 16 numbers
    if(numbers == 16)
    {
        // Extracted the numbers just two add
         subforinput = (input/10);
         do
         {
             multinumber = (subforinput - subforinput/10*10);
             if(multinumber < 5)
             {
                 backnumber += (multinumber*2);
             }
             else
             {
                 multinumber = (multinumber*2-10+1);
                 backnumber += multinumber;
             }
             subforinput = (subforinput/100);
         }
         while(subforinput > 1);
         subforinput = input;

         // Extract and multiply
         return count();
    }

    // Check if there is 13 or 15
    if(numbers == 13 || numbers == 15)
    {
        // Extracted the numbers just two add
        do
        {
            multinumber = (subforinput - subforinput/10*10);
            if(multinumber < 5)
            {
                backnumber += (multinumber*2);
            } else
            {
                multinumber = (multinumber*2-10+1);
                backnumber += multinumber;
            }
            subforinput = (subforinput/100);
        }
        while(subforinput > 1);
        subforinput = input;

        // Extract and multiply
        subforinput = (input/10);
        return count();
    }
    return n;
}







// Implementing longhs counting every second one and adding up part 2
int count(void)
{
    do
    {
        backnumber += (subforinput - subforinput/10*10);
        subforinput = (subforinput/100);
     }
     while(subforinput > 1);
     return backnumber;
}



// Validation function
string validation(void)
{
     string valid = "";

     backnumber = (backnumber %10);
     if (backnumber == 0)
     {
         printf("Valid Card\n");
     }
     else
     {
         printf("Invalid Card number\n");
     }
      return valid;
}




// Checking card Function
string checkcard(void)
{
    string text = "";
    if(backnumber == 0)
    {
        // Check for visa
        if (first/4==1||(first/4000==1 && first<=4999))
        {
            printf ("It's visa");
        }
        // Check for amex
        else if ((first/340==1 && first<=349)||(first/370==1 && first<=379))
        {
            printf("It's amex");
        }
        // Check for mastercard
        else if ((first/5100==1 && first<=5199)||(first/5200==1 && first<=5299)||(first/5300==1 && first<=5399)||(first/5400==1 && first<=5499)||(first/5500==1 && first<=5599))
        {
            printf("It's mastercard");
        }
        // Card type not recognized
        else
        {
            printf("card type not recognized");
        }
    }

    return text;
}