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

BITMAPHEADERS resize_headers(BITMAPHEADERS input_file_headers, int coefficient){
    
    BITMAPHEADERS resized_headers;
    resized_headers.info_header.biWidth = input_file_headers.info_header.biWidth * coefficient;
    resized_headers.info_header.biHeight = input_file_headers.info_header.biWidth * coefficient;
    int padding = (4 - (resized_headers.info_header.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    resized_headers.info_header.biSizeImage = ((sizeof(RGBTRIPLE) * resized_headers.info_header.biWidth) + padding) * abs(resized_headers.info_header.biHeight);
    
    resized_headers.file_header.bfSize = resized_headers.info_header.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    return resized_headers;
}

void update_headers(FILE *outptr, BITMAPHEADERS new_headers){
    
    fwrite(&new_headers.file_header, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&new_headers.file_header, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    return;
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
    
    int inputPadding = (4 - (input_file_headers.info_header.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    BITMAPHEADERS output_file_headers = resize_headers(input_file_headers, coefficient); 
    
    update_headers(outptr, output_file_headers);
    
    BITMAPINFOHEADER bi = output_file_headers.info_header;
    BITMAPFILEHEADER bf = output_file_headers.file_header;
    
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++){
        for(int k = 0; k < coefficient; k++){
            for (int j = 0; j < (bi.biWidth); j++){
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    
                for(int m = 0; m < coefficient; m++){
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                }
            }
            for (int n = 0; n < padding; n++){
                fputc(0x00, outptr);
            }
            if(k < coefficient - 1){
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        fseek(inptr, inputPadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
