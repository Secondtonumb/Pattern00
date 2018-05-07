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
  
  for(m = 0; m < type_len; m++){
    printf("pattern [%d] %d\n",type_dic[m],cnt[m]);
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
