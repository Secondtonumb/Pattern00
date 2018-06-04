#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "file.h"
#include "evalution.h"

#define CLU_NUM 3
#define W_DIM 3

int max_ele_index(double *arr,int len){
  int i;
  int count = 0;
  double max = arr[0];
  int max_element_number = 0;
  for(i = 1; i < len; i++){
    if(max < arr[i]){
      max = arr[i];
      max_element_number = i;
    }
  }
  for (i = 0; i < len; i++){
    if(arr[i] == max) count ++;
  }
  
  if(count > 1)
    return -1;
  else
    return max_element_number;
}


int main(int argc,char* argv[]){
  if(argc != 3){
    printf("Usage: ./pl_rec weight.dat unknown.dat");
    exit(1);
  }
  int i, j;

  double *eval;
  double **w;
  char *w_file_name = argv[1];
  FILE *w_file = fopen(w_file_name, "r");
  
  eval = malloc(CLU_NUM * sizeof(double));

  w = malloc(CLU_NUM * sizeof(double*));
  for(i = 0; i < CLU_NUM; i++){
    w[i] = malloc(W_DIM * sizeof(double));
  }

  for(i = 0; i < CLU_NUM * W_DIM; i++){
    fscanf(w_file,"%lf", &w[i / W_DIM][i % W_DIM]);
  }
  
  char *unknown_pattern_file_name = argv[2];
  FILE *unrec_file = fopen(unknown_pattern_file_name, "r");

  Pattern unrec_p;

  get_feature(&unrec_p,unrec_file);

  data_malloc(&unrec_p);

  input(&unrec_p,unrec_file);

  // data_print(&unrec_p);

  fclose(unrec_file);


  for(i = 0; i < CLU_NUM; i++){
    eval[i] = multi(unrec_p.data, w[i], CLU_NUM);
    printf("Value of g[%d]: %f\n", i, eval[i]);
  }

  int result;
  result = max_ele_index(eval, CLU_NUM);

  printf("recog result == %d\n", result);

  for(i = 0; i < CLU_NUM; i++){
    free(w[i]);
  }
  free(w);
  data_free(&unrec_p);
}
