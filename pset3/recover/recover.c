#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
// Check if there is 1 and only 1 CLA
    if(argc != 2)
    {
        fprintf(stderr, "Invalid input. Only 1 file accepted.\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if(!inptr)
    {
        fprintf(stderr, "Invalid file type received.\n");
        return 2;
    }

// Create array to store 512 bytes at 1 time
    typedef uint8_t BYTE;
    BYTE indibyte[512];
    int filecount = 0, terminate = 0, sum = 0, fileopen = 0;
    char outfile[8] = "000.jpg";
    FILE *outptr = NULL;

// Creates new images while all 512 bytes are not 0
    while(terminate == 0)
    {
        sum = 0;
        sum = fread(indibyte, 1, 512, inptr);

        if(sum == 0 && feof(inptr))
        {
            break;
        }

// Creates a new file if first 4 bytes matches jpeg file format
        if(indibyte[0] == 0xff && indibyte[1] == 0xd8 && indibyte[2] == 0xff && indibyte[3] >= 0xe0 && indibyte[3] <= 0xef)
        {
            if(filecount != 0)
            {
                fclose(outptr);
                sprintf(outfile, "%03i.jpg", filecount);
            }
            outptr = fopen(outfile, "w");
            filecount++;
            fileopen = 1;
        }

// Writes data in file
        if(fileopen == 1)
        {
            fwrite(indibyte, 1, sum, outptr);

        }
    }

    fclose(outptr);
    fclose(inptr);
    return 0;
}
