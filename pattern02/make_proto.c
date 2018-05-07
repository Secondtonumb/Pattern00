#include <stdio.h>
#include <stdlib.h>

#include "data_process.h"
#include "file.h"
#include "sort.h"

#define CLUSTER_NUM 3
int CLUSTER_DIC[] =  {2, 7, 9};

int main(int argc,char* argv[]){
  if(argc != 3 ){
    fprintf(stderr,"Usage: ./make_proto <learning_data.list> <protofile.list> \n");
      exit(-1);
  }
  int m;  
  char *learning_listfile = argv[1];
  FILE *files = fopen(learning_listfile, "r"); 
  
  int LEARNING_NUM ; 
  LEARNING_NUM = learning_ptn_num(files);
  
  char fileName[256];
  
  character_data char_data[LEARNING_NUM], proto[CLUSTER_NUM];
    
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

  /* Generate Prototypes */
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

  /* To get the average, we shoud know each patterns' number by statist all learning patterns  */
  /* Still I'm trying to figure it out:) */
  for(m = 0; m < CLUSTER_NUM; m++){
    data_div(&proto[m], 5);
    printf("==> PROTOTYPE %d <==\n", m);
    data_print(&proto[m]);
  }

  /* Get output files' address */
  char *protofile_list = argv[2]; 
  FILE *output = fopen("proto.list","r");
  char pf_file[256];

  for(m = 0; m <CLUSTER_NUM; m++){
    fscanf(output, "%s", pf_file);
    FILE *p = fopen(pf_file, "w");
    proto_output(&proto[m], p);
    printf("==>%s Written succeed<==\n",pf_file);
  }

  /* Free memery */
  for(m = 0; m < LEARNING_NUM; m++){
    data_free(&char_data[m]);
  }

  for(m = 0; m < CLUSTER_NUM; m++){
    data_free(&proto[m]);
  }
  
}

