#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 255
#define NS "|-"

char str[MAX_SIZE + 1];

// 状態の定義
typedef enum {
    Sp, Sq, Sr, Sd
} STATE;

void getWord();
void printInfer();
char nextChar();
void printConfiguration(STATE, char *);
void nextState();                // ' |- 'を出力する関数
void runAutomaton();            // オートマトンを実行する関数

int main(){
    // 記号列の読み込み
    getWord();

    // 状態遷移の実行
    runAutomaton();

    printf("\n");

    return 0;
}

void getWord(){
    printf("w = ");
    scanf("%s", str);
}

void printConfiguration(STATE s, char *pStr){
    // 様相の出力
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



    printf(", %s)", pStr);
}


char nextChar(){
    static char *pStr = str;
    char c;

    c = *pStr;
    *pStr++;

    return c;
}

void nextState(){
    printf(" |- ");
}

void runAutomaton(){
    STATE s = Sp;               // q0 = p
    int cnt = 0;                // 処理した後の文字数カウンタ
    char ch;

    // 最初の文字を取得
    ch = nextChar();

    // 状態遷移の実行
    do{
        // 現在の状態の表示
        printConfiguration(s, str + cnt);

        // 状態遷移
        switch(s){
            case Sp:{
                if(ch == 'a'){
                    s = Sq;
                }else{
                    s = Sd;
                }
                break;
            }
            case Sq:{
                if(ch == 'b'){
                    s = Sr;
                }else if(ch != 'a'){
                    s = Sd;
                }
                break;
            }
            case Sr:{
                if(ch != 'b'){
                    s = Sd;
                }
                break;
            }
            case Sd: default:{
                break;
            }
        }

        nextState();

        cnt++;
    }while((ch = nextChar()) != '\0');

    // 現在の状態の表示
    printConfiguration(s, str + cnt);

    putchar('\n');

    if(s == Sr){
        printf("accept\n");
    }else{
        printf("reject\n");
    }
}

// bool isAlphabet(char data){
//     bool flag = false;
//     for(int i = 0; i < 8; i++){
//         if(data == Sigma[i]){
//             flag = true;
//         }
//     }
//     return flag;
// }