#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string get_name(void);


int make_initials(char initials[], string name){
    
    int length = 0;
    for(int i = 0; i < strlen(name); i++){
        if(isalpha(name[i])){
            if( i > 0){
                if(!isalpha(name[i-1])){
                    initials[length] = toupper(name[i]);
                    length++; 
                }
            }else{
                initials[length] = toupper(name[0]);
                length++;
            }
        }
    }
    
    return length;
}
void show_initials(char initials[],int length){
    for(int i = 0; i < length; i++){
        printf("%c", initials[i]);
    }
    printf("\n");
}
int main(void){
    char initials[10];
    show_initials(initials,make_initials(initials,get_name()));
    
    return 0;
}

string get_name(){
    string name;
    do {
        name = get_string();    
    }while(name == NULL);
    
    return name;
}
