#include<stdio.h>
#include<ctype.h>
int main(int argc, char *argv[]){
    FILE *fp;
    char str[256];

    fp = fopen(argv[1], "r");

    if(fp == NULL){
        // 失敗時
        printf("ファイルオープンに失敗");
        return -1;
    }

    // 読み込みと出力を行う
    while((fgets(str, 256, fp)) != NULL){
        // 変換処理を行う
        for(int i = 0; i < 256; i++){
            if(islower((int)str[i]) != 0){
                str[i] = (char)toupper((int)str[i]);
            }
        }
        // 格納された文字を出力
        printf("%s", str);
    }

    // ファイルをクローズ
    fclose(fp);
    return 0;
}