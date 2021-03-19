#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[2])
{
    // if two args are not submitted, then  usge error is returned
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // opens the file with deleted data to be read
    FILE *file = fopen(argv[1], "r");
    // if the file pointer is NULL, then the file has not been found
    if (file == NULL)
    {
        printf("File not found\n");
    }
    // opens a file pointer to the recovered image
    FILE *image;
    // creates a 512 byte buffer
    BYTE buffer[512];
    // NULL pointer
    char *name= malloc(sizeof(unsigned long));
    // counter for number of files
    int n = 0;
    // while we haven't reached the end of the file
    while(fread(&buffer, sizeof(BYTE), 512, file) == 512)
    {
        // if the start of the buffer is the start of a file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1 || buffer[3] == 0xe2 || buffer[3] == 0xe3 || buffer[3] == 0xe4 || buffer[3] == 0xe5 || buffer[3] == 0xe6 || buffer[3] == 0xe7 || buffer[3] == 0xe8 || buffer[3] == 0xe9 || buffer[3] == 0xea || buffer[3] == 0xeb || buffer[3] == 0xec || buffer[3] == 0xed || buffer[3] == 0xee || buffer[3] == 0xef))
        {
            // stores the name of the file as a integer equal to n  to three places (ex: 000.jpg, 042.jpg, etc.)
            sprintf(name, "%03d.jpg", n);
            // image has the name of opened name
            image = fopen(name, "w");
            // writes all the buffer contents into the image
            fwrite(&buffer, sizeof(BYTE), 512, image);
            // increment counter
            n++;
        }
        if (n > 0)
        {
            // append buffer to current file with name
            image = fopen(name, "a");
            fwrite(&buffer, sizeof(BYTE), 512, image);
            fclose(image);
        }
    }
    free(name);
    fclose(file);
    return 0;
}
