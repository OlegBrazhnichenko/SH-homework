#include <ctype.h>
#include <stdio.h>

#include <iostream>
#include "Dictionary.h"
#include "Trecker.h"

int main() {

    Trecker trecker;

    Dictionary dictionary;

    getrusage(RUSAGE_SELF, &(trecker.before));
    dictionary.load();
    getrusage(RUSAGE_SELF, &(trecker.after));

    double time_load = trecker.calculate(&(trecker.before),&(trecker.after));

    FILE* text = fopen("texts/austinpowers.txt","r");

    getrusage(RUSAGE_SELF, &(trecker.before));
    cout<<"Words misspelled: "<<dictionary.check(text)<<endl;
    getrusage(RUSAGE_SELF, &(trecker.after));

    double time_check = trecker.calculate(&(trecker.before),&(trecker.after));

    printf("TIME IN load:     %.2f\n", time_load);
    printf("TIME IN check:    %.2f\n", time_check);

    return 0;
}