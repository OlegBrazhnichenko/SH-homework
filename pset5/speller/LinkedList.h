//
// Created by oleg on 22.03.17.
//

#ifndef SPELLER_LINKEDLIST_H
#define SPELLER_LINKEDLIST_H


#include <iostream>
#include "Node.h"

class LinkedList{
private:
    Node* root;
    int* size;

    // return pointer to the node by index
    Node* get_node_by_index(int index);

    // return pointer to the last node
    Node* get_last_node();
public:
    // memory allocate for the root node
    LinkedList();

    // freeing memory
    ~LinkedList();

    // adding new node to the end of listed list and initialize it with data
    void add(int data);

    // setting new data to the particular node
    void set(int index, int data);

    // getting value of particular node
    int get(int index);

    // remove node by its index
    void remove(int index);

    // show all elements of listed list
    void show();
};


#endif //SPELLER_LINKEDLIST_H
