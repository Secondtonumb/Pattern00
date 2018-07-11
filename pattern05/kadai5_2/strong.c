#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Dim 2
#define Clu 2


#include "evalution.h"
#include "data.h"
#include "file.h"

#include "sort.h"

int reverse(int a){
  if(a == 2)return 1;
  else if(a == 1)return 2;
  else return 0;
}

int judge(int a){
  if(a == 2) return -1;
  else if(a == 1) return 1;
  else return 0;
}
int revert(int a){
  if(a == -1) return 2;
  else if(a == 1) return 1;
  else return 0;
}

double H(Pattern p, Stump *s, int trees, double *alpha){
  double res = 0;
  int i;
  for(i = 0; i < trees; i++){
    if(p.data[s[i].feat_index] < s[i].threshold){
      res += alpha[i] * judge(s[i].class);
    }
    else{
      res += alpha[i] * judge(reverse(s[i].class));
    }
  }
  return res;
}

int sign(double x){
  if(x > 0) return 1;
  else if(x < 0) return -1;
  else return 0;
}

int main(int argc, char *argv[]){
  if(argc != 3){
    printf("Usage: ./rec rec.dat forest.dat \n");
    exit(1);
  }
  int i, j, k; //i -> Layer, j -> Cluster, k -> Ptn Dimension
  
  int m; // m -> Ptn number;
  int n;

  char *learning_listfile = argv[1];
  char *forest_name = argv[2];
  int judge_dim;
  
  FILE *ptn_files = fopen(learning_listfile, "r");
  FILE *forest_file = fopen(forest_name, "r");
  
  int LEARNING_NUM;  
  LEARNING_NUM = learning_ptn_num(ptn_files);
  int FOREST_NUM;
  FOREST_NUM = learning_ptn_num(forest_file);

  Pattern p_arr[LEARNING_NUM];

  double step_len;
  int s;

  Stump forest[Dim];
  
  for(m = 0; m < LEARNING_NUM; m++){
    p_arr[m].dim = Dim;

    fscanf(ptn_files, "%d", &p_arr[m].pclass);

    data_malloc(&p_arr[m]);
    
    for(i = 1; i < Dim + 1; i++){
      fscanf(ptn_files, "%lf", &p_arr[m].data[i - 1]);
    }    
    //data_print(&p_arr[m]);
  }

  fclose(ptn_files);

  double h_w[FOREST_NUM];
  
  for(n = 0; n < FOREST_NUM; n++){
    fscanf(forest_file, "%d %d %lf %lf %lf",
	   &forest[n].feat_index,
	   &forest[n].class,
	   &forest[n].threshold,
	   &forest[n].mini_gini,
	   &h_w[n]);
  }

  for(n = 0; n < FOREST_NUM; n++){
    printf("%d %d %lf %lf %lf\n",
           forest[n].feat_index,
           forest[n].class,
           forest[n].threshold,
           forest[n].mini_gini,
           h_w[n]);
  }
  fclose(forest_file);  

  for(m = 0; m < LEARNING_NUM; m++){
    int temp;
    temp = revert(sign(H(p_arr[m], forest, FOREST_NUM, h_w)));
    p_arr[m].pclass = temp;
  }
  for(m = 0; m < LEARNING_NUM; m++){
    data_print(&p_arr[m]);
    printf("recon result %d\n", p_arr[m].pclass);
  }
}
