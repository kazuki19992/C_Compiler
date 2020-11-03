#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* 定義 */
#define TOKEN_SIZE 128 // トークンの長さの最大値 
#define STR(var) #var

/* 文字・トークンの種類 */
/* step1, step3 */
typedef enum {
    Digit,
    IntNum,
    LParen,
    RParen,
    Plus,
    Minus,
    Multi,
    Div,
    EOFToken,
    NULLToken,
    Symbol,
    Other
} Kind;

/* トークン */
/* step4 */
typedef struct {
    Kind kind;
    char str[TOKEN_SIZE + 1];
    int val;
} Token;

/* グローバル変数 */
Kind charKind[256]; /* 文字種表 */
FILE *fp;

/* プロトタイプ宣言 */
void initializeCharKind(void);
int nextChar(void);
Token nextToken(void);
void writeTokenStr(char **p, char c); 
void printToken(Token *t);


int main(int argc, char *argv[]) {
	Token token;

	/* 文字種表charKindの初期化 */
//	printf("initializing charKind[]... "); /* 動作確認用．提出時には表示しないこと */
	initializeCharKind();
//	printf("done.\n"); /* 動作確認用．提出時には表示しないこと */

	/* open file argv[1] */
	if (argc < 2) {
		printf("no file name\n");
		exit(EXIT_FAILURE);
	}
	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("error: file \"%s\" can not open\n", argv[1]);
		exit(EXIT_FAILURE);
	} else {
//		printf("file \"%s\" is opened.\n", argv[1]);
	}

	/* nextToken関数によるトークンの取得と表示 */
	token = nextToken();
	while (token.kind != EOFToken) {
		printToken(&token);
		token = nextToken();
	}

	/* close file argv[1] */
	fclose(fp);
//	printf("file \"%s\" is closed.\n", argv[1]); /* 動作確認用．提出時には表示しないこと */

	return 0;
}

/*
 * 文字種表charKindの初期化
 */
void initializeCharKind(void) {
	/* step2 */

    // 初期化
    for(int i = 0; i < 256; i++){
        charKind[i] = Other;
    }

    // Digitの割り当て
    for(int i = '0'; i < '9'; i++){
        charKind[i] = Digit;
    }

    // 個々の文字の割り当て
    charKind['('] = LParen;
    charKind[')'] = RParen;
    charKind['+'] = Plus;
    charKind['-'] = Minus;
    charKind['*'] = Multi;
    charKind['/'] = Div;
}

/*
 * ファイルから次の1文字を取得する
 */
int nextChar(void) {
	static int ch;

	if (ch == EOF) { // 最後に読んだ文字がEOFならば，EOFを返す
		return ch;
	}
	ch = fgetc(fp);


	return ch;
}

/*
 * ファイルから記号を1文字ずつ読み，トークンを取得する
 */
Token nextToken(void) {
	static int ch = ' ';
	Token token = {NULLToken, "", 0};
	char *pStr = token.str;
	int val = 0;
    char intFlg = 0;

	/* step5 */
    ch = nextChar();

    // 空白の読み飛ばし
	while (isspace(ch)) {
		ch = nextChar();
	}

    // デバッグ
    // printf("---テスト用---\n");
    // putchar(ch);
    // putchar('\n');


    // if(ch == NULL){
    //     token.kind = NULLToken;
    //     token.str = "";
    //     token.val = 0;
    //     return token;
    // }

    // while(ch >= '0' && ch <= '9'){
    while(1){
        if(ch < '0' || ch > '9'){
            break;
        }
        *pStr = ch;
        pStr++;
        ch = nextChar();
        intFlg = 1;
    }

    if(intFlg == 1){
        // intだったら
        // 余分に読み込んだ分ひとつfpを戻す
        fseek(fp, -1, SEEK_CUR);
        token.kind = IntNum;
        val = atoi(token.str);
        // token.val = val;
        // return token;
    }else{
        switch(ch){
            case '(':{
                token.kind = LParen;
                *pStr = '(';
                break;
            }
            case ')':{
                token.kind = RParen;
                *pStr = ')';
                break;
            }
            case '+':{
                token.kind = Plus;
                *pStr = '+';
                break;
            }
            case '-':{
                token.kind = Minus;
                *pStr = '-';
                break;
            }
            case '*':{
                token.kind = Multi;
                *pStr = '*';
                break;
            }
            case '/':{
                token.kind = Div;
                *pStr = '/';
                break;
            }
            case EOF:{
                token.kind = EOFToken;
                *pStr = ' ';
                break;
            }
            default:{
                token.kind = Symbol;
                *pStr = (char)ch;
                break;
            }
        }
    }



    // int以外のvalは0になる
    token.val = val;

	return token;
}

void writeTokenStr(char **p, char c) {
	**p = c;
	(*p)++;
}

/* Tokenの表示 */
void printToken(Token *t) {
	printf("%s, val=%d, kind=", t->str, t->val);
	switch (t->kind) {
		case LParen: printf("%s", STR(LParen)); break;
		case RParen: printf("%s", STR(RParen)); break;
		case Plus: printf("%s", STR(Plus)); break;
		case Minus: printf("%s", STR(Minus)); break;
		case Multi: printf("%s", STR(Multi)); break;
		case Div: printf("%s", STR(Div)); break;
		case IntNum: printf("%s", STR(IntNum)); break;
		case Symbol: printf("%s", STR(Symbol)); break;
		case EOFToken: printf("%s", STR(EOFToken)); break;
		case NULLToken: printf("%s", STR(NULLToken)); break;
		case Other: printf("%s", STR(Other)); break;
		default: printf("not implemented"); break;
	}
	printf("\n");
}

