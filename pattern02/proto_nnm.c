#include <stdio.h>
#include <stdlib.h>

#include "data_process.h"
#include "file.h"
#include "sort.h"

#define CLUSTER_NUM 3
int CLUSTER_DIC[] =  {2, 7, 9};

int main(int argc,char* argv[]){
 if(argc != 3 ){
    fprintf(stderr,"Usage: ./proto_nnm <proto.list> <unrecognized_data> \n");
      exit(-1);
  }
  int m;  
  char *proto_listfile = argv[1];
  FILE *files = fopen(proto_listfile, "r"); 
  
  int PROTO_NUM ; 
  PROTO_NUM = learning_ptn_num(files);
  
  char fileName[256];
  
  character_data proto[PROTO_NUM];
    
  /* save prototype */
  for(m = 0; m < PROTO_NUM; m++){
    fscanf(files, "%s", fileName);
    //printf("==> %s <==\n",fileName);
    
    FILE *data_file = fopen(fileName, "r");

    get_feature(&proto[m],data_file);
    
    data_malloc(&proto[m]);
    
    input(&proto[m],data_file);

    //data_print(&proto[m]);

    proto[m].pattern = get_pattern_type_1(fileName);
    
    //printf("%d\n",proto[m].pattern);

    //data_free(&proto[m]);

    fclose(data_file);
  }
  
  fclose(files);

  
  char *recon_file = argv[2];
  FILE *recon_file_pt = fopen(recon_file, "r");

  character_data rec_data;

  get_feature(&rec_data,recon_file_pt);

  data_malloc(&rec_data);

  input(&rec_data,recon_file_pt);

  printf("\n==> %s <==\n",recon_file);

  data_print(&rec_data);
  
  fclose(recon_file_pt);
  
  /*  Evaluation Module  */
  printf("\n==> Valuation module ==<\n");
  int x;
  double length[CLUSTER_NUM];

  for(m = 0; m < CLUSTER_NUM; m++){
    length[m] = get_distence(&proto[m],&rec_data);
    printf("Distence with Prototype [%d] : %f \n",proto[m].pattern,length[m]);
  }

  /* Use function minimum defined in sort.h */
  /* x will be the smallest element's index  */
  x = min_ele_index(length,PROTO_NUM);
  rec_data.pattern = proto[x].pattern; 
  printf("\n==> Recognition Result of PATTERN by Prototype Method <==\n==> %d <==\n", rec_data.pattern);

  /* Free Memory  */
 for(m = 0; m < CLUSTER_NUM; m++){
    data_free(&proto[m]);
  }
   data_free(&rec_data);
}

