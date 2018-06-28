#include <stdio.h>
#include <stdlib.h>

/* Struct for Function [qsort] */
typedef struct node{
  double value;
  int index;
}Node;

/* Function for [qsort], adapted for struct node */
/* Ascending Order */
int comp_array(const void *a, const void *b){
  return(*(struct node *)a).value > (*(struct node *)b).value ? 1 : -1;
}

int comp_stump(const void *a, const void *b){
  return(*(Stump *)a).mini_gini > (*(Stump *)b).mini_gini ? 1 : -1;
}
/* Get the element, which comes most frequently in a int array  */
/* However,Reject when several values comes at the same frequency,
which means [-1] when be returned. */
int maxfreq_ele(int *arr, int len,int *type_dic, int type_len){
  int i;
  int m;
  int cnt[type_len];
  for(m = 0; m < type_len; m++) cnt[m] = 0;
  
  for(i = 0; i < len; i++){
    for(m = 0; m < type_len; m++){
      if(arr[i] == type_dic[m]) cnt[m]++;
    }
  }
  
  int max; max = cnt[0];
  int max_index; max_index = 0;
  for(m = 1; m < type_len; m++){
    if(max < cnt[m]){
      max = cnt[m];
      max_index = m;
    } 
  }
  
  int reject_flag = 0;
  for(m = 0; m < type_len; m++){
    if(max == cnt[m]) reject_flag++;
  }
  if(reject_flag == 1)
  return type_dic[max_index];
  else return -1;
}

/* return the smallest value's index in double array */
int min_ele_index(double *arr,int len){
  int i;

  double min = arr[0];
  int min_element_number = 0;
  for(i = 1; i < len; i++){
    if(min > arr[i]){
      min = arr[i];
      min_element_number = i;
    }
  }
  return min_element_number;
}


