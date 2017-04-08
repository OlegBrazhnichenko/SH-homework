#include <cs50.h>
#include <stdio.h>

/** 
 * Calculating amount of bottles that need per one minute of shower
 */

int const BOTTLES_PER_MINUTE = 12;

int main(void){
    printf("Minutes: ");
    printf("Bottles: %i\n", get_int() * BOTTLES_PER_MINUTE);

    return 0;
}