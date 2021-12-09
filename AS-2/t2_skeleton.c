#include <stdio.h> 
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;


void selectionSort(int arr[], int size) 
{ 
  int i, j, temp, toSwap;
  for (i=0; i<size-1; i++){
    toSwap = i;
    for (j=i+1; j<size; j++){
      number_comparisons++;
      if (arr[toSwap] > arr[j]){
        toSwap = j;
      }
    }
    number_swaps++;
    temp = arr[i];
    arr[i] = arr[toSwap];
    arr[toSwap] = temp; 
  }
  //TODO
} 

void insertionSort(int arr[], int size) 
{ 
  int i, j, temp;
  for (i=0; i<size-1; i++){
    number_comparisons++;
    for (j=i+1; j>0; j--){  
      // number_comparisons++;
      if (arr[j-1] > arr[j]){
        number_comparisons++;
        number_swaps++;
        temp = arr[j];
        arr[j] = arr[j-1];
        arr[j-1] = temp;
      }
      else break;
    }
  }
  //TODO
}

void sort(int arr[], int smallerIndex, int biggerIndex){
  if (smallerIndex < biggerIndex){
    int pivot = arr[smallerIndex]; // first element as pivot
    int partitionIndex = smallerIndex+1;
    int i, temp;
    for (i=smallerIndex+1; i<=biggerIndex; i++){
      number_comparisons++;
      if (arr[i] < pivot){
        number_swaps++;
        temp = arr[i];
        arr[i] = arr[partitionIndex];
        arr[partitionIndex] = temp;
        partitionIndex++;
      }
    }
    partitionIndex--;
    temp = arr[smallerIndex];
    arr[smallerIndex] = arr[partitionIndex];
    arr[partitionIndex] = temp;
    number_swaps++;
    sort(arr, smallerIndex, partitionIndex-1);
    sort(arr, partitionIndex+1, biggerIndex);
  }
}

void quickSort(int arr[], int size) 
{ 
  sort(arr, 0, size-1);
 //TODO
}



