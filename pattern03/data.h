#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  double *data; /*Character Datas*/
  int dim; /*dimension of Data Array*/
  int pclass;
} Pattern;

void input(Pattern *p,FILE *df){
  int i;
  for(i = 1; i < p->dim + 1; i++){
    fscanf(df,"%lf", &p->data[i - 1]);
  }  
}

void input_weight(double **a, int x, int y,  FILE *df){
  int i;
  a = malloc(x * sizeof(double*));
  for(i = 0; i < x; i++){
    a[i] = malloc(y * sizeof(double));
  }
   
  for(i = 0; i < x * y; i++){
    fscanf(df,"%lf", &a[i / y][i % y]);
    }
}

/* Get Width and Height from File and Save into the Struct */
void get_feature(Pattern *p, FILE *ptr){
  fscanf(ptr,"%d",&p->dim);
}

/* Print result in a matrix format */
void data_print(Pattern *data2print){
  int i;
  for(i = 0; i < data2print->dim; i++){
      printf("%.0f ", data2print->data[i]);
    }
  printf("\n");
}

/* Allocate memory block */
/* p->data save as the head of Two-dimensional array */
/* p->data[i] save as the head of each One-dimensional array */
void data_malloc(Pattern *p){
  int i;
  p->data = malloc(p->dim * sizeof(double*));
}

/* Free memory  */
/* First Free each One-dimensional array,then the whole Two-dimensional array */
void data_free(Pattern *q){
  free(q->data);
}
