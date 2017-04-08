#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void fill_codes_array(int* char_codes, char* chars, unsigned long char_codes_length){
    
    for(int i = 0; i < char_codes_length; i++){
        if(!isalpha(chars[i])){
            printf("Usage: ./caesar k\n");
            exit(1);
        }
        char_codes[i] = (int)tolower(chars[i])-97;
        
    }
}

string encrypt_string(string str, int* secret_keys, int keys_len) {
    int k = 0;
    for (int i = 0; i < strlen(str); i++) {
        if(isalpha(str[i])){
            if(isupper(str[i]) > 0){
                str[i] = tolower(str[i]) + secret_keys[k]; 
                if(!isalpha(str[i])){
                    str[i] -= 26;
                }
                str[i] = toupper(str[i]);
            }else{
                str[i] = str[i] + secret_keys[k];          
                if(!isalpha(str[i])){
                    str[i] -= 26;
                }
            }
            k++;
            if(k > keys_len-1){
                k=0;
            }    
        }
    }

    return str;
}

int main( int argc, char *argv[] )  {

    if( argc != 2 ) {
        printf("Wrong amount of arguments.\n");
        printf("Usage: ./caesar k\n");
        printf("%s",argv[0]);
        return 1;
    }
    
    int char_codes[strlen(argv[1])];
    
    fill_codes_array(char_codes, argv[1], strlen(argv[1]));
    printf("plaintext:");
    string text = get_string();
    
    printf("ciphertext:%s\n",encrypt_string(text,char_codes,strlen(argv[1])));
    return 0;
}