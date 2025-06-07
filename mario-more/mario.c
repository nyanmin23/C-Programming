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

    pyramid(height);
    return 0;
}

void pyramid(int height)
{
    for (int row = 0; row < height; row++)
    {
        // Print right-aligned pyramid
        for (int space = 0; space < height - row - 1; space++)
        {
            printf(" ");
        }

        for (int right = 0; right < row + 1; right++)
        {
            printf("#");
        }

        // Print gap between each pyramid
        printf("  ");

        // Print left-aligned pyramid
        for (int left = 0; left < row + 1; left++)
        {
            printf("#");
        }

        // Print line-break for each row
        printf("\n");
    }
    return;
}
