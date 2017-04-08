/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

FILE* open_file(char *file_name, char* mode, int error_code){
    FILE *file = fopen(file_name, mode);
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", file_name);
        exit(error_code);
    }
    return file;
}

BITMAPHEADERS get_headers(FILE *inptr){
    
    BITMAPHEADERS headers;
    fread(&headers.file_header, sizeof(BITMAPFILEHEADER), 1, inptr);
    fread(&headers.info_header, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (headers.file_header.bfType != 0x4d42 || headers.file_header.bfOffBits != 54 || headers.info_header.biSize != 40 || 
        headers.info_header.biBitCount != 24 || headers.info_header.biCompression != 0)
    {
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        exit(4);
    }
    
    return headers;
}

// void update_headers(FILE *outptr, BITMAPHEADERS new_headers){
    
//     fwrite(&new_headers.file_header, sizeof(BITMAPFILEHEADER), 1, outptr);
//     fwrite(&new_headers.file_header, sizeof(BITMAPINFOHEADER), 1, outptr);
    
//     return;
// }


int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }
    int coefficient = atoi(argv[1]);
    if(coefficient < 0 || coefficient >= 100 ){
        fprintf(stderr, "Coefficient must be higher than 0 and less than 100\n");
        return 1;
    }
    
    char *infile = argv[2];
    char *outfile = argv[3];

    FILE *inptr = open_file(infile, "r", 2);
    
    BITMAPHEADERS input_file_headers = get_headers(inptr);

    FILE *outptr = open_file(outfile, "w", 3);

    BITMAPFILEHEADER bf = input_file_headers.file_header;
    BITMAPINFOHEADER bi = input_file_headers.info_header;
    
    int inputPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biWidth *= coefficient;
    bi.biHeight *= coefficient;
    
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // BITMAPHEADERS output_file_headers; 
    
    // output_file_headers.file_header = bf;
    // output_file_headers.info_header = bi;
    
    // update_headers(outptr, output_file_headers);
    
    
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    for (int i = 0, biHeight = abs(bi.biHeight/coefficient); i < biHeight; i++){
        
        for(int k = 0; k < coefficient; k++){
            
            for (int j = 0; j < (bi.biWidth/coefficient); j++){
                
                RGBTRIPLE triple;
                
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    
                for(int m = 0; m < coefficient; m++){
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                }
            }
            for (int n = 0; n < padding; n++){
                fputc(0x00, outptr);
            }
            if(k < coefficient - 1){
                fseek(inptr, -bi.biWidth/coefficient * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        fseek(inptr, inputPadding, SEEK_CUR);
    }
    fclose(inptr);
    fclose(outptr);

    return 0;
}
