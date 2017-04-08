//
// Created by oleg on 22.03.17.
//

#ifndef SPELLER_NODE_H
#define SPELLER_NODE_H

#include <iostream>

class Node {
private:
    // address of next node
    Node* next;

    // data of current node
    int* data;
public:
    // memory allocation for new node. Setting NULL pointer to next node
    Node();

    // freeing memory
    ~Node();

    // get data of current node
    int get_data();

    // set data for current node
    void set_data(int input_data);

    // getting address of next node
    Node* get_next();

    // setting address for next node
    void set_next(Node* address);
};

#endif //SPELLER_NODE_H
