#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int **data; /*Character Datas*/
  int width; /*Width of Data matrix*/
  int height; /*Height of Data Matrix*/
} character_data;

/* Declarations  */
void data_malloc(character_data *char_data1);
void data_malloc(character_data *char_data2);
void data_malloc(character_data *char_data_out);

void data_add(character_data *char_data1, character_data *char_data2,character_data *char_data_out);

void data_print(character_data *char_data_out);

void data_free(character_data *char_data1);
void data_free(character_data *char_data2);
void data_free(character_data *char_data_out);

int main(int argc, char* argv[]){
  character_data char_data1,char_data2,char_data_out;

  char *fileName1 = argv[1];
  char *fileName2 = argv[2];
  
  FILE *fp1 = fopen(fileName1, "r");
  FILE *fp2 = fopen(fileName2, "r");
  int i, j;

  /* Get Width and Height from File and Save into the Struct */
  fscanf(fp1,"%d %d",&char_data1.width, &char_data1.height);
  fscanf(fp2,"%d %d",&char_data2.width, &char_data2.height);

  /* Check Matrix 1 and 2 of whether they are in the same format */
  if(char_data1.width != char_data2.width || char_data1.height != char_data2.height){
    printf("Raw or Colmun of Matrices seems different.\n");
    printf("EXIT ERROR");
    exit(1);
  }
  else{
    char_data_out.width = char_data1.width;
    char_data_out.height = char_data1.height;

    /* Allocate memory block */
    data_malloc(&char_data1);
    data_malloc(&char_data2);
    data_malloc(&char_data_out);

    /* As the first two data is Width and Height, Start from the Second Element */
    /* (i - 2) / width will return current Raw   */
    /* (i - 2) % width will return current Colmun */
    for(i = 2; i < char_data1.width * char_data1.height + 2;  i++){
      fscanf(fp1,"%d", &char_data1.data[(i - 2)/char_data1.width][(i - 2) % char_data2.width]);
      fscanf(fp2,"%d", &char_data2.data[(i - 2)/char_data2.width][(i - 2) % char_data2.width]);
    }
    
    /* Add  */
    data_add(&char_data1, &char_data2, &char_data_out);

    /* Print result */
    data_print(&char_data_out);
  
     /* Free memory */
    data_free(&char_data1);
    data_free(&char_data2);
    data_free(&char_data_out);
    
    /* Closes the file associated with the stream and disassociates it */
    fclose(fp1);
    fclose(fp2);  
  }
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

/* Nothing Special,jusr add these two Matrices:) */
void data_add(character_data *p, character_data *q, character_data *r){
  int i,j;
  for(i = 0; i < p->height; i++){
    for(j = 0; j < p->width; j++){
      r->data[i][j] = p->data[i][j] + q->data[i][j];
    }
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
