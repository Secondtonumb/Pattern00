#include <stdio.h>
#include <stdlib.h>
#include "input_data.h"

#define DATA_NUM 15


int main(int arfc,char* argv[]){
  int m;
  
  char *listfile = argv[1];
  FILE *files = fopen(listfile, "r"); //ファイル名保存ファイルを開く
  char fileName[256];

  for(m = 0; m < DATA_NUM; m++){
    fscanf(files, "%s", fileName); 
    printf("%s\n",fileName);
    FILE *data_file = fopen(fileName, "r");
    input(data_file);
  }
}

