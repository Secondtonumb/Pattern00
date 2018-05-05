#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DATA_NUM 15

typedef struct {
  int **data; /*Character Datas*/
  int pattern;
  int width; /*Width of Data matrix*/
  int height; /*Height of Data Matrix*/
} character_data;

typedef struct node {
  struct node *next;
  character_data ptn;
}*cluster,ptn_node;

void input(character_data *p,FILE *df){
  int i;
  for(i = 3; i < p->width * p->height + 3; i++){
    fscanf(df,"%d",
	   &p->data[(i - 3) / p->width][(i - 3) % p->width]);
  }  
}

/* Get Width and Height from File and Save into the Struct */
void get_feature(character_data *p, FILE *ptr){
  fscanf(ptr,"%d %d %d",&p->pattern, &p->width, &p->height);
}

/* Print result in a matrix format */
void data_print(character_data *data2print){
  int i, j;
  for(i = 0; i < data2print->height; i++){
    for(j = 0; j < data2print->width; j++){
      printf("%d ", data2print->data[i][j]);
    }
    printf("\n");
  }
}

/* Allocate memory block */
/* p->data save as the head of Two-dimensional array */
/* p->data[i] save as the head of each One-dimensional array */
void data_malloc(character_data *p){
  int i;
  p->data = malloc(p->height * sizeof(int*));
  for(i = 0; i < p->height; i++){
    p->data[i] = malloc(p->width * sizeof(int));
  }
}

/* Free memory  */
/* First Free each One-dimensional array,then the whole Two-dimensional array */
void data_free(character_data *q){
  int i;
  for(i = 0; i < q->height; i++){
    free(q->data[i]);
  }
  free(q->data);
}

void add(character_data *p, character_data *q){
  int i, j;
  for(i = 0; i < p->height; i++){
    for(j = 0; j < p->width; j++){
      p->data[i][j] += q->data[i][j];
    }
  }
}

float get_distence(character_data *p, character_data *q){
  int i, j;
  float dis = 0;
  for(i = 0; i < p->height; i++){
    for(j = 0; j < p->width; j++){
      dis += abs( p->data[i][j] -  5 * q->data[i][j]); 
    }
  }
  return dis;
}
  
