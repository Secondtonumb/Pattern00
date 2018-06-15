#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Layer 2
#define Dim 2
#define Clu 2

#include "evalution.h"
#include "data.h"
#include "file.h"

typedef struct{
  double *w; /*input weights(w0, w1, w2, w3)*/
  double e;
  double g;
  double h;
} Neural;


#define Arr_Len(array,len){len = (sizeof(array) / sizeof(array[0]));}


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

int main(int argc, char *argv[]){
  if(argc != 4){
    printf("Usage: ./nw ptn.list bias.dat weight.list");
    exit(1);
  }
  
  double rho;
  rho = 0.1;
  
  int i, j, k;

  int m;

  char *learning_listfile = argv[1];
  char *bias_name = argv[2];
  char *weight_listfile = argv[3];
  
  FILE *ptn_files = fopen(learning_listfile, "r");
  FILE *bias_file = fopen(bias_name, "r");
  FILE *weight_files = fopen(weight_listfile, "r");
   
  int LEARNING_NUM;
  LEARNING_NUM = learning_ptn_num(ptn_files);

  char ptn_name[256];
  Pattern p_arr[LEARNING_NUM];
  
  for(m = 0; m < LEARNING_NUM; m++){
    fscanf(ptn_files, "%s", ptn_name);

    printf("==> %s <==\n",ptn_name);

    FILE *data_file = fopen(ptn_name, "r");
    
    get_feature(&p_arr[m],data_file);

    data_malloc(&p_arr[m]);

    input_pattern(&p_arr[m],data_file);

    data_print(&p_arr[m]);

    p_arr[m].pclass = get_pattern_type(ptn_name);

    printf("%d\n",p_arr[m].pclass);

    // data_free(&p_arr[m]);

    fclose(data_file);
  }

  fclose(ptn_files);
  
  Neural n_net[Layer][Clu];

  char w_name[256];

  int weight_num;
  weight_num = learning_ptn_num(weight_files);

  if(weight_num != Layer){
    printf("weight file ERROR\n");
    exit(1);
  }

  fscanf(weight_files, "%s", w_name);
  printf("==> %s <==\n",w_name);
  
  FILE *w_data_file = fopen(w_name, "r");

  for(j = 0; j < Clu; j++){
    N_first_layer_malloc(&n_net[0][j]);
  }

  for(j = 0; j < Clu; j++){
    for(k = 0; k < Dim ; k++){
      fscanf(w_data_file, "%lf", &n_net[0][j].w[k]);
    }
  }
  
  for(i = 1; i < Layer; i++){
    fscanf(weight_files, "%s", w_name);
    printf("==> %s <==\n",w_name);

    FILE *w_data_file = fopen(w_name, "r");
    for(j = 0; j < Clu; j++){
      N_malloc(&n_net[i][j]);
    }
    for(j = 0; j < Clu; j++){
      for(k = 0; k < Clu ; k++){
        fscanf(w_data_file, "%lf", &n_net[i][j].w[k]);
      }
    }
  }  
  
  for(i = 0; i < Layer; i++){
    printf(" Layer %d\n", i);
    for(j = 0; j < Clu; j++){
      N_print_weight(&n_net[i][j]);
    }
    printf("\n");
  }
  
  /* Bias file Input */
  int length;
  double *b;

  fscanf(bias_file, "%d", &length);
  b = malloc(sizeof(double) * length);

  for(m = 1; m < length + 1; m ++){
    fscanf(bias_file,"%lf", &b[m - 1]);
  }

  double *L_input; //Layer input ,前一层h的集合

  L_input = malloc(sizeof(double) * Clu);
  
  double *init_p= p_arr[0].data; 
  
  double *label;

  label = malloc(sizeof(double) * Clu);

  for(j = 0; j < Clu; j++){
    label[j] = 0;
  }
  label[p_arr[0].pclass] = 1;

  int n;
  for(n = 0; n < 10000; n++){
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
    printf(" Layer %d 's weight\n", i);
    for(j = 0; j < Clu; j++){
      N_print_weight(&n_net[i][j]);
    }
    printf("\n");
  }
  }

  for(i = 0; i < Layer; i++){
    for(j = 0; j < Clu; j++){
      N_free(&n_net[i][j]);
    }
  }
}
