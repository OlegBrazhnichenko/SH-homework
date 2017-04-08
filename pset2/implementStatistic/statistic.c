#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void show(int *stat){
    int the_highest = 0;
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            if(stat[j] > stat[the_highest]){
                the_highest = j;
            }
        }
        if(stat[the_highest] == 0){
            exit(0);
        }
        printf("%c - %i\n",(char)the_highest+65,stat[the_highest]);
        stat[the_highest] = 0;
        the_highest = 0;
    }
}

void make_statistic(string str){
    int letters[30] = {0};
    for(int i = 0; i < strlen(str); i++){
        letters[((int)toupper(str[i]))-65]++;    
    }
    show(letters);
}

int main(void){
    string str;
    do{
        printf("please, enter your string: ");
        str = get_string();
    }while(str[0] == '\0');
    make_statistic(str);
    
    return 0;
}