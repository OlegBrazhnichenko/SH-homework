//
// Created by oleg on 22.03.17.
//

/**
 *  TODO
 *
 *  destructor
 *  constructor
 *
 */

#ifndef SPELLER_ARRAYLIST_H
#define SPELLER_ARRAYLIST_H

const int INITIONAL_ARRAY_SIZE = 10;
const int MULTIPLICATION_FACTOR = 2;

class ArrayList {
private:
    // initialize array with amount of ints defined in INITIONAL_ARRAY_SIZE const
    int* arr = (int *) malloc(INITIONAL_ARRAY_SIZE * sizeof(int)) ;

    // amount of added to array list elements
    int size = 0;

    // amount of current maximum length of array list
    int max_length = INITIONAL_ARRAY_SIZE;

    // increases size of array each time when its going to overflow
    void increase_array_length();

public:
    // add element to the end of array list
    void add(int data);

    // get the value of element from array list by its index
    int get(int index);

    int getSize();

    // update value of element from array list by its index
    void set(int index, int data);

    // remove element from array list by index
    void remove(int index);

    // release all unused memory from array list
    void trim();

    // display all elements of array list via std::cout
    void show();
};

#endif //SPELLER_ARRAYLIST_H
