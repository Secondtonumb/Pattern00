#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Dim 2
#define Clu 2


#include "evalution.h"
#include "data.h"
#include "file.h"
#include "sort.h"

int Samp_Num(Pattern *arr, int len, int class){
  int i;
  int cnt = 0;
  for(i = 0; i < len; i++){
    if(arr[i].pclass == class) cnt ++;
  }
  return cnt;
}

void resamp(Samp_Node *s, Samp_Node res, int len, double rate){
  int i;
  int m;
  if(rate <= s[0].cum_w){
    for(m = 0; m < Dim;  m++){
      res.data[m] = s[0].data[m];
    }
  }
  else{
    for(i = 1; i < len; i++){
      if(s[i - 1].cum_w < rate && rate <= s[i].cum_w) {
	for(m = 0; m < Dim;  m++){
	  res.data[m] = s[i].data[m];
	}
	break;
      }
    }
  }
}

int main(int argc, char *argv[]){
  if(argc != 4){
    printf("Usage: ./resamp ptns.dat resamp.dat <resamples_num>");
    exit(1);
  }
  
  int i, j, k; //i -> Layer, j -> Cluster, k -> Ptn Dimension
  int m; // m -> Ptn number;
  int n;

  char *learning_listfile = argv[1];
  char *resample_name = argv[2];
  int RESAMPS = atoi(argv[3]);
  
  FILE *ptn_files = fopen(learning_listfile, "r");
  FILE *resamp_file = fopen(resample_name, "w");
  
  int LEARNING_NUM;  
  LEARNING_NUM = learning_ptn_num(ptn_files);

  Pattern p_arr[LEARNING_NUM];

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

  char resamp_name[256];

  qsort(p_arr, LEARNING_NUM, sizeof(Pattern), comp_pclass);

  for(m = 0; m < LEARNING_NUM; m++){
    printf("Pattern kind : %d\n", p_arr[m].pclass);
    data_print(&p_arr[m]);
  }

  int s;
  int old = 0;
  for(n = 0; n < Clu; n++){
    
    int samp_alts_num;
    
    Samp_Node *samp_alts;
      
    samp_alts_num = Samp_Num(p_arr, LEARNING_NUM, n + 1);
    printf("%d\n", samp_alts_num);
    
    samp_alts = (Samp_Node *)malloc(sizeof(Samp_Node) * samp_alts_num);


    for(s = 0; s < samp_alts_num; s++){
      samp_alts[s].type = n + 1;
      samp_alts[s].w = 1.0 / (samp_alts_num * 1.0);
      //printf("%f \n",samp_alts[s].w);
      
      samp_alts[s].data = p_arr[old + s].data;
    }
    
    
    qsort(samp_alts, samp_alts_num, sizeof(Samp_Node), comp_sample);

    /* for(s = 0; s < samp_alts_num; s++){ */
    /*   printf("%f\n", samp_alts[s].w); */
    /*   for(m = 0; m < Dim; m++){ */
    /* 	printf("%f ", samp_alts[s].data[m]); */
    /*   } */
    /*   printf("\n"); */
    /* } */

    samp_alts[0].cum_w = samp_alts[0].w;
    
    for(s = 1; s < samp_alts_num; s++){
      samp_alts[s].cum_w = samp_alts[s - 1].cum_w + samp_alts[s].w;
    }

    /* for(s = 0; s < samp_alts_num; s++){ */
    /*   printf("%f\n", samp_alts[s].cum_w); */
    /* } */
    
    int samp_num = (samp_alts_num * 1.0) / (LEARNING_NUM * 1.0) * RESAMPS;
    printf("samp_num %d\n", samp_num);

    int x;
    Samp_Node resamples[samp_num];
    double r;

    for(x = 0; x < samp_num; x++){
      r = (rand()%1000) / 1000.0;

      if(r <= samp_alts[0].cum_w){
	resamples[x].w = 1.0 / (samp_num * 1.0);
	resamples[x].type = samp_alts[0].type;
	resamples[x].data = samp_alts[0].data;
      }
      else{
	for(s = 1; s < samp_alts_num; s++){
	  if(samp_alts[s - 1].cum_w < r && r <= samp_alts[s].cum_w) {
	    resamples[x].w = 1.0 / (samp_num * 1.0);
	    resamples[x].type = samp_alts[s].type;
	    resamples[x].data = samp_alts[s].data;
	    break;
	  }
	}
      }
    }
    
    for(x = 0; x < samp_num; x++){
      fprintf(resamp_file, "%d ", resamples[x].type);
      for(m = 0; m < Dim; m++){
    	fprintf(resamp_file, "%f ", resamples[x].data[m]);
      }
      //fprintf(resamp_file, "%f ",resamples[x].w);
      fprintf(resamp_file, "\n");
    }
    
    free(samp_alts);
    old = old + samp_alts_num;

  }
  
  fclose(resamp_file);
}
