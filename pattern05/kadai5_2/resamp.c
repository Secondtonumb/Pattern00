#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Dim 2
#define Clu 2


#include "evalution.h"
#include "data.h"
#include "file.h"


typedef struct samp_node_{
  double type;
  double w;
  double cum_w;
}Samp_Node;

typedef struct Stump_{
  int feat_index;
  double threshold;
  double mini_gini;
}Stump;

#include "sort.h"

int Samp_Types(Node *arr, int len){
  int i;
  int cnt = 1;
  for(i = 1; i < len; i++){
    if(arr[i].value != arr[i - 1].value) cnt ++;
  }
  return cnt;
}

double resamp(Samp_Node *s, int n, double rate){
  int i;
  if(rate <= s[0].cum_w) return s[0].type;
  else{
    for(i = 1; i < n; i++){
      if(s[i - 1].cum_w < rate && rate <= s[i].cum_w) break;
    }
    return s[i].type;
  }
  
}

int main(int argc, char *argv[]){
  
  int i, j, k; //i -> Layer, j -> Cluster, k -> Ptn Dimension
  int m; // m -> Ptn number;
  int n;

  char *learning_listfile = argv[1];
  int RESAMPS = atoi(argv[2]);

  
  FILE *ptn_files = fopen(learning_listfile, "r");
  
  int LEARNING_NUM;  
  LEARNING_NUM = learning_ptn_num(ptn_files);

  Pattern p_arr[LEARNING_NUM];
  
  Node array[LEARNING_NUM];//Struct for sorting

  double gini = 0;

  double thre[Clu + 1];  

  double *thre_alts;
  int alt_nums;
  
  int s;
  
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
    for(m = 0; m < LEARNING_NUM; m++){
      array[m].value = p_arr[m].data[n];
      array[m].index = m;
    }

    qsort(array, LEARNING_NUM, sizeof(Node), comp_array);

    for(m = 0; m < LEARNING_NUM; m++){
      printf("\n[PATTERN NO.%d]  feature : %f Pattern kind : %d\n",
             array[m].index, array[m].value, p_arr[array[m].index].pclass);
    }
    
    int samp_types;
    Samp_Node *samp_list;
    samp_types = Samp_Types(array, LEARNING_NUM);
   
    samp_list = (Samp_Node *)malloc(sizeof(Samp_Node) * samp_types);
    
    s = 1;
    samp_list[0].type = array[0].value;
    for(m = 1; m < LEARNING_NUM ; m++){
      if(array[m].value != array[m - 1].value){
    	samp_list[s].type = array[m].value;
    	s ++;
      }
      // printf("%d\n", s);
    }
    
    for(s = 0; s < samp_types; s++){
      printf("%f \n", samp_list[s].type);
    }

    double weight = 1.0 / LEARNING_NUM * 1.0;
    int type_cnt = 0;

    m = 0;
    for(s = 0; s < samp_types; s++){
      printf("array[m].value : %f\t  samp_list[s].type : %f\n", array[m].value,samp_list[s].type);
      while(array[m].value == samp_list[s].type){
    	type_cnt ++;
    	m ++;
      }
      samp_list[s].w = type_cnt * weight;
      type_cnt = 0;
    }

    
    for(s = 0; s < samp_types; s++){
      printf("%f %f \n", samp_list[s].type, samp_list[s].w);
    }

    qsort(samp_list, samp_types, sizeof(Samp_Node), comp_sample);

    samp_list[0].cum_w = samp_list[0].w;

    for(s = 1; s < samp_types; s++){
      samp_list[s].cum_w = samp_list[s - 1].cum_w + samp_list[s].w;
    }

    
    printf("samp_list[s].type \t samp_list[s].w \t samp_list[s].cum_w\n");
    for(s = 0; s < samp_types; s++){
      printf("%f \t  %f \t  %f \n", samp_list[s].type, samp_list[s].w, samp_list[s].cum_w);
    }
    int x;
    double resamples[RESAMPS];
    double r;
    for(x = 0; x < RESAMPS; x++){
      r = (rand()%100) / 100.0;
      //printf("%f \n",r);
      resamples[x] = resamp(samp_list, samp_types, r);
    }
    
    qsort(resamples, RESAMPS, sizeof(double), comp_double);
    
    for(x = 0; x < RESAMPS; x++){
      printf("%f \n", resamples[x]);
    }
    
    free(samp_list);
  }

}
