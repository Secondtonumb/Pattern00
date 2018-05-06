#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int value;
  int index;
}Node;

int minimum(int *arr,int len){
  int i,min = arr[0];
  int min_element_number;
  for(i = 1; i < len; i++){
    if(min > arr[i]){
      min = arr[i];
      min_element_number = i;
    }
  }
  return min_element_number;
}

int comp_array(const void *a, const void *b){
  return(*(struct node *)a).value > (*(struct node *)b).value ? 1 : -1;
}
