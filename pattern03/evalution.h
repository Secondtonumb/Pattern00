#include <stdio.h>
#include <stdlib.h>

/* Vector dot product */
double multi(double a[], double b[], int n){
  double sum = 0;
  int i;
  for(i = 0; i < n; i ++ ){
    sum += a[i] * b[i];
  }
  return sum;
}

/* Judging Whether max_index is the real [max index] of array a */
/* If Ture, return -1 */
/* If False, return the first maximum element index */
int judge_max(double a[], int n, int max_index){
  int i;
  double max = a[max_index];
  int temp_max_index = max_index;

  for(i = 0; i < n; i++){
    if(a[i] > max){
      max = a[i];
      temp_max_index = i;
    }
  }

  if(a[max_index] == max)
    return -1;
  else
    return temp_max_index;
}

/* Convergence */
/* If array a has [1], return 1
   else, return 0 */
int conv(int a[], int n){
  int i;
  int flag = 0;
  for(i = 0; i < n; i++){
    if(a[i] == 1){
      flag = 1;
        break;
    }
  }
    return flag;
}
