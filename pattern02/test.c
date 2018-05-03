#include <stdio.h>
#include <stdlib.h>
#include "input_data.h"
#include "file.h"

#define CLUSTER_NUM 3

int main(int argc,char* argv[]){
  int m;

  char *learning_listfile = argv[1];
  FILE *files = fopen(learning_listfile, "r"); 
  
  int LEARNING_NUM ; 
  LEARNING_NUM = learning_ptn_num(files);
  printf("%d\n",LEARNING_NUM);
  
  char fileName[256];
  
  character_data char_data[LEARNING_NUM], proto[CLUSTER_NUM];

  /* cluster lrn_data,protos; */
  /* lrn_data = (cluster)malloc(sizeof(ptn_node)); */
  /* protos = (cluster)malloc(sizeof(ptn_node)); */
  /* lrn_data-> next = NULL; */
  /* protos->next = NULL; */
  
  for(m = 0; m < LEARNING_NUM; m++){
    fscanf(files, "%s", fileName); 
    printf("==> %s <==\n",fileName);
    
    FILE *data_file = fopen(fileName, "r");

    get_size(&char_data[m],data_file);
    
    data_malloc(&char_data[m]);
    
    input(&char_data[m],data_file);

    data_print(&char_data[m]);

    //data_free(&char_data[m]);

    fclose(data_file);
  }
  
  fclose(files);
  

  for(m = 0; m < CLUSTER_NUM; m++){
    proto[m].width = char_data[0].width;
    proto[m].height = char_data[0].height;
    data_malloc(&proto[m]);
  }
  
  for(m = 0; m < 5;  m++){
    add(&proto[0],&char_data[m]);
    add(&proto[1],&char_data[5 + m]);
    add(&proto[2],&char_data[10 + m]);
  }
  
  for(m = 0; m < CLUSTER_NUM; m++){
    printf("==> PROTOTYPE %d <==\n", m);
    data_print(&proto[m]);
  }
  
  int length[CLUSTER_NUM];
  int i;
  for(i = 0; i < LEARNING_NUM; i++){
    printf("==> RESULT FOR PATTERN %d <==\n", i);
    for(m = 0; m < CLUSTER_NUM; m++){
      length[m] = get_distence(&proto[m],&char_data[i]); 
      printf("%d\n",length[m]);
    }
  }

  /* REMEMBER saved learning pattern and prototype 's memory still not be freed  */
}

