#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int check_readability(int x, string y);
int check_sentence(char l);
bool check_punct(char p);
int count_word(int i, string w);
int assess_grading(int s, int w, int l);

// Global variables used to keep track of counts across functions.
int sentence = 0; // To count sentence terminating characters.
int word = 0;     // To count word boundaries.
int letter = 0;   // To count individual letters.
int n = 0;        // A helper index used in word counting.

int main(void)
{
    string text; // To hold the user input string
    int length;  // Length of the input string

    // Prompt repeatedly until the input does not start or end with a space.
    do
    {
        text = get_string("Text: ");
        length = strlen(text);
    }
    while (text[0] == ' ' || text[length - 1] == ' ');

    // Call function to process readability measurements on the input text.
    check_readability(length, text);
}

// This function iterates through each character in the text and updates the global counts.
// Parameter x: the length of the text
// Parameter y: the text itself (user input)
int check_readability(int x, string y)
{
    for (int i = 0; i < x; i++)
    {
        // Ensure the loop stops at the null terminator.
        if (y[i] != '\0')
        {
            // Add to sentence count if the character is a sentence ending punctuation.
            sentence += check_sentence(y[i]);

            // Check if the current character indicates a word boundary and update count.
            word += count_word(i, y);

            // If the character is any punctuation or a space, skip counting it as a letter.
            if (check_punct(y[i]))
            {
                continue;
            }
            // Otherwise, consider it a letter and increment the letter count.
            letter++;
        }
    }
    // After processing all characters, compute and display the readability grade.
    assess_grading(sentence, word, letter);
    return 0;
}

// This function calculates and prints the readability grade using a formula similar to the
// Coleman-Liau index. Parameters: s (sentence count), w (word count), l (letter count)
int assess_grading(int s, int w, int l)
{
    // Calculate average letters per 100 words.
    float L = (((float) l / (float) w) * 100);
    // Calculate average sentences per 100 words.
    float S = (((float) s / (float) w) * 100);
    // Calculate the readability index using coefficients that factor in L and S.
    float G = (0.0588 * L - 0.296 * S - 15.8);
    // Round the index to the nearest whole number.
    int index = (int) (round(G));

    // Use a conditional operator to check grade boundaries:
    // If the index falls between greater than 1 and less than or equal to 10, print "Grade X".
    // Otherwise, if index is 1 or lower, print "Before Grade 1".
    (index > 1 && index <= 10) ? printf("Grade %i\n", index) : printf("Before Grade 1\n");

    // If the index exceeds 10, it is reported as "Grade 16+".
    if (index > 10)
    {
        printf("Grade 16+\n");
    }
    return 0;
}

// This helper function checks if a character is a sentence delimiter.
// Parameter l: a single character from the text.
// Returns 1 if the character is a period, exclamation point, or question mark; otherwise returns 0.
int check_sentence(char l)
{
    int sentences = 0;
    if (l == '!' || l == '.' || l == '?')
    {
        sentences++;
    }
    return sentences;
}

// This function checks if a character is punctuation or a space.
// Parameter p: the character to check.
// Returns true if p is punctuation (using ispunct) or if it is a space.
bool check_punct(char p)
{
    if (ispunct(p) || p == ' ')
    {
        return true;
    }
    return false;
}

// This function uses delimiters to determine word boundaries.
// Parameter i: the current index in the string.
// Parameter w: the input text.
// If the character at index i is a space, comma, or sentence punctuation,
// and the preceding character is an alphabetic character (ensuring the word was valid),
// then it counts as the end of a word.
int count_word(int i, string w)
{
    int words = 0;
    if (w[i] == ' ' || w[i] == ',' || check_sentence(w[i]))
    {
        n = i; // Record the current index as a potential word boundary.
        // Only count if the previous character is alphabetic.
        if (isalpha(w[n - 1]))
        {
            words++;
        }
    }
    return words;
}
