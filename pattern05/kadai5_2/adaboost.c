#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Dim 2
#define Clu 2

#include "evalution.h"
#include "data.h"
#include "file.h"

#include "sort.h"

void normalization(double *arr, int len){
  int i;
  double sum = 0;
  for(i = 0; i < len; i ++){
    sum += arr[i];
  }
  for(i = 0; i < len; i ++){
    arr[i] = arr[i] / sum;
  }
}

int main(int argc, char *argv[]){
  if(argc != 4){
    printf("Usage: resamp.dat forest.dat new_forest.dat\n");
    exit(1);
  }
  int i, j, k; //i -> Layer, j -> Cluster, k -> Ptn Dimension
  int m; // m -> Ptn number;
  int n;

  char *resample_listfile = argv[1];
  char *forest_name = argv[2];
  char *new_forest_name = argv[3];
 
  FILE *resamp_files = fopen(resample_listfile, "r");
  FILE *forest_file = fopen(forest_name, "r");
  FILE *new_forest_file = fopen(new_forest_name, "w");
  
  int LEARNING_NUM;  
  LEARNING_NUM = learning_ptn_num(resamp_files);
  printf("LEARNING_NUM %d \n", LEARNING_NUM);
  
  int FOREST_NUM;//maybe FOREST = Dim??
  FOREST_NUM = learning_ptn_num(forest_file);
  printf("FOREST_NUM %d \n", FOREST_NUM);
  
  Pattern p_arr[LEARNING_NUM];

  Node array[LEARNING_NUM];//Struct for sorting

  Stump forest[FOREST_NUM];
  
  int s;
  
  for(m = 0; m < LEARNING_NUM; m++){
    p_arr[m].dim = Dim;

    fscanf(resamp_files, "%d", &p_arr[m].pclass);

    data_malloc(&p_arr[m]);
    
    for(i = 1; i < Dim + 1; i++){
      fscanf(resamp_files, "%lf", &p_arr[m].data[i - 1]);
    }

    //data_print(&p_arr[m]);
  }

  fclose(resamp_files);

  /* 将决策树有效数据存入结构体中 */
  for(n = 0; n < FOREST_NUM; n++){
    fscanf(forest_file, "%d %d %lf %lf",
  	   &forest[n].feat_index,
  	   &forest[n].class,
  	   &forest[n].threshold,
  	   &forest[n].mini_gini);
  }

  /* for(n = 0; n < FOREST_NUM; n++){ */
  /*   printf("%d %d %lf %lf\n", */
  /*          forest[n].feat_index, */
  /*          forest[n].class, */
  /*          forest[n].threshold, */
  /*          forest[n].mini_gini); */
  /* } */
  
  fclose(forest_file);

  // value 是某次元的 向量的值
  // index 是此pattern的类

  double weight[LEARNING_NUM];
  double h_w[FOREST_NUM];
  // 初始化
  for(m = 0; m < LEARNING_NUM; m++){
    weight[m] = 1.0 / (LEARNING_NUM * 1.0);
    // printf("%f \n ", weight[m]);
  }

  for(n = 0; n < FOREST_NUM; n++){
    int error = 0;
    double eps = 0;
    h_w[n] = 1;

    for(m = 0; m < LEARNING_NUM; m++){
      array[m].value = p_arr[m].data[n];
      array[m].index = p_arr[m].pclass;
    }

    qsort(array, LEARNING_NUM, sizeof(Node), comp_array);
    
    for(m = 0; m < LEARNING_NUM; m++){
      printf("feature : %f Pattern kind : %d\n",
      	     array[m].value, array[m].index);

      if(array[m].value < forest[n].threshold){
	if(array[m].index != forest[n].class){
	  error ++;
	  eps += weight[m];
	}
      }
      
      else if(array[m].value >= forest[n].threshold){
	if(array[m].index == forest[n].class){
	  error ++;
	  eps += weight[m];
	}
      }
      printf("error %d eps %f\n", error, eps);
    }
    
    h_w[n] = 0.5 * log((1.0 - eps) / eps);

    //error 识别错误的个数 eps 错误率 h_w 识别器权重
    printf("\n===> Tree %d 's Final Result <===\n", n);
    printf("===> Error %d \t eps %f \t h_w %f\n", error, eps, h_w[n]);
    
    for(m = 0; m < LEARNING_NUM; m++){
      /* Weight Correction */
      /* For valuies under threshold, 
	 if class is right, Correct weight to make it smaller  
	 if class is wrong , Correct weight to make it bigger*/
      if(array[m].value < forest[n].threshold){
        if(array[m].index != forest[n].class){
          weight[m] = weight[m] * exp( - h_w[n] * (-1.0));
        }
	else{
	  weight[m] = weight[m] * exp( -h_w[n] * (1.0));
	}
      }

      else if(array[m].value >= forest[n].threshold){
        if(array[m].index == forest[n].class){
	  weight[m] = weight[m] * exp( - h_w[n] * (-1.0));
        }
	else{
          weight[m] = weight[m] * exp( -h_w[n] * (1.0));
        }
      }
      /* printf("new_weight %f\n", weight[m]); */
    }

    normalization(weight, LEARNING_NUM);
    printf("\n ===> Normalized Weights <===\n");

    for(m = 0; m < LEARNING_NUM; m++){
      printf("new_weight %f\n", weight[m]);
    }
    
    printf("\n");

    fprintf(new_forest_file, "%d %d %f %f %f\n",
	    forest[n].feat_index,
	    forest[n].class,
	    forest[n].threshold,
	    forest[n].mini_gini,
	    h_w[n]);
  }

  fclose(new_forest_file);
}

