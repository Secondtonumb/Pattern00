#include<stdio.h>

int main(int argc, char* argv[]){
    char *fileName1 = argv[1];
    char *fileName2 = argv[2];

    FILE *fp1 = fopen(fileName1,"r");/*fopenを使って読み込みファイルポインタを取得 */
    FILE *fp2 = fopen(fileName2,"r");
    
    int num1,num2;
    int i;
    int array_1[10];
    int array_2[10];
    int my_result = 0; 
    for(i = 0; i < 10; i++){
      fscanf(fp1,"%d",&num1);
      fscanf(fp2,"%d",&num2);
      /*変数numにファイルから読み込んだ数値を代入．fscanfを利用すると良い*/
      array_1[i] = num1;
      array_2[i] = num2;      
      my_result += num1 * num2;
    }
    
    printf("result=%d\n", my_result);
    fclose(fp1); /* fopenしたファイルはfcloseすること */
    fclose(fp2);
}
