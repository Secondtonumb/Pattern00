#include <stdio.h>
#include <stdlib.h>
#define DATA_NUM 15

typedef struct {
  int **data; /*Character Datas*/
  int width; /*Width of Data matrix*/
  int height; /*Height of Data Matrix*/
} character_data;

/* Declarations  */
void data_print(character_data *char_data);
void data_malloc(character_data *char_data);
void data_free(character_data *char_data);

character_data char_data;

character_data input(FILE *data_file){
  int i;
   
  /* Get Width and Height from File and Save into the Struct */
  fscanf(data_file,"%d %d",&char_data.width, &char_data.height);
  
  /* Allocate memory block */  
  data_malloc(&char_data);
    
  /* As the first two data is Width and Height, Start from the Second Element */
  /* (i - 2) / width will return current Raw   */
  /* (i - 2) % width will return current Colmun */
  for(i = 2; i < char_data.width * char_data.height + 2; i++){
    fscanf(data_file,"%d",
	   &char_data.data[(i - 2) / char_data.width][(i - 2) % char_data.width]);
  }
  /* Print result */
  data_print(&char_data);

  /* Free memory */
  data_free(&char_data);

  /* Closes the file associated with the stream and disassociates it */
  fclose(data_file);

  return char_data; 
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
