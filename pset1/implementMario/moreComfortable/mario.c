#include <cs50.h>
#include <stdio.h>

/**
 * Build mario piramid
 */ 

 int get_height(void);
void build_pyramid(int);
void build_row(int, int);
bool validate_height(int);

int const PYRAMID_MAX_HEIGHT = 23;
int const PYRAMID_MIN_HEIGHT = 0;
int const SHARP_SYMBOL_CODE  = 35;
int const SPASE_SYMBOL_CODE  = 32; 
int const ENTER_SYMBOL_CODE  = 10;

int main(void){
    build_pyramid(get_height());
    
    return 0;
}

int get_height(void){
    int height = 0;
    do{
        printf("Please, enter the pyramid height: ");
        height = get_int();    
    }while(!validate_height(height));
    
    return height;
}

bool validate_height(int height){
    if(height > PYRAMID_MAX_HEIGHT){
        printf("Error, given size is greater than maximum height \n");
        
        return false;
    }else if(height < PYRAMID_MIN_HEIGHT){
        printf("Error, given size is lower than minimum height \n");
        
        return false;
    }
    
    return true;
}

void build_pyramid(int pyramid_height){
    for(int row_num = 1; row_num <= pyramid_height; row_num++){
        build_row(row_num, pyramid_height);    
    }
}

void build_row(int row_num, int pyramid_height){
    int half_pyramid_width = pyramid_height;
    int sharps_num = half_pyramid_width - (half_pyramid_width - row_num);
    int spaces_num =  half_pyramid_width - row_num;
    for (int i = 0; i < half_pyramid_width; i++){
        if( i >= spaces_num ){
            putchar(SHARP_SYMBOL_CODE);
        } else {
            putchar(SPASE_SYMBOL_CODE);
        }
    }
    putchar(SPASE_SYMBOL_CODE);
    putchar(SPASE_SYMBOL_CODE);
    for (int i = 0; i < sharps_num; i++){
        putchar(SHARP_SYMBOL_CODE);
    }
    putchar(ENTER_SYMBOL_CODE); // end of row
}


