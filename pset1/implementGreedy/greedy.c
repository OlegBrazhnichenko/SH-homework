#include <cs50.h>
#include <stdio.h>

int get_owed_change(void);
void give_change(int);

const int QUARTER = 25;
const int DIME = 10;
const int NICKEL = 5;
const int PENNIE = 1;
const int available_coins[4] = {QUARTER, DIME, NICKEL, PENNIE};

int main(void){
    give_change(get_owed_change());
    
    return 0;
}

int get_owed_change(){
    // double is more accurate, so in case vere arithmetic operations with floats make error, but double not
    double owed_change = 0;  
    do{
        printf("How much change is owed?\n");
        owed_change = get_double();
    }while(owed_change < 0);
    return (int)(owed_change*100);
}

void give_change(int owed_change){
    int coins_amount = 0;
    int coin_type = 0;
    while(owed_change > 0){
        if(owed_change - available_coins[coin_type] < 0){
            coin_type++;
        }else{
            owed_change -= available_coins[coin_type];
            coins_amount++;
        }
    }
    printf("%i\n",coins_amount);
}