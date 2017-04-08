//
// Created by oleg on 27.03.17.
//

#include <cstdio>
#include <iostream>
#include <map>
#include "Dictionary.h"
#define DICTIONARY "dictionaries/large"
#define LENGTH 45

void Dictionary::load(){
    this->dictionary = fopen(DICTIONARY,"r");
    if (this->dictionary == NULL){
        std::cout<<"Could not load: "<<this->dictionary<<std::endl;
    } else {
        this->formMap();
    }
}

void Dictionary::formMap(){
    int index = 0, words = 0;
    char word[LENGTH+1];
    FILE* fp = this->dictionary;

    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)) {
        if (isalpha(c) || (c == '\'' && index > 0)) {
            word[index] = c;
            index++;
            if (index > LENGTH) {
                while ((c = fgetc(fp)) != EOF && isalpha(c));
                index = 0;
            }
        }
        else if (isdigit(c)) {
            while ((c = fgetc(fp)) != EOF && isalnum(c));
            index = 0;
        }
        else if (index > 0) {
            word[index] = '\0';
            words++;
            this->dictionaryMap[word] = "correct";
            index = 0;
        }
    }
    this->dictionarySize = words;
}

int Dictionary::check(FILE* fp){
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH+1];
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)) {
        if (isalpha(c) || (c == '\'' && index > 0)) {
            word[index] = tolower(c);
            index++;
            if (index > LENGTH) {
                while ((c = fgetc(fp)) != EOF && isalpha(c));
                index = 0;
            }
        }
        else if (isdigit(c)) {
            while ((c = fgetc(fp)) != EOF && isalnum(c));
            index = 0;
        }
        else if (index > 0) {
            word[index] = '\0';
            words++;

            if (this->dictionaryMap[word] != "correct") {
                printf("%s\n", word);
                misspellings++;
            }
            index = 0;
        }
    }
    return misspellings;
}