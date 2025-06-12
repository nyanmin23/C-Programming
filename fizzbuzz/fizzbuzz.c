#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int input;

    do 
    {
        input = get_int("Enter Number: ");
    }
    while(input < 0 || input > 100);

    for (int i = 0; i <= input; i++)
    {
        if (i % 3 == 0)
        {
            printf("Fizz\n");
        }
        if (i % 5 == 0)
        {
            printf("Buzz\n");
        }
        if (i % 3 == 0  && i % 5 == 0)
        {
            printf("FizzBuzz\n");
        }
        else
        {
            printf("%i\n", i);
        }
    }
    
    return 0;
}
