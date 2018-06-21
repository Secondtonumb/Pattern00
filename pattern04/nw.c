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
  if(argc != 7){
    printf("Usage: ./nw <training_pattern_list>\n" "<init_bias>\n" "<init_weight_list_for_training>\n" "<bias_training_result>\n" "<weights_training_result_list>\n" "<convolution method>");
    exit(1);
  }
  
  double rho;
  rho = 0.1;
  int i, j, k; //i -> Layer, j -> Cluster, k -> Ptn Dimension
  
  int m; // m -> Ptn number;

  char *learning_listfile = argv[1];
  char *bias_name = argv[2];
  char *weight_listfile = argv[3];
  char *res_bias_name = argv[4];
  char *res_weight_listfile = argv[5];

  int conv_method = atoi(argv[6]);

  double Threshold = 0.1;
  int epoch = 10000;
  
  FILE *ptn_files = fopen(learning_listfile, "r");
  FILE *bias_file = fopen(bias_name, "r");
  FILE *weight_files = fopen(weight_listfile, "r");
  FILE *res_weight_files = fopen(res_weight_listfile, "r");
  FILE *res_bias_file = fopen(res_bias_name, "w");
  
  int LEARNING_NUM;
  
  LEARNING_NUM = learning_ptn_num(ptn_files);
  int Layer;
  Layer = learning_ptn_num(weight_files);

  char ptn_name[256],w_name[256];
  Pattern p_arr[LEARNING_NUM];

  Neural n_net[Layer][Clu];

  for(m = 0; m < LEARNING_NUM; m++){
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
  for(i = 0; i < Layer; i++){
    fscanf(bias_file,"%lf", &b[i]);
  }
  fclose(bias_file);

  /* Create Teacher Signal (One hot vector) */
  double **label;
  label = malloc(sizeof(double*) * LEARNING_NUM);

  for(m = 0 ; m < LEARNING_NUM; m++){
    label[m] = malloc(sizeof(double) * Clu);
    for(j = 0; j < Clu; j++){
      label[m][j] = 0.0;
    }
    label[m][p_arr[m].pclass] = 1.0;
  }
  
  double *L_input; //Layer's input
  L_input = malloc(sizeof(double) * Clu);

  int n = 0;// n -> epoch
  int flag[LEARNING_NUM];

  for(i = 0; i < LEARNING_NUM; i++){
    flag[i] = 1;
  }

  /* Training Begin */
  while(conv(flag, LEARNING_NUM)){
    for(m = 0; m < LEARNING_NUM; m++){
      double *init_p = p_arr[m].data;

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
      
      /* if(judge_max(L_input, Clu, p_arr[m].pclass) != -1){ */
      /* 	flag[m] = 1; */
      /* } */

      /* if(label[m][p_arr[m].pclass] - L_input[p_arr[m].pclass] > Threshold){ */
      /* 	flag[m] = 1; */
      /* } */

      if(n < epoch * LEARNING_NUM){
      	flag[m] = 1;
      	n ++;
      }
      
      else{
	flag[m] = 0;
      }
      
      /* Backward */

      /* Get Output Layer's Epsilon */
      for(j = 0; j < Clu; j++){
	n_net[Layer - 1][j].e = op_layer_e(label[m][j], n_net[Layer - 1][j].h);
      }    

      double e2bcorr[Clu], w2bcorr[Clu];

      /* Get Hidden Layers' Epsilon */
      for(i = Layer - 2; i >= 0; i--){
	for(j = 0; j < Clu; j++){
	  e2bcorr[j] = n_net[i + 1][j].e;
	}
    
	for(j = 0; j < Clu; j++){
	  for(k = 0; k < Clu; k++){
	    w2bcorr[k] = n_net[i + 1][k].w[j];
	  }
	  n_net[i][j].e = hid_layer_e(w2bcorr, e2bcorr, n_net[i][j].h);
	}
      }
      
      /* After Eplison Generated, Update weights */
      /* Layer[1] ~ Layer[<output>] */
      for(i = Layer - 1; i > 0; i--){
	for(j = 0; j < Clu; j++){
	  for(k = 0; k < Clu; k++){
	    n_net[i][j].w[k] += - rho * n_net[i][j].e * n_net[i - 1][k].h;
	  }
	  b[i] += - rho * n_net[i][j].e;
	}
      }

      /* Layer[0] */
      for(j = 0; j < Clu; j++){
	for(k = 0; k < Dim; k++){
	  n_net[0][j].w[k] += - rho * n_net[0][j].e * init_p[k];
	}
	b[0] += - rho * n_net[0][j].e;
      } 
    }    
    printf("\n");
  }

  /* Parameter Output */
  // Weights
  char res_name[256];

  for(i = 0; i < Layer; i++){
    
    fscanf(res_weight_files, "%s", res_name);

    FILE *op_file = fopen(res_name, "w");

    for(j = 0; j < Clu; j++){
      weight_output(&n_net[i][j], op_file, i);
    }
    
    fclose(op_file);
  }

  //Bias
  fprintf(res_bias_file,"%d",Layer);
  fprintf(res_bias_file,"\n");

  for(i = 0; i < Layer; i++){
    fprintf(res_bias_file,"%f ",b[i]);
  }
  fclose(res_bias_file);   
      
  for(i = 0; i < Layer; i++){
    for(j = 0; j < Clu; j++){
      N_free(&n_net[i][j]);
    }
  }
  
  // Data Free Module
  for(m = 0 ; m < LEARNING_NUM; m++){
    data_free(&p_arr[m]);
    free(label[m]);
  }
  free(label);
  free(b);
  free(L_input);
}
