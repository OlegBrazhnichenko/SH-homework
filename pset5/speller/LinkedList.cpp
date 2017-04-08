//
// Created by oleg on 22.03.17.
//

#include "LinkedList.h"

// --------------------------------private----------------------------

Node* LinkedList::get_node_by_index(int index){
    Node* node = root;
    for (int i = 0; i < index; i++){
        node = node->get_next();
    }

    return node;
}

Node* LinkedList::get_last_node(){

    return get_node_by_index(*size);
}

//---------------------------------public-----------------------------

LinkedList::LinkedList(){
    this->root = new Node;
    this->size = new int(0);
}

LinkedList::~LinkedList(){
    delete(this->root); // rewrite
    delete(this->size);
}

void LinkedList::add(int data){
    Node* node = get_last_node();
    node->set_next(new Node);
    node->get_next()->set_data(data);
    (*size)++;
}

void LinkedList::set(int index, int data){
    Node* node = get_node_by_index(index);
    node->set_data(data);
}

int LinkedList::get(int index){
    Node* node = get_node_by_index(index);

    return node->get_data();
}

void LinkedList::remove(int index){
    index += 1;                                   // rewrite
    // withdraw node from nodes chain
    // get address of previous node
    Node* prev_node = get_node_by_index(index-1);

    // get address of withdraws node
    Node* node = get_node_by_index(index);

    // connect previous and next nodes
    prev_node->set_next(node->get_next());
    delete(node);
    *size -= 1;
}

void LinkedList::show(){
    Node* node = root;
    for (int i = 0; i < *size; i++){
        node = node->get_next();
        std::cout<<node->get_data()<<std::endl;
    }
}