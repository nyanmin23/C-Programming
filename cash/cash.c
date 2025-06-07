#include <cs50.h>
#include <stdio.h>

void calculateChange(int cent);

enum cents { quarter = 25, nickel = 10, dime = 5, penny = 1 };

int main(void)
{
    int change;

    do
    {
        // Prompt the user for change owed, in cents
        change = get_int("Change owed: ");
        if (change == 0)
        {
            printf("No changes owed.\n");
            break;
        }
        else
        {
            calculateChange(change);
        }
    }
    while (change < 0);
}

void calculateChange(int cent)
{
    int quarters = 0;
    int nickels = 0;
    int dimes = 0;
    int pennies = 0;

    // Calculate how many quarters you should give customer
    while (cent >= quarter)
    {
        // Subtract the value of those quarters from cents
        cent -= quarter;
        quarters++;
    }
    // Calculate how many nickels you should give customer
    while (cent >= nickel)
    {
        // Subtract the value of those nickels from remaining cents
        cent -= nickel;
        nickels++;
    }
    // Calculate how many dimes you should give customer
    while (cent >= dime)
    {
        // Subtract the value of those dimes from remaining cents
        cent -= dime;
        dimes++;
    }
    // Calculate how many pennies you should give customer
    while (cent >= penny)
    {
        // Subtract the value of those pennies from remaining cents
        cent -= penny;
        pennies++;
    }
    // Sum the number of quarters, dimes, nickels, and pennies used
    // Print that sum
    printf("%d\n", quarters + nickels + dimes + pennies);
}
