#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DATA_NUM 15

typedef struct {
  int **data; /*Character Datas*/
  int width; /*Width of Data matrix*/
  int height; /*Height of Data Matrix*/
  int pattern;
} character_data;

void input(character_data *p,FILE *df){
  int i;
  for(i = 2; i < p->width * p->height + 2; i++){
    fscanf(df,"%d",
	   &p->data[(i - 2) / p->width][(i - 2) % p->width]);
  }  
}

/* Get Width and Height from File and Save into the Struct */
void get_feature(character_data *p, FILE *ptr){
  fscanf(ptr,"%d %d",&p->width, &p->height);
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

int get_distence(character_data *p, character_data *q){
  int i, j;
  int dis = 0;
  for(i = 0; i < p->height; i++){
    for(j = 0; j < p->width; j++){
      dis += abs( p->data[i][j] -  q->data[i][j]); 
    }
  }
  return dis;
}
  
void enlarge(character_data *p, int power){
 int i, j;
  for(i = 0; i < p->height; i++){
    for(j = 0; j < p->width; j++){
      p->data[i][j] = p->data[i][j] * power;
    }
  }
}
