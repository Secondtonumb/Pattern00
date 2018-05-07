#include <stdio.h>
#include <stdlib.h>

#include "input_data.h"
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

  /* 产生原型 */

  for(m = 0; m < CLUSTER_NUM; m++){
    proto[m].width = char_data[0].width;
    proto[m].height = char_data[0].height;
    data_malloc(&proto[m]);
  }

  proto[0].pattern = 2;
  proto[1].pattern = 7;
  proto[2].pattern = 9;
  
  for(m = 0; m < LEARNING_NUM;  m++){
    if(char_data[m].pattern == proto[0].pattern){
      add(&proto[0],&char_data[m]);
    }
    else if (char_data[m].pattern == proto[1].pattern){
      add(&proto[1],&char_data[m]);
    }
    else if (char_data[m].pattern == proto[2].pattern){
      add(&proto[2],&char_data[m]);
    }
  }
  
  /* for(m = 0; m < CLUSTER_NUM; m++){ */
  /*   printf("==> PROTOTYPE %d <==\n", m); */
  /*   data_print(&proto[m]); */
  /* } */

  /* 未知模式存储 */
  char *recon_file = argv[2];
  FILE *recon_file_pt = fopen(recon_file, "r");

  character_data rec_data;

  get_feature(&rec_data,recon_file_pt);

  data_malloc(&rec_data);

  input(&rec_data,recon_file_pt);

  data_print(&rec_data);
  
  fclose(recon_file_pt);
  
  /* 评价 */
  int x;
  int k = atoi(argv[3]);

  // k近邻法
  struct node array[LEARNING_NUM];
  for(m = 0; m < LEARNING_NUM; m++){
    array[m].value = get_distence(&char_data[m],&rec_data);
    array[m].index = m;
    printf("%d %d\n",array[m].value,array[m].index);
  }

  qsort(array, LEARNING_NUM, sizeof(struct node), comp_array);

  /* for(m = 0; m < LEARNING_NUM; m++){ */
  /*   printf("%d %d\n",array[m].value,array[m].index); */
  /* } */

  int *nearest_patterns;
  nearest_patterns = (int *)malloc(sizeof(int) * k);
  for(m = 0; m < k; m++){
    nearest_patterns[m] = char_data[array[m].index].pattern;
    printf("Recognition Result of PATTERN by K-NearestNeighbor Method  == %d\n", nearest_patterns[m]);
  }
  
  int result;
  result = maxfreq_ele(nearest_patterns, k, CLUSTER_DIC, 3);
  printf("Recognition Result == %d\n", result);


  /* 原型法 */
  int length[CLUSTER_NUM];

  enlarge(&rec_data, 5);

  for(m = 0; m < CLUSTER_NUM; m++){
    length[m] = get_distence(&proto[m],&rec_data); 
    printf("%d ",length[m]);
  }
  printf("\n");
  x = minimum(length,CLUSTER_NUM);
  rec_data.pattern = proto[x].pattern;
  printf("Recognition Result of PATTERN by Prototype Method == %d\n", rec_data.pattern);
  
  for(m = 0; m < LEARNING_NUM; m++){
    data_free(&char_data[m]);
  }

  for(m = 0; m < CLUSTER_NUM; m++){
    data_free(&proto[m]);
  }
  data_free(&rec_data);
  
}
  /* REMEMBER saved learning pattern and prototype 's memory still not be freed  */


