#include <stdio.h>
#include <stdlib.h>

#include "data_process.h"
#include "file.h"
#include "sort.h"

#define CLUSTER_NUM 3

#define ARR_LEN(array, length){ length =  sizeof(array) / sizeof(array[0]); }


int main(int argc,char* argv[]){
  int m;  
  int CLUSTER_DIC[] =  {2, 7, 9};
  
  char *learning_listfile = argv[1];
  FILE *files = fopen(learning_listfile, "r"); 
  
  int LEARNING_NUM ; 
  LEARNING_NUM = learning_ptn_num(files);
  
  char fileName[256];
  
  character_data char_data[LEARNING_NUM], proto[CLUSTER_NUM];
    
  /* 存储学习用模式数据 */
  for(m = 0; m < LEARNING_NUM; m++){
    fscanf(files, "%s", fileName);
    
    //printf("==> %s <==\n",fileName);
    
    FILE *data_file = fopen(fileName, "r");

    get_feature(&char_data[m],data_file);
    
    data_malloc(&char_data[m]);
    
    input(&char_data[m],data_file);

    //data_print(&char_data[m]);

    char_data[m].pattern = get_pattern_type(fileName);
    
    // printf("%d\n",char_data[m].pattern);

    //data_free(&char_data[m]);

    fclose(data_file);
  }
  
  fclose(files);

  /* 未知模式存储 */
  char *recon_file = argv[2];
  FILE *recon_file_pt = fopen(recon_file, "r");

  character_data rec_data;

  get_feature(&rec_data,recon_file_pt);

  data_malloc(&rec_data);

  input(&rec_data,recon_file_pt);

  printf("\n==> %s <==\n",recon_file);
  data_print(&rec_data);
  
  fclose(recon_file_pt);
  
  /* 评价 */
  int x;
  int k = atoi(argv[3]);

  // k近邻法
  printf("\n==> Valuation Module <==\n");
  struct node array[LEARNING_NUM];
  for(m = 0; m < LEARNING_NUM; m++){
    array[m].value = get_distence(&char_data[m],&rec_data);
    array[m].index = m;
    //  printf("%d %d\n",array[m].value,array[m].index);
  }

  qsort(array, LEARNING_NUM, sizeof(struct node), comp_array);

  /* for(m = 0; m < LEARNING_NUM; m++){ */
  /*   printf("%d %d\n",array[m].value,array[m].index); */
  /* } */

  int *nearest_patterns;
  nearest_patterns = (int *)malloc(sizeof(int) * k);
  for(m = 0; m < k; m++){
    nearest_patterns[m] = char_data[array[m].index].pattern;
    printf("No. %d nestest pattern : %d\n distence : %d\n", m + 1,array[m].index, nearest_patterns[m]);
  }

  printf("\n==> Result <==\n");
  int result;
  result = maxfreq_ele(nearest_patterns, k, CLUSTER_DIC, CLUSTER_NUM);
  printf("Recognition Result == %d\n", result);

  for(m = 0; m < LEARNING_NUM; m++){
    data_free(&char_data[m]);
  }

  data_free(&rec_data);
  
}

