#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Dim 3
#define Clu 2


#include "evalution.h"
#include "data.h"
#include "file.h"

typedef struct Stump_{
  int feat_index;
  double threshold;
  double mini_gini;
}Stump;

#include "sort.h"

double gini_inp(double lower, double upper, Node *arr, Pattern *ptn, int n, int class){
  int i;
  int count_all = 0;
  int count_right = 0;
  double g = 0;
  
  for(i = 0; i < n; i++){
    if(lower <= arr[i].value && arr[i].value <= upper){
      count_all ++;
      if(ptn[arr[i].index].pclass == class){
	count_right ++;
      }
    }    
  }
  if(count_all == 0)
    return 0;
  else{
    double p = (count_right * 1.0 ) / (count_all * 1.0);
    g = p * (1 - p);
    return g;
  }
}

void thre_init(double *arr, int n, double lower, double upper){
  int i;
  for(i = 0; i < n; i ++) arr[i] = 0;
  arr[0] = lower;
  arr[n - 1] = upper;
}
  
int main(int argc, char *argv[]){
  if(argc != 4){
    printf("Usage: ./cart ptns.dat forest.dat <steps>\n");
    exit(1);
  }
  int i, j, k; //i -> Layer, j -> Cluster, k -> Ptn Dimension
  
  int m; // m -> Ptn number;
  int n;

  char *learning_listfile = argv[1];
  char *forest_name = argv[2];
  double steps = atof(argv[3]);
  
  FILE *ptn_files = fopen(learning_listfile, "r");
  FILE *forest_file = fopen(forest_name, "w");
  
  int LEARNING_NUM;  
  LEARNING_NUM = learning_ptn_num(ptn_files);

  Pattern p_arr[LEARNING_NUM];

  Node array[LEARNING_NUM];

  double gini = 0;

  double thre[Clu + 1];
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

  for(n = 0; n < Dim; n ++){
    forest[n].feat_index = n;
    for(m = 0; m < LEARNING_NUM; m++){
      array[m].value = p_arr[m].data[n];
      array[m].index = m;
    }

    qsort(array, LEARNING_NUM, sizeof(Node), comp_array);
  
    /* for(m = 0; m < LEARNING_NUM; m++){ */
    /*   printf("[PATTERN NO.%d]  feature : %f Pattern kind : %d\n", */
    /* 	     array[m].index, array[m].value, p_arr[array[m].index].pclass); */
    /* } */
    
    step_len = (array[LEARNING_NUM - 1].value - array[0].value) / steps;

    thre_init(thre, Clu + 1, array[0].value, array[LEARNING_NUM - 1].value);

    forest[n].threshold = thre[0];
    forest[n].mini_gini = 1;
    
    for(s = 0; s < steps; s++){
      thre[1] = step_len * (s + 1) + thre[0];
      double last_gini = gini;
      gini = 0;
      
      for(i = 0; i < Clu; i++){
	double temp;
	temp = gini_inp(thre[i], thre[i + 1], array, p_arr, LEARNING_NUM, i + 1);
	gini += temp;
	//	printf("thre %f gini of class %d --> %f\n", thre[1], i + 1, temp);
      }
      if(gini < last_gini){
	forest[n].threshold = thre[1];
	forest[n].mini_gini = gini;
      }
    }
  }

  for(n = 0; n < Dim; n++){
    fprintf(forest_file, "%d %f %f\n",
	    forest[n].feat_index,
            forest[n].threshold,
	    forest[n].mini_gini);
  }
  fclose(forest_file);

  /* qsort(forest, Dim, sizeof(Stump), comp_stump); */

  /* printf("Sorted Forest \n"); */
  
  for(n = 0; n < Dim; n ++){
    printf("%d %f %f \n",
           forest[n].feat_index,
           forest[n].threshold,
           forest[n].mini_gini);
  }
}
