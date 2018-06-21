#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Dim 2
#define Clu 3

#include "evalution.h"
#include "neural.h"
#include "data.h"
#include "file.h"

int main(int argc, char *argv[]){
  if(argc != 4){
    printf("Usage: ./rec <testset.list> <trained_bias> <trained_weights.list>");
    exit(1);
  }
  
  int i, j, k; //i -> Layer, j -> Cluster, k -> Ptn Dimension
  
  int m; // m -> Ptn number;

  char *learning_listfile = argv[1];
  char *bias_name = argv[2];
  char *weight_listfile = argv[3];
  
  FILE *ptn_files = fopen(learning_listfile, "r");
  FILE *bias_file = fopen(bias_name, "r");
  FILE *weight_files = fopen(weight_listfile, "r");
  
  int PTN_NUM;
  PTN_NUM = learning_ptn_num(ptn_files);
  int Layer;
  Layer = learning_ptn_num(weight_files);

  char ptn_name[256],w_name[256];
  Pattern p_arr[PTN_NUM];

  Neural n_net[Layer][Clu];

  /* Pattern Input */
  for(m = 0; m < PTN_NUM; m++){
    fscanf(ptn_files, "%s", ptn_name);

    FILE *data_file = fopen(ptn_name, "r");
    
    get_feature(&p_arr[m],data_file);

    data_malloc(&p_arr[m]);

    input_pattern(&p_arr[m],data_file);

    p_arr[m].pclass = get_pattern_type(ptn_name);
    
    fclose(data_file);
  }
  fclose(ptn_files);

  /* Read first Layer's weights */
  fscanf(weight_files, "%s", w_name);
  
  FILE *w_data_file = fopen(w_name, "r");

  for(j = 0; j < Clu; j++){
    N_first_layer_malloc(&n_net[0][j]);
  }
  
  for(j = 0; j < Clu; j++){
    for(k = 0; k < Dim ; k++){
      fscanf(w_data_file, "%lf", &n_net[0][j].w[k]);
    }
  }
  
  /* Read Other Layers' weights  */
  for(i = 1; i < Layer; i++){
    fscanf(weight_files, "%s", w_name);

    FILE *w_data_file = fopen(w_name, "r");
    for(j = 0; j < Clu; j++){
      N_malloc(&n_net[i][j]);
    }
    for(j = 0; j < Clu; j++){
      for(k = 0; k < Clu ; k++){
        fscanf(w_data_file, "%lf", &n_net[i][j].w[k]);
      }
    }
    fclose(w_data_file);
  }  
  fclose(weight_files);
    
  /* Bias file Input */
  double *b;
  b = malloc(sizeof(double) * Layer);
  for(i = 1; i < Layer + 1; i++){
    fscanf(bias_file,"%lf", &b[i - 1]);
  }
  fclose(bias_file);
  
  double *L_input; //Layer's input
  L_input = malloc(sizeof(double) * Clu);

  /* Training Begin */
  for(m = 0; m < PTN_NUM; m++){

    double *init_p = p_arr[m].data;
    data_print(&p_arr[m]);
    /* Forward */

    for(j = 0; j < Clu; j++){
      n_net[0][j].g = multi(n_net[0][j].w, init_p, Dim) + b[0];
      n_net[0][j].h = S(n_net[0][j].g);
    }

    for(j = 0; j < Clu; j++){
      L_input[j] = n_net[0][j].h;
    }

    for(i = 1; i < Layer ; i++){
      for(j = 0; j < Clu; j++){
	n_net[i][j].g = multi(n_net[i][j].w, L_input, Clu) + b[i];
	n_net[i][j].h = S(n_net[i][j].g);
      }

      for(j = 0; j < Clu; j++){
	L_input[j] = n_net[i][j].h;
      }
    }

    for(j = 0; j < Clu; j++){
      printf("%f,", L_input[j]);
    }
    int res = max_ele_index(L_input, Clu);
    printf("\nRecog result: CLuster[%d]\n", res);
  }

  // Data Free Module
  for(i = 0; i < Layer; i++){
    for(j = 0; j < Clu; j++){
      N_free(&n_net[i][j]);
    }
  }
  
  for(m = 0 ; m < PTN_NUM; m++){
    data_free(&p_arr[m]);
  }
  
  free(b);
  free(L_input);
}
