#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
  double *w; /*input weights(w0, w1, w2, w3)*/
  double e;
  double g;
  double h;
} Neural;

void N_first_layer_malloc(Neural *N){
  N->w = malloc(Dim * sizeof(double));
}

void N_malloc(Neural *N){
  N->w = malloc(Clu * sizeof(double));
}

void N_init_weight(Neural *N){
  int k;
  int  upper = 10, lower = -10;
  for(k = 0; k < Clu; k++){
    N->w[k] = (rand() % (upper-lower + 1)) + lower;
  }
}

void N_print_weight(Neural *N, int l){
  int k;
  if(l == 0){
    for(k = 0; k < Dim; k++){
      printf("weight [%d]th :%f ",k,N->w[k]);
    }
  }
  else{
    for(k = 0; k < Clu; k++){
      printf("weight [%d]th :%f ",k,N->w[k]);
    }
  }
  printf("\n");
}

void N_free(Neural *N){
  free(N->w);
  //free(N->e);
}

double S(double x){
  return 1 / (1 + exp(-x));
}

double op_layer_e(double teach, double op){
  double res;
  res = (op - teach) * op * (1 - op);
  return res;
}

double hid_layer_e(double *w_arr, double *e_arr, double ip){
  int i;
  double temp, res;
  temp = multi(w_arr, e_arr, Clu);
  res = temp * ip * (1 - ip);
  return res;
}

double err(double *a, double *b){
  double res = 0;
  int i;
  for(i = 0; i < Clu; i++){
    res += pow((a[i] - b[i]), 2);
  }
  return res;
}
