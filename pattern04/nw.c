#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#include "evalution.h"

#define Layer 2
#define Dim 2
#define Clu 2

#define Arr_Len(array,len){len = (sizeof(array) / sizeof(array[0]));}

typedef struct{
  double *w; /*input weights(w0, w1, w2, w3)*/
  //double *e;
  double e;
  double g;
  double h; 
} Neural;


void N_first_layer_malloc(Neural *N){
  N->w = malloc(Dim * sizeof(double));
  //  N->e = malloc(Dim * sizeof(double));
}

void N_malloc(Neural *N){
  N->w = malloc(Clu * sizeof(double));
  //N->e = malloc(Clu * sizeof(double));
}

/* void N_init_weight(Neural *N){ */
/*   int k; */
/*   int upper = 10, lower = -10; */
/*   for(k = 0; k < Clu; k++){ */
/*     N->w[k] = (rand() % (upper-lower + 1)) + lower; */
/*     N->e[k] = 1; */
/*   } */
/* } */

void N_print_weight(Neural *N){
  int k;
  for(k = 0; k < Clu; k++){
    printf("weight [%d]th :%f ",k,N->w[k]);
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

int main(){  
  double rho;
  rho = 0.1;
  
  Neural n_net[Layer][Clu];
  int i, j, k;

  for(j = 0; j < Clu; j++){
    N_first_layer_malloc(&n_net[0][j]);
  }
  
  for(i = 1; i < Layer; i++){
    for(j = 0; j < Clu; j++){
      N_malloc(&n_net[i][j]);
    }
  }

  /* for(i = 0; i < Layer; i++){ */
  /*   for(j = 0; j < Clu; j++){ */
  /*     N_init_weight(&n_net[i][j]); */
  /*   } */
  /* } */

  n_net[0][0].w[0] = 0.15;
  n_net[0][0].w[1] = 0.20;
  n_net[0][1].w[0] = 0.25;
  n_net[0][1].w[1] = 0.30;
  n_net[1][0].w[0] = 0.40;
  n_net[1][0].w[1] = 0.45;
  n_net[1][1].w[0] = 0.50;
  n_net[1][1].w[1] = 0.55;
  
  /* for(i = 0; i < Layer; i++){ */
  /*   printf(" Layer %d\n", i); */
  /*   for(j = 0; j < Clu; j++){ */
  /*     N_print_weight(&n_net[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  /* for(i = 0; i < Layer -1 ; i++){ */
  /*   printf("Hidden Layer %d\n", i); */
  /*   for(j = 0; j < Clu; j++){ */
  /*     N_print_weight(&n_net[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */
  
  double b[Layer] = {0.35, 0.60};
  double *L_input; //Layer input ,前一层h的集合

  L_input = malloc(sizeof(double) * Clu);
  
  double init_p[] = {0.050, 0.100}; //初始向量，不包括扩张？
  
  double *output;//神经网络输出
  output = malloc(sizeof(double) * Clu);

  double label[Clu] = {0.01, 0.99};//教师信号
  int n;

  
  // forward
  for(j = 0; j < Clu; j++){
    n_net[0][j].g = multi(n_net[0][j].w, init_p, Clu) + b[0];
    n_net[0][j].h = S(n_net[0][j].g);
  }

  for(j = 0; j < Clu; j++){
    L_input[j] = n_net[0][j].h;
  }
  
  for(i = 1; i < Layer ; i++){
    for(j = 0; j < Clu; j++){
      // x should change into the putputs of pre neurals 
      // a h array
      n_net[i][j].g = multi(n_net[i][j].w, L_input, Clu) + b[i];
      n_net[i][j].h = S(n_net[i][j].g);
    }

    for(j = 0; j < Clu; j++){
      L_input[j] = n_net[i][j].h;
    }
  }
  printf("Result of [%d] turns\n", n);
  for(j = 0; j < Clu; j++){
    printf("%f ", L_input[j]);
  }
  printf("\n");
  
  printf("誤差逆搬运\n");
  
  //　出力層修正
  for(j = 0; j < Clu; j++){
    n_net[Layer - 1][j].e = op_layer_e(label[j], n_net[Layer - 1][j].h);
    printf("Layer[%d] Unit[%d]: epsilon, %f \n",Layer -1, j, n_net[Layer - 1][j].e);
  }    

  double e2bcorr[Clu], w2bcorr[Clu];
  // 隠れ層修正
  // 需要存在前后一层
  for(i = Layer - 2; i >= 0; i--){
    printf("Layer [%d]\n", i);

    for(j = 0; j < Clu; j++){
      e2bcorr[j] = n_net[i + 1][j].e;
    }
    
    for(j = 0; j < Clu; j++){
      for(k = 0; k < Clu; k++){
	w2bcorr[k] = n_net[i + 1][k].w[j];
      }
      n_net[i][j].e = hid_layer_e(e2bcorr, w2bcorr, n_net[i][j].h);
      printf("Layer[%d] Unit[%d]: epsilon, %f \n",i, j, n_net[i][j].e);
    }
  }

  // 改w
  // 改非首层
  for(i = Layer - 1; i > 0; i--){
    for(j = 0; j < Clu; j++){
      for(k = 0; k < Clu; k++){
        n_net[i][j].w[k] += - rho * n_net[i][j].e * n_net[i - 1][j].h;
	// printf("Layer[%d] Unit[%d] weight[%d] : %f \n",i, j ,k,  n_net[i][j].w[k]);
      }
    }
  }
  
  // 改第0层
  for(j = 0; j < Clu; j++){
    for(k = 0; k < Dim; k++){
      n_net[0][j].w[k] += - rho * n_net[0][j].e * init_p[k];
      printf("Layer[%d] Unit[%d] weight[%d] : %f, 系数项: %f %f %f\n",0, j ,k, n_net[i][j].w[k], rho, n_net[0][j].e, init_p[k]);
    }
  }

  for(i = 0; i < Layer; i++){
    printf(" Layer %d 's epsilon\n", i);
    for(j = 0; j < Clu; j++){
      N_print_weight(&n_net[i][j]);
    }
    printf("\n");
  }
    

  for(i = 0; i < Layer; i++){
    for(j = 0; j < Clu; j++){
      N_free(&n_net[i][j]);
    }
  }
}
