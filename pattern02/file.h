#ifndef STDIO_H
#define STDIO_H

#include <stdio.h>

/* Return the number of Learning data */
int learning_ptn_num(FILE *p){
  char buf[256];
  int line_num = 0;
  while(fgets(buf, 256, p)){
    line_num ++;
    }
  /* After get listfile line number, make file pointer back to the file first */
  fseek(p,0L,SEEK_SET);
  return line_num;
}

/* Return the type of Learning Data from Pattern File's name */
/* Learning Data should be saved in Directroy [learning_data/] */
int get_pattern_type(char *str){
  int i;
  i = atoi(&str[21]);
  return i;
}
/* Return the type of Prototype Data from  File's name */
/* Prototype Data should be saved in Directroy [.] */
int get_pattern_type_1(char *str){
  int i;
  i = atoi(&str[9]);
  return i;
}
/* Save struct prototype variable into Standard File */
/* Format as:
   <width> <height>
   1 0 1 ... 1
   1 1 0 ... 0
   .         .
   .         .
   0 1 0 ... 1
 */

void proto_output(character_data *p, FILE *fp){
  int i,j;
  fprintf(fp,"%d %d",p->width, p->height);
  fprintf(fp,"\n");
  for(i = 0; i < p->height; i++){
    for(j = 0; j < p->width; j++){
      fprintf(fp,"%f ",p->data[i][j]);
    }
    fprintf(fp,"\n");
  }
}

#endif
