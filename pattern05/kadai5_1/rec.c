#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Dim 3
#define Clu 2


#include "evalution.h"
#include "data.h"
#include "file.h"

#include "sort.h"

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
  
  Pattern p_arr[LEARNING_NUM];

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

  for(n = 0; n < Dim; n++){
    fscanf(forest_file, "%d %d %lf %lf",
	   &forest[n].feat_index,
	   &forest[n].class,
	   &forest[n].threshold,
	   &forest[n].mini_gini);
  }

  fclose(forest_file);

  for(n = 0; n < Dim; n ++){
    printf("%d %f\n",
           forest[n].feat_index,
           forest[n].threshold);
  }

  qsort(forest, Dim, sizeof(Stump), comp_stump);

  printf("Sorted Forest \n");

  for(n = 0; n < Dim; n ++){
    printf("%d %d  %f %f \n",
           forest[n].feat_index,
	   forest[n].class,
           forest[n].threshold,
           forest[n].mini_gini);
  }

  judge_dim = forest[0].feat_index;

  printf("\n Judge Dimention [%d]\n", judge_dim);
  for(m = 0; m < LEARNING_NUM; m++){
    if(p_arr[m].data[judge_dim] <= forest[0].threshold)
      printf("p_arr[%d] --> Cluster %d\n", m,  forest[0].class);
    else
      printf("p_arr[%d] --> Cluster %d\n", m, reverse(forest[0].class));
  }

}
