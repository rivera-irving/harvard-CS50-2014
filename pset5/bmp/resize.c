/*
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
   // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    // check for 1-100 condition
    if (n < 1  || n > 100)
    {
        printf("Usage: n must be > 1 and  < 100\n");
        return 1;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // store old Width
    int oldWidth = bi.biWidth;
    bi.biWidth = bi. biWidth * n;
    
    //store new Width
    int oldHeight = bi.biHeight;
    bi.biHeight = bi.biHeight * n;
    
    //calculate padding
    int newpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) %4;
    int oldpadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4 ) %4;
    
    //calculate new size of bmp
    bi.biSizeImage = abs(bi.biHeight) * bi.biWidth * sizeof(RGBTRIPLE) + newpadding;
    
    //calculate new size of the data file
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    RGBTRIPLE scanline[bi.biWidth];

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
   // int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
        int scannner = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            for (int s = 0; s < n; s++)
            {
                scanline[scannner].rgbtRed = triple.rgbtRed;
                scanline[scannner].rgbtGreen = triple.rgbtGreen;
                scanline[scannner].rgbtBlue = triple.rgbtBlue;
                scannner++;
            }
            
        }
    //read all the scanline        
    for ( int w = 0; w < n; w++)
        {
        //write new size scanline   
        for (scannner = 0; scannner < bi.biWidth; scannner++)
            {
            // write RGB triple to outfile
            fwrite(&scanline[scannner], sizeof(RGBTRIPLE), 1, outptr);
            }

        // write padding
        for (int k = 0; k < newpadding; k++)
            {
            fputc(0x00, outptr);
            }
        }
        // skip over padding, if any
        fseek(inptr, oldpadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
