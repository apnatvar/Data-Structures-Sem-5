#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "t1.h"


//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size)
{
    int i;
    for (i=0; i<size; i++){
        array[i] = i;
    }
    //TODO
    
}
//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size)
{
    int i;
    for (i=0; i<size; i++){
        array[i] = size-i-1;
    }
    //TODO
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size)
{
    //srand(time(0));
    int nonUniformNumber = rand() % size;
    int i;
    for(i=0; i<size; i++){
        array[i] = nonUniformNumber;
    }
    //TODO
    
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size)
{
    //srand(time(0));
    int i;
    for (i=0; i<size; i++){
        array[i] = rand() % size;
    }
    //TODO
    
}


//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
    //srand(time(0));
    int i, nonUniformNumber, j, flag;
    for (i=size-1; i>-1; i--){
        nonUniformNumber = rand() % size;
        flag = 1;
        for (j=size-1; j>i; j--){
            if (array[j] == nonUniformNumber){
                flag = 0;
                break;
            }
        }
        if (flag) array[i] = nonUniformNumber;
        else i++;
    }
    //TODO

}

void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}
