#include <stdio.h>
#include <stdlib.h>

#include "data1.h"
#include "file.h"

/* Define CLUSTER's type and numbers first*/
/* A more reasonable mathod is to get these variable from learning datas */
/* I'm still cling to solve this problem;) */
#define CLU_NUM 3

double multi(double a[], double b[], int n){
  double sum = 0;
  int i;
  for(i = 0; i < n; i ++ ){
    sum += a[i] * b[i]; 
  }
  return sum;
}

int judge_max(double a[], int n, int max_index){
  int i;
  double max = a[max_index];
  int temp_max_index = max_index;
  for(i = 0; i < n; i++){
    if(a[i] > max) max = a[i]; 
    temp_max_index = i;
  }
  
  if(a[max_index] == max)
    return -1;
  else
    return temp_max_index;
}

int only_max(double a[], int n, int max_index){
  int i;
  double max = a[max_index];
  int diff_index = -1;

  for(i = 0; i < n; i ++){
    if(a[i] == max){
      if(i == max_index);
      else diff_index = i;
    }
  }
  return diff_index;
}

double max_ele(double a[], int n){
  int i;
  double max = a[0];
  for(i = 1; i < n; i ++){
    if(a[i] > max){
      max = a[i];
    }
  }
  return max;  
}

int sub(double a[], double b[], double k, int n){
  int i;
  for(i = 0; i < n; i++){
    a[i] = a[i] - b[i];
  }
  return 0;
}

int print_w(double **a, int x, int y){
  int i, j;
  printf("========\n");
  for(i = 0; i < x; i++){
    for(j = 0; j < y; j++){
      printf("%.0f ",a[i][j]);
    }
    printf("\n");
  }
  return 0;
}

int main(int argc,char* argv[]){

  int m;

  char *learning_listfile = argv[1];
  FILE *files = fopen(learning_listfile, "r"); 
  
  int LEARNING_NUM ; 
  LEARNING_NUM = learning_ptn_num(files);
  
  char fileName[256];
  
  Pattern p_arr[LEARNING_NUM];
    
  /* Get Learning Datas from Learning Pattern Files */
  /*  Save data in struct character_data p_arr[LEARNING_NUM] */

  for(m = 0; m < LEARNING_NUM; m++){
    fscanf(files, "%s", fileName);
    
    printf("==> %s <==\n",fileName);
    
    FILE *data_file = fopen(fileName, "r");

    get_feature(&p_arr[m],data_file);
    
    data_malloc(&p_arr[m]);
    
    input(&p_arr[m],data_file);

     data_print(&p_arr[m]);

    p_arr[m].pclass = get_pattern_type(fileName);
    
    printf("%d\n",p_arr[m].pclass);
    
    // data_free(&p_arr[m]);

    fclose(data_file);
  }
  
  fclose(files);

  int W_DIM;
  W_DIM = p_arr[0].dim;
  printf("weight_vector's_dimention: %d\n", W_DIM);

  double *eval;
  /* double **w; */
  /* /\* char w_file = argv[2]; *\/ */
  /* /\* FILE * wei = fopen(w_file,"r"); *\/ */
  
  
  eval = malloc(CLU_NUM * sizeof(double));

  int i, j, p;
  /* w = malloc(CLU_NUM * sizeof(double*)); */
  /* for(i = 0; i < W_DIM; i++){ */
  /*   w[i] = malloc(W_DIM * sizeof(double)); */
  /* } */
  
  /* for(i = 0; i < CLU_NUM; i++){ */
  /*   eval[i] = 0; */
  /*   for(j = 0; j < W_DIM; j++){ */
  /*     w[i][j] = i * 1 + j; */
  /*   } */
  /* } */
  
  double rho = 1.0;
  double w[3][3] = {6, 2, 1, 2, 1, 5, 1, 6 ,1};
  
  for(i = 0; i < CLU_NUM; i++){
    printf("eval[i] = %.0f\n",eval[i]);
    for(j = 0; j < W_DIM; j++){
      printf("%.0f ",w[i][j]);
    }
    printf("\n");
  }

  
  for(p = 0; p < 6; p++){
    
    for(j = 0; j < CLU_NUM; j++){
      eval[j] = multi(p_arr[p].data, w[j], CLU_NUM);
      printf("eval of pattern %d : %f\n", p, eval[j]);
    }
  
    int corr = p_arr[p].pclass;
    int err = judge_max(eval, CLU_NUM, corr);
    
    printf("right class = %d,error index = %d\n",corr,err);
    if(err != -1){
      for(j = 0; j < W_DIM; j++){
	w[corr][j] += rho * p_arr[p].data[j];
	w[err][j] -= rho * p_arr[p].data[j];
      }
    }
    
    printf("========\n");
    for(i = 0; i < CLU_NUM; i++){
      for(j = 0; j < W_DIM; j++){
	printf("%.0f ",w[i][j]);
      }
      printf("\n");
    }
  }

}



