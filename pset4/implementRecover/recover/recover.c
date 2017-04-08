#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;
int new_jpeg_found(BYTE []);
void write_new_jpg(BYTE [], FILE *, int);
void start_recover(FILE *);

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[]){
    
    if (argc != 2){
        fprintf(stderr, "Usage: ./recover infile \n");
        return 1;
    }
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL){
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    start_recover(inptr);
    fclose(inptr);
    
    return 0;
}

void start_recover(FILE *inptr){
    BYTE buffer[BLOCK_SIZE];
    int imagesCounter = 0;
    while(fread(buffer, BLOCK_SIZE, 1, inptr)){
        if( new_jpeg_found(buffer) ){
            write_new_jpg(buffer, inptr, imagesCounter);
            imagesCounter++;
        }
    }
}

void write_new_jpg(BYTE buffer[], FILE *inptr, int imagesCounter){
    char filename[50];
    sprintf(filename,"%03i.jpg",imagesCounter);
    FILE *img = fopen(filename, "w");
    do{
        fwrite(buffer, BLOCK_SIZE, 1, img);
    }
    while(fread(buffer,BLOCK_SIZE,1,inptr) && !new_jpeg_found(buffer));
    fseek(inptr, -BLOCK_SIZE, SEEK_CUR);
    fclose(img);
}

int new_jpeg_found(BYTE buffer[]){
    if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
        return 1;
    }
    return 0;
}