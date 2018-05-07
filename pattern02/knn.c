#include <stdio.h>
#include <stdlib.h>

#include "data_process.h"
#include "file.h"
#include "sort.h"

/* Define CLUSTER's type and numbers first*/
/* A more reasonable mathod is to get these variable from learning datas */
/* I'm still cling to solve this problem;) */

#define CLUSTER_NUM 3
int CLUSTER_DIC[] =  {2, 7, 9};

int main(int argc,char* argv[]){
  if(argc != 4 ){
    fprintf(stderr,"Usage: ./knn <learning_data.list> <unrecognized_data> <K>\n");
      exit(-1);
  }
  else{
  int m;

  char *learning_listfile = argv[1];
  FILE *files = fopen(learning_listfile, "r"); 
  
  int LEARNING_NUM ; 
  LEARNING_NUM = learning_ptn_num(files);
  
  char fileName[256];
  
  character_data char_data[LEARNING_NUM];
    
  /* Get Learning Datas from Learning Pattern Files */
  /*  Save data in struct character_data char_data[LEARNING_NUM] */

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

  /* Get Datas from Unrecognized Pattern Files */
  /* Save data in struct rec_data */

  char *recon_file = argv[2];
  FILE *recon_file_pt = fopen(recon_file, "r");

  character_data rec_data;

  get_feature(&rec_data,recon_file_pt);

  data_malloc(&rec_data);

  input(&rec_data,recon_file_pt);

  printf("\n==> %s <==\n",recon_file);
  data_print(&rec_data);
  
  fclose(recon_file_pt);
  
  /* Evaluation Module */
  
  int x;
  int k = atoi(argv[3]);

  /* Save distences and their index in struct node(which is defined in sort.h) */
  /* In order to get the smallest [k]th distances and their patterns  */
  printf("\n==> Valuation Module <==\n");
  struct node array[LEARNING_NUM];
  for(m = 0; m < LEARNING_NUM; m++){
    array[m].value = get_distence(&char_data[m],&rec_data);
    array[m].index = m;
  }

  /* Use Function qsort to sort the distances  */
  /* array.value will be sort in an ascending order */
  /* Meanwhile, array.index will show elements' original index before sorting */
  qsort(array, LEARNING_NUM, sizeof(struct node), comp_array);

  /* int array nearest_patterns will show the smallest kth distences */
  int *nearest_patterns;
  nearest_patterns = (int *)malloc(sizeof(int) * k);
  for(m = 0; m < k; m++){
    nearest_patterns[m] = char_data[array[m].index].pattern;
    printf("No. %d nestest pattern [PATTERN NO.%d]\nPattern kind : %d\n", m + 1,array[m].index, nearest_patterns[m]);
  }

  /* Result Generation */
  
  /* Evalue the combination of [nearest_patterns] */
  /* Return the element which comes most frequentlly */
  /* However, Reject while several values have the most frequency at the same time (Result == -1 ) */
  printf("\n==> Result <==\n");
  int result;
  result = maxfreq_ele(nearest_patterns, k, CLUSTER_DIC, CLUSTER_NUM);
  printf("Recognition Result == %d\n", result);

  /* Free Memory  */
  for(m = 0; m < LEARNING_NUM; m++){
    data_free(&char_data[m]);
  }

  data_free(&rec_data);
  }
}

