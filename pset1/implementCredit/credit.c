#include <cs50.h>
#include <stdio.h>

/**
 * check the validity of credit card number and output name of credit card firm (VISA, MASTERCARD etc.)
 */

long long get_credit_card_number(void);
void validate_credit_card_number(long long int);
int  factor_digits(long long int,int *,int);
bool check_num_by_luhn_algorithm(long long int, int *, int);

int const MAX_SIZE_OF_ARRAY_WITH_CARD_NUMBER = 16;

int main(void){
    validate_credit_card_number(get_credit_card_number());
    
    return 0;
}

long long int get_credit_card_number(){
    printf("Please, enter your credit card number: ");
    long long int credit_card_number = get_long_long();
    
    return credit_card_number;
}

void validate_credit_card_number(long long int credit_card_number){
    
    int factored_number[MAX_SIZE_OF_ARRAY_WITH_CARD_NUMBER];
    int factored_number_len = factor_digits(credit_card_number, factored_number, MAX_SIZE_OF_ARRAY_WITH_CARD_NUMBER); 
    
    // firsts two letters from credit card number
    int check_num = factored_number[factored_number_len-1]*10+factored_number[factored_number_len-2]; 
    
    if( check_num_by_luhn_algorithm(credit_card_number, factored_number, factored_number_len) ){
        if( check_num / 10 == 4 ){
            printf("VISA\n");
        } else if( check_num == 34 || check_num == 37 ){
            printf("AMEX\n");
        } else if ( check_num > 50 && check_num < 56){
            printf("MASTERCARD\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }
}

bool check_num_by_luhn_algorithm(long long int number, int *factored_number, int factored_number_len){
    
    int check_sum = 0;
   
    for (int i = 0; i <= factored_number_len - 1; i++) {
        if(i % 2 == 0){
            check_sum += factored_number[i];
        } else {
            if(factored_number[i]*2 > 9){
                check_sum += 1 + ( factored_number[i] * 2 - 10);
            }else{
                check_sum += factored_number[i] * 2;
            }
        }
    }
    
    return check_sum % 10 == 0 ? true : false;
}

// split int to a digits array, return length of this array

int factor_digits(long long int num, int *digits, int limit){
    
    int digits_count = 0;
    
    if (num == 0) {
        digits[0] = 0;
        return 1;
    }
    while (num > 0 && limit) {
        digits[digits_count++] = num % 10;
        num /= 10;
        limit--;
   }
   
   return num ? 0 : digits_count;
}