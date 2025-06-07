#include <cs50.h>
#include <stdio.h>

void pyramid(int height);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // Print single-sided pyramid
    pyramid(height);
    return 0;
}

void pyramid(int height)
{
    for (int row = 0; row < height; row++)
    {
        // Print left-aligned pyramid
        for (int space = 0; space < height - row - 1; space++)
        {
            // Print spaces
            printf(" ");
        }

        for (int brick = 0; brick < row + 1; brick++)
        {
            // Print bricks
            printf("#");
        }
        // Print line-break for each row
        printf("\n");
    }

    return;
}
