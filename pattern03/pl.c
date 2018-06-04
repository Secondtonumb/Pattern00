#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "file.h"
#include "evalution.h"

#define CLU_NUM 3

int main(int argc,char* argv[]){
  if(argc != 5){
    printf("Usage: ./pl learning_data.list init_weight.dat weight.dat [rho]");
    exit(1);
  }
  
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

  double *eval;
  double **w;
  char *w_file_name = argv[2];
  FILE *w_file = fopen(w_file_name,"r");

  int i, j;
  int p = 0;
  
  double rho = atof(argv[4]);

  eval = malloc(CLU_NUM * sizeof(double));
  
  w = malloc(CLU_NUM * sizeof(double*));
  for(i = 0; i < CLU_NUM; i++){
    w[i] = malloc(W_DIM * sizeof(double));
  }

  for(i = 0; i < CLU_NUM * W_DIM; i++){
    fscanf(w_file,"%lf", &w[i / W_DIM][i % W_DIM]);
    }

  
  int flag[LEARNING_NUM];
  for(i = 0; i < LEARNING_NUM; i++){
    flag[i] = 1;
  }

  /* calculate until converge, while converge condition is all pattern have become stable */
  while(conv(flag, LEARNING_NUM)){
    
    if(p >= LEARNING_NUM) p = p % LEARNING_NUM;
    
    for(j = 0; j < CLU_NUM; j++){
      eval[j] = multi(p_arr[p].data, w[j], CLU_NUM);
      printf("Evaluation of Pattern %d by g(%d) : %f\n", p, j, eval[j]);
    }

    /* Corr is pattern's true Class */
    /* Err is Evaluated Class, if condition is met , err == -1 */
    int corr = p_arr[p].pclass;
    int err = judge_max(eval, CLU_NUM, corr);
    
    printf("Right Class = %d,Error Class = %d\n",corr,err);

    if(err != -1){
      flag[p] = 1;
      for(j = 0; j < W_DIM; j++){
	w[corr][j] += rho * p_arr[p].data[j];
	w[err][j] -= rho * p_arr[p].data[j];
      }
    }

    /* Weight Condition is met, change flag to let result converge */
    else{
      flag[p] = 0;
    }
    
    printf("========\n");

    for(i = 0; i < CLU_NUM; i++){
      for(j = 0; j < W_DIM; j++){
	printf("%f ",w[i][j]);
      }
      printf("\n");
    }
    
    /* printf("==> Converge Condition Array  <==") */
    /* for(i = 0; i < LEARNING_NUM; i++){ */
    /*   printf("%d ",flag[i]); */
    /* } */
    p++;
  }

  char *new_w_file_name = argv[3];

  /* Output New Generated Weight */
  FILE *output = fopen(new_w_file_name, "w");
  for(i = 0; i < CLU_NUM; i++){
      for(j = 0; j < W_DIM; j++){
        fprintf(output,"%f ",w[i][j]);
      }
      fprintf(output,"\n");
  }

  /* Free Memory */
  for(i = 0; i < LEARNING_NUM; i++){
    data_free(&p_arr[i]);
  }
  for(i = 0; i < CLU_NUM; i++){
    free(w[i]);
  }
  free(w);
}

