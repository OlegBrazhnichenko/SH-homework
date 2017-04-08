/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 
#include <stdio.h>

int get_the_highest_num(int values[],int n);
void fill_n(int*, int, int);
bool binary_search(int, int values[], int, int);

bool search(int value, int values[], int n)
{
    int left_limit = 0;
    int right_limit = n;
    return binary_search(value,values, left_limit, right_limit);
}

bool binary_search(int search_value, int values[], int left_limit, int right_limit){
    int middle = (left_limit + right_limit) / 2;
    if(search_value < values[middle]){
        right_limit = middle;
    }else if (search_value > values[middle]){
        left_limit = middle;
    }else if (search_value == values[middle] || search_value == values[right_limit]){
        return true;
    }
    if(middle == right_limit-1){
        return false;
    }
    
    return binary_search(search_value, values, left_limit, right_limit);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int the_highest_num = get_the_highest_num(values,n);
    
    int arr[the_highest_num];
    fill_n(arr, the_highest_num, 0);
    
    for(int i = 0; i < n; i++){
        arr[values[i]]++;
    }
    int elem_num = 0;
    for(int i = 0; i < the_highest_num; i++){
        for(int j = 0; j < arr[i]; j++){
            values[elem_num] = i;
            elem_num ++;
        }
    }
    
    return;
}

int get_the_highest_num(int values[],int n){
    int highest = 0;
    for(int i = 0; i < n; i++){
        if(highest < values[i]){
            highest = values[i];
        }
    }
    return highest + 1;
}
void fill_n(int* arr, int amount, int num){
    for(int i = 0; i < amount; i++){
        arr[i] = num;
    }
    
    return;
}
