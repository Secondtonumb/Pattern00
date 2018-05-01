#include<stdio.h>

int main(int argc, char* argv[]){
    char *fileName = argv[1]/*最初の引数を代入する*/;

    FILE *fp = fopen(fileName,"r");/*fopenを使って読み込みファイルポインタを取得 \
*/

    int num;
    int i;
    for(i = 0; i < 10; i++){
      fscanf(fp,"%d",&num);      
      /*変数numにファイルから読み込んだ数値を代入．fscanfを利用すると良い*/
      printf("%d\n", num);
    }
    fclose(fp); /* fopenしたファイルはfcloseすること */
}
