#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
// Check for 4 and only 4 arguments
    if(argc != 4)
    {
        fprintf(stderr, "Invalid arguments. Input scale factor, original and destination file names.\n");
        return 1;
    }
    int scale = atoi(argv[1]);
    if((!(scale > 0 && scale <= 100)))
    {
        fprintf(stderr, "Invalid scale factor. Scale factor must be positive integer of at most 100.\n");
        return 1;
    }

// Save the name of the files
    char *infile = argv[2];
    char *outfile = argv[3];

// Open the 2 files, but close opened files and terminate exe should any be invalid
    FILE *inptr = fopen(infile, "r");
    if(!inptr)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    FILE *outptr = fopen(outfile, "w");
    if(!outptr)
    {
        fprintf(stderr, "Could not create %s.\n", outfile);
        fclose(inptr);
        return 3;
    }

//Reads bitmapfileheader and info header of infile
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

// Check if the the file is (likely) a 24-bit bmp file
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
       bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

// Determine padding size for og image and determine padding needed for scaled image
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int reqpd = (4 - (scale * bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    LONG oldwidth = bi.biWidth;
    LONG oldheight = bi.biHeight;

// Edit bf and bi info to suit scale factor
    bi.biWidth *= scale;
    bi.biHeight *= scale;
    bi.biSizeImage = (sizeof(RGBTRIPLE) * bi.biWidth + reqpd) * (abs(bi.biHeight));
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;

// Write bitmapfileheader and info header into outfile
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE pixel[bi.biWidth];

// For iterations equal to height of og image, construct **scale amounts of scanline
    for(int i = 0; i < abs(oldheight); i++)
    {

// Construct an array of pixels for the current scanline
        for(int j = 0; j < oldwidth; j++)
        {
            fread(&pixel[j * scale], sizeof(RGBTRIPLE), 1, inptr);
            for(int k = 0; k < scale - 1; k++)
            {
                pixel[j * scale + k + 1] = pixel[j * scale];
            }
        }

// Implement that array of pixels and add padding for *scale number of times
        for(int l = 0; l < scale; l++)
        {
            fwrite(&pixel, sizeof(RGBTRIPLE), bi.biWidth, outptr);

            // Add padding
            for (int m = 0; m < reqpd; m++)
            {
                fputc(0x00, outptr);
            }
        }

// skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }


// close infile
    fclose(inptr);

// close outfile
    fclose(outptr);

// success
    return 0;

}
