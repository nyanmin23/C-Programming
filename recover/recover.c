#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JPEG_SIZE 512
#define HEADER_SIZE 3

typedef uint8_t BYTE;

bool isJPEG(BYTE buffer[HEADER_SIZE]);

const BYTE JPEG_SIGNATURE[HEADER_SIZE] = {0xff, 0xd8, 0xff}; // Standard JPEG file header signature

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    char *filename = argv[1];
    FILE *card = fopen(filename, "r");

    // Exit the program if the file doesn't exist
    if (card == NULL)
    {
        printf("Could not open %s.\n", filename);
        return 2;
    }

    FILE *currentJPEG = NULL;
    BYTE buffer[JPEG_SIZE];
    int count = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, sizeof(BYTE), JPEG_SIZE, card) == JPEG_SIZE)
    {
        // Check for beginning of a JPEG file
        if (isJPEG(buffer))
        {
            if (currentJPEG != NULL)
                fclose(currentJPEG); // Close previous JPEG file, if open

            char filenames[8]; // Buffer for filename ("000.jpg")
            sprintf(filenames, "%03i.jpg", count);
            currentJPEG = fopen(filenames, "w");

            if (currentJPEG == NULL)
            {
                fclose(card);
                if (currentJPEG != NULL)
                    fclose(currentJPEG);
                return 3;
            }
            count++;
        }

        // Create JPEGs from the data
        if (currentJPEG != NULL)
            fwrite(buffer, sizeof(BYTE), JPEG_SIZE, currentJPEG);
    }

    if (currentJPEG != NULL)
        fclose(currentJPEG);

    fclose(card);
    return 0;
}

// Validate JPEG header using fixed first three bytes and fourth byte's high nibble check
bool isJPEG(BYTE buffer[HEADER_SIZE])
{
    return (memcmp(buffer, JPEG_SIGNATURE, HEADER_SIZE) == 0 &&
            (buffer[HEADER_SIZE] & 0xf0) == 0xe0);
}
