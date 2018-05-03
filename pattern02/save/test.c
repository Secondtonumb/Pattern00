#include <stdio.h>
#include <stdlib.h>
#include "input_data.h"

#define DATA_NUM 15

typedef struct node {
  struct node *next;
  character_data *ptn;
} Node,*linklist;  


int main(int argc,char* argv[]){
  int m;

  Node *s;
  linklist p,head;
  
  //创建表头结点
  head = (linklist)malloc(sizeof(Node));
  p = head;
  head->next = NULL;
  
  char *listfile = argv[1];
  FILE *files = fopen(listfile, "r"); //ファイル名保存ファイルを開く
  char fileName[256];
  //character_data *pt;
  
  for(m = 0; m < DATA_NUM; m++){
    fscanf(files, "%s", fileName); 
    printf("==> %s <==\n",fileName);
    
    FILE *data_file = fopen(fileName, "r");
    
    s = (linklist)malloc(sizeof(Node));
    s->next =NULL;   
    
    s->ptn = input(s->ptn,data_file);
    
    p->next = s;
    p = s;

    //free(s);
    data_print(p->ptn);
    /* Tt seems that p has the same address as char_data I've defined in input_data.h */
    /* When I free p ,char_data is also freed */
    //  data_free(p->ptn);
    //free(s);
  }

  p = head;
  
  while(p->next != NULL){
    printf("1\n");
    p = p->next; 
    data_print(p->ptn);
    free(p->ptn);
  }
  free(head);
}

