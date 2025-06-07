#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string get_card_number(void);
bool is_numeric(const string card_number);
int check_sum(const string card_number);
int get_prefix(const string card_number, int length);
void card_type(const string card_number, int checkSum);

int main(void)
{
    // Get card_number number from user
    string credit_card = get_card_number();
    int checkSum = check_sum(credit_card);

    // Determine card_number type based on number and checksum
    card_type(credit_card, checkSum);
    return 0;
}

// Prompt user for card_number number and validate it's numeric
string get_card_number(void)
{
    string card;
    do
    {
        card = get_string("Number: ");
    }
    while (!is_numeric(card)); // Repeat until a numeric string is entered

    return card;
}

// Check if the input string is numeric
bool is_numeric(const string card_number)
{
    for (int i = 0, length = strlen(card_number); i < length; i++)
    {
        if (!isdigit(card_number[i]))
        {
            return false;
        }
    }

    return true;
}

// Calculate the final checksum by summing all digits
int check_sum(const string card_number)
{
    int total_sum = 0;
    int length = strlen(card_number);
    bool is_second = false;

    for (int i = length - 1; i >= 0; i--)
    {
        int digit = card_number[i] - '0'; // Convert character to integer

        // If it's the second digit from the right, double it
        if (is_second)
        {
            digit *= 2;
            // If doubling results in a number greater than 9, subtract 9
            if (digit > 9)
            {
                digit -= 9;
            }
        }

        total_sum += digit;     // Add to total sum
        is_second = !is_second; // Toggle for next iteration
    }

    return total_sum;
}

int get_prefix(const string card_number, int length)
{
    int prefix = 0;
    for (int i = 0; i < length; i++)
    {
        prefix = prefix * 10 + (card_number[i] - '0');
    }
    
    return prefix;
}

// Identify and print the card_number type if valid
void card_type(const string card_number, int checkSum)
{
    int length = strlen(card_number);
    // If checksum is invalid, card_number is invalid
    if (checkSum % 10 != 0)
    {
        printf("INVALID\n");
        return;
    }

    // Check for Visa (starts with 4, length 13 or 16)
    if ((length == 13 || length == 16) && card_number[0] == '4')
    {
        printf("VISA\n");
        return;
    }

    // Check for AMEX (starts with 34 or 37, length 15)
    int AMEX = get_prefix(card_number, 2);
    if (length == 15 && (AMEX == 34 || AMEX == 37))
    {
        printf("AMEX\n");
        return;
    }

    // Check for Mastercard_number (starts with 51–55, length 16)
    int MASTERCARD = get_prefix(card_number, 2);
    if (length == 16 && (MASTERCARD >= 51 && MASTERCARD <= 55))
    {
        printf("MASTERCARD\n");
        return;
    }

    // If none match, print INVALID
    printf("INVALID\n");
}
