#include <stdio.h>
#include <stdlib.h>
typedef struct{
  double *data;
}array;

int main(int argc, char * argv[]){
  int i, j, k;
  array *a;
  double *b;
  b = malloc(sizeof(double) * 3);
  a = malloc(sizeof(array*) * 2);
  int len;
  for(i = 0; i < 2; i ++){
      a[i].data = malloc(sizeof(double) * 4); 
  }
  len = sizeof(a->data)/ sizeof(double);
  printf("%d", len);
  len =sizeof(b)/ sizeof(b[0]);
  printf("%d", len);
}
