//
// Created by oleg on 22.03.17.
//

#include "Node.h"

// ----------------------------------public ----------------------------------

Node::Node() {
    this->next = NULL;
    this->data = new int(0);
}

Node::~Node(){
    delete( this->data );
}

int Node::get_data(){
    return *(this->data);
}

void  Node::set_data(int input_data){
    *(this->data) = input_data;
}

Node* Node::get_next(){
    return this->next;
}

void Node::set_next(Node* address){
    this->next = address;
}