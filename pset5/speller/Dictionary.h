//
// Created by oleg on 27.03.17.
//

#ifndef SPELLER_DICTIONARY_H
#define SPELLER_DICTIONARY_H

#include <stdbool.h>
#include <map>

#define LENGTH 45

using namespace std;

class Dictionary {
private:
    FILE* dictionary = NULL;
    map<string,string> dictionaryMap;
    int dictionarySize = 0;
public:

    void load();

    void formMap();

    int check(FILE*);
};


#endif //SPELLER_DICTIONARY_H
