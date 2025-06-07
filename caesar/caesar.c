// Step 1: Program Initialization and Header Files
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Step 2: Main Function Implementation
int main(int argc, string argv[])
{
    int key = 0; // Step 2.1: Initialize key variable to store shift value

    // Step 3: Validate Command-Line Argument
    if (argc == 2) // Step 3.1: Ensure exactly one argument is provided
    {
        // Step 4: Check if the argument is a positive integer
        for (int i = 0, length = strlen(argv[1]); i < length; i++)
        {
            if (isdigit(argv[1][i])) // Step 4.1: Verify each character is a digit
            {
                continue;
            }
            else
            {
                printf("Usage: ./caesar key\n"); // Step 4.2: Print error message if invalid
                return 1;                        // Step 4.3: Exit with error code 1
            }
        }

        // Step 5: Convert key from string to integer
        key = atoi(argv[1]); // Step 5.1: Use atoi() to convert argument to an integer

        // Step 6: Get user input for plaintext
        string input = get_string("plaintext:  "); // Step 6.1: Prompt user for input
        int length = strlen(input);                // Step 6.2: Determine the length of input

        printf("ciphertext: "); // Step 6.3: Print ciphertext label

        // Step 7: Apply Caesar Cipher Encryption
        for (int i = 0; i < length; i++)
        {
            if (input[i] >= 'a' && input[i] <= 'z') // Step 7.1: Check if character is lowercase
            {
                printf("%c",
                       'a' + (input[i] - 'a' + key) % 26); // Step 7.2: Shift and print character
                continue;
            }

            if (input[i] >= 'A' && input[i] <= 'Z') // Step 7.3: Check if character is uppercase
            {
                printf("%c",
                       'A' + (input[i] - 'A' + key) % 26); // Step 7.4: Shift and print character
                continue;
            }

            printf("%c", input[i]); // Step 7.5: Print non-alphabetic characters unchanged
        }
        
        printf("\n"); // Step 7.6: Print newline after ciphertext output
        return 0;     // Step 7.7: Successful execution
    }
    else
    {
        printf("Usage: ./caesar key\n"); // Step 8: Print error if argument is missing
        return 1;                        // Step 8.1: Exit with error code 1
    }
}
