//
// Created by oleg on 22.03.17.
//

#include <iostream>
#include "ArrayList.h"

// -------------------------------private--------------------------

void ArrayList::increase_array_length(){
    max_length *= MULTIPLICATION_FACTOR;
    this->arr = (int*)realloc(arr, (max_length*sizeof(int)));
}

// -------------------------------public---------------------------

void ArrayList::add(int data){
    if(size == max_length){
        increase_array_length();
    }
    this->arr[size] = data;
    size++;
}

void ArrayList::show(){
    for( int i = 0; i < size; i++){
        std::cout << this->arr[i]<<std::endl;
    }
}

int ArrayList::get(int index){
    return this->arr[index];
}

int ArrayList::getSize(){
    return this->size;
}

void ArrayList::set(int index, int data){
    this->arr[index] = data;
}

void ArrayList::remove(int index){
    for(int i = index; i < size, i < 20; i++){
        this->arr[i] = this->arr[i+1];
    }
    size--;
}

void ArrayList::trim(){
    this->arr = (int*)realloc(arr, (size*sizeof(int)));
};

