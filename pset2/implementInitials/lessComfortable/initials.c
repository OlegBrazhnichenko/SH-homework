#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string get_name(){
    string name;
    do {
        name = get_string();    
    }while(name == NULL);
    
    return name;
}

void make_initials(string name){
    char initial[2];
    for(int i = 0; i < strlen(name); i++){
        if(isalpha(name[i])){
            if( i > 0){
                if(!isalpha(name[i-1])){
                    initial[0] = toupper(name[i]);
                    printf("%s", initial);
                }
            }else{
                initial[0] = toupper(name[0]);
                printf("%s", initial);
            }
        }
    }
    printf("\n");
    
    
}

int main(void){
    
    make_initials(get_name());
    
    return 0;
}
