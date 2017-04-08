#include <cs50.h>
#include <stdio.h>

/**
 * Build mario half piramid
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
    for(int i = 0; i < pyramid_height; i++){
        build_row(i, pyramid_height);    
    }
}

void build_row(int row_width, int max_pyramid_width){
    // adding 1 for pyramid width and variable i because we have to skip first row
    for (int i = 0; i < max_pyramid_width+1; i++){
        i+1 < max_pyramid_width - row_width ?  
                 putchar(SPASE_SYMBOL_CODE) : putchar(SHARP_SYMBOL_CODE);
    }
    putchar(ENTER_SYMBOL_CODE);
}


