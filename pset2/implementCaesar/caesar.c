#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char encrypt_char(char c, int secret_key){
    if(!isalpha(c + secret_key)){
        c = c + secret_key - 26;
    }else{
        c = c + secret_key;          
    }
    return c;
}

void encrypt_string(string str, int secret_key) {
    for (int i = 0; i < strlen(str); i++) {
        if(isalpha(str[i])){
            str[i] = encrypt_char(str[i],secret_key);
        }
    }
}

int main( int argc, char *argv[] )  {
    if( argc != 2 ) {
      printf("Wrong amount of arguments.\n");
      printf("Usage: ./caesar k\n");
      return 1;
    }
    printf("plaintext:");
    string text = get_string();
    encrypt_string(text,atoi(argv[1]) % 26);
    printf("ciphertext:%s\n",text);
    return 0;
}