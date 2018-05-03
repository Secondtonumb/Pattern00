#include <stdio.h>
#include <stdlib.h>
#include "input_data.h"

#define DATA_NUM 15

int main(int argc,char* argv[]){
  int m;
  
  char *listfile = argv[1];
  FILE *files = fopen(listfile, "r"); //ファイル名保存ファイルを開く
  char fileName[256];
  
  character_data char_data[DATA_NUM],proto[3];
  
  for(m = 0; m < DATA_NUM; m++){
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
  
  for(m = 0; m < 3; m++){
    proto[m].width = char_data[0].width;
    proto[m].height = char_data[0].height;
    data_malloc(&proto[m]);
  }
  
  for(m = 0; m < 5;  m++){
    add(&proto[0],&char_data[m]);
    add(&proto[1],&char_data[5 + m]);
    add(&proto[2],&char_data[10 + m]);
  }
  
  for(m = 0; m < 3; m++){
    data_print(&proto[m]);
  }
  
  int length;
  
  for(m = 0; m < DATA_NUM; m++){
    length = get_distence(&proto[2],&char_data[m]);
    printf("%d\n",length);
  }
}

