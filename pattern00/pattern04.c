#include<stdio.h>

int main(int argc, char* argv[]){
    char *fileName = argv[1];

    FILE *fp = fopen(fileName,"r");/*fopenを使って読み込みファイルポインタを取得 */

    int num;
    int i;
    int array[10];
    
    for(i = 0; i < 10; i++){
      fscanf(fp,"%d",&num);
      /*変数numにファイルから読み込んだ数値を代入．fscanfを利用すると良い*/
      array[i] = num;
    }

    int max = array[0];
    int min = array[0];
    for(i = 0; i < 10; i++){
      if(max <= array[i]){
    	max = array[i];
      }
      if(min >= array[i]){
    	min = array[i];
      }
    }
    printf("max=%d\n", max);
    printf("min=%d\n", min); 
    fclose(fp); /* fopenしたファイルはfcloseすること */
}


