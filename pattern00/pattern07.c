#include <stdio.h>
#include <stdlib.h>

/*ここで構造体を作成*/
typedef struct {
  int **data; /*文字データそのもの*/
  int width; /*文字データの幅*/
  int height; /*文字データの高さ*/
} character_data;

/*文字データを画面に出力する関数のプロトタイプ宣言*/
void data_print(character_data *char_data);

int main(int argc, char* argv[]){
  character_data char_data;

  char *fileName = argv[1];
  FILE *fp = fopen(fileName, "r");
  int i, j;

  for(i = 0; i < 1; i++){
    fscanf(fp,"%d %d",&char_data.width, &char_data.height);
  }
  
  /* 領域 char_data.data の確保処理 */
  char_data.data = malloc(char_data.height * sizeof(int*));

  for(i = 0; i < char_data.height; i++){
    char_data.data[i] = malloc(char_data.width * sizeof(int));
  }
  
  for(i = 2; i < char_data.width * char_data.height + 2; i++){
    fscanf(fp,"%d",&char_data.data[(i - 2) / char_data.width][(i - 2) % char_data.width]);
  }

  /* 画面に表示 */
  data_print(&char_data);

  /* 領域 char_data.data の解放処理 */
  for(i = 0; i < char_data.height; i++){
    free(char_data.data[i]);
  }
  free(char_data.data);

  fclose(fp);
}

/*文字データ（ここでは行列）を画面に出力する関数*/
/* 注意：関数をここで宣言する場合は，main関数の前にプロトタイプ宣言が必要です．*/
/* プロトタイプ宣言をする場所はよく考えましょう． */
void data_print(character_data *data2print){
  int i, j;
  for(i = 0; i < data2print->height; i++){
	for(j = 0; j < data2print->width; j++){
	  printf("%d ", data2print->data[i][j]);
	}
	printf("\n");
  }
}
