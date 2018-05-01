#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){

  char *fileName = argv[1]/*最初の引数を代入する*/;
  FILE *fp = fopen(fileName,"r");/*fopenを使って読み込みファイルポインタを取得*/

  int **matrix;
  int raw, colmun;
  int i,j;

  for(i = 0; i < 1; i++){
    fscanf(fp,"%d %d",&raw, &colmun);
  }
  /* Save matrix data into a 1 dimention array */
  int data[raw * colmun];
  
  for(i = 2; i < raw * colmun + 2; i++ ){
     fscanf(fp,"%d",&data[i - 2]);	
  }
  
  /* Ask memory for 2 dimention array */
  matrix = malloc(colmun * sizeof(int*));
    
  for(i = 0; i < colmun; i++){
    matrix[i] = malloc(raw * sizeof(int));
  }
  /* Save data into 2 dimention array */
  for(i = 0; i < colmun; i++){
    for(j = 0; j < raw; j++){
      matrix[i][j] = data[i * raw + j];
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  /* Release memory */
  for(i = 0; i < colmun; i++){
    free(matrix[i]);
  }
  free(matrix);

  fclose(fp); 
}



