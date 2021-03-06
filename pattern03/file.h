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


int get_pattern_type(char *str){
  int i;
  i = atoi(&str[3]) - 1; // 为了和数组元素一致
  return i;
}

#endif
