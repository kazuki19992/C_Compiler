#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 255
char str[MAX_SIZE + 1];

// 状態の定義
typedef enum {
    Sp, Sq, Sr, Sd
} STATE;

void getWord();
void printInfer();
void nextChar();
void printConfiguration(STATE, char *);

int main(){
    STATE s = Sp;               // q0 = p
    int cnt = 0;                // 処理した後の文字数カウンタ
    char ch;

    // 記号列の読み込み
    getWord();

    printConfiguration(s, str + cnt);
    printf("\n");

    return 0;
}

void getWord(){
    printf("w = ");
    scanf("%s", str);
}

void printConfiguration(STATE s, char *str){
    // 初期様相の出力
    printf("(");
    switch(s){
        case Sp:{
            putchar('p');
            break;
        }case Sq:{
            putchar('q');
            break;
        }case Sr:{
            putchar('r');
            break;
        }case Sd:{
            putchar('d');
            break;
        }
    }

    printf(", %s)", str);
}

// char nextChar(int nextPointer){
//     return str[nextPointer];
// }

// bool isAlphabet(char data){
//     bool flag = false;
//     for(int i = 0; i < 8; i++){
//         if(data == Sigma[i]){
//             flag = true;
//         }
//     }
//     return flag;
// }