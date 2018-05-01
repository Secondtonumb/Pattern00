#include <stdio.h>
#include <stdlib.h>

/*ここで構造体を作成*/
typedef struct {
  int **data; /*文字データそのもの*/
  int width; /*文字データの幅*/
  int height; /*文字データの高さ*/
} character_data;

/*文字データを画面に出力する関数のプロトタイプ宣言*/
void data_print(character_data *char_data_out);

void data_malloc(character_data *char_data1);
void data_malloc(character_data *char_data2);
void data_malloc(character_data *char_data_out);

void data_free(character_data *char_data1);
void data_free(character_data *char_data2);
void data_free(character_data *char_data_out);

void data_add(character_data *char_data1, character_data *char_data2,character_data *char_data_out);


int main(int argc, char* argv[]){
  character_data char_data1,char_data2,char_data_out;

  char *fileName1 = argv[1];
  char *fileName2 = argv[2];
  
  FILE *fp1 = fopen(fileName1, "r");
  FILE *fp2 = fopen(fileName2, "r");
  int i, j;

  /* 行と列を獲得し、構造体内に保存 */
  for(i = 0; i < 1; i++){
    fscanf(fp1,"%d %d",&char_data1.width, &char_data1.height);
  }
  for(i = 0; i < 1; i++){
    fscanf(fp2,"%d %d",&char_data2.width, &char_data2.height);
  }
  
  int temp_data1[char_data1.width * char_data1.height];
  int temp_data2[char_data2.width * char_data2.height];
  
  /* 一回行列のデータを一元配列に保存し、後で二次元配列に渡す */
  for(i = 2; i < char_data1.width * char_data1.height + 2;  i++){
    fscanf(fp1,"%d", &temp_data1[i - 2]);
    fscanf(fp2,"%d", &temp_data2[i - 2]);
  }
  
  /* 領域 char_data.data の確保処理 */  
  data_malloc(&char_data1);
  data_malloc(&char_data2);

  char_data_out.width = char_data1.width;
  char_data_out.height = char_data1.height;
  
  data_malloc(&char_data_out);
  
  /* 一回保存したデータを二次元配列に渡して保存 */
  for(i = 0; i < char_data1.height; i++){
    for(j = 0; j < char_data1.width; j++){
      char_data1.data[i][j] = temp_data1[i * char_data1.width + j];
      char_data2.data[i][j] = temp_data2[i * char_data2.width + j];
    }
  }

  data_add(&char_data1, &char_data2, &char_data_out);

  /* 画面に表示 */
  data_print(&char_data_out);
  
  /* 領域 char_data.data の解放処理 */
  data_free(&char_data1);
  data_free(&char_data2);
  data_free(&char_data_out);

  fclose(fp1);
  fclose(fp2);
}

void data_print(character_data *data2print){
  int i, j;
  for(i = 0; i < data2print->height; i++){
    for(j = 0; j < data2print->width; j++){
      printf("%d ", data2print->data[i][j]);
    }
    printf("\n");
  }
}

void data_malloc(character_data *p){
  int i;
  p->data = malloc(p->height * sizeof(int*));
  for(i = 0; i < p->height; i++){
    p->data[i] = malloc(p->width * sizeof(int));
  }
}

void data_free(character_data *q){
  int i;
  for(i = 0; i < q->height; i++){
    free(q->data[i]);
  }
  free(q->data);
}

void data_add(character_data *p, character_data *q, character_data *r){
  int i,j;
  for(i = 0; i < p->height; i++){
    for(j = 0; j < p->width; j++){
      r->data[i][j] = p->data[i][j] + q->data[i][j];
    }
  }
}
