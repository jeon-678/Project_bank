/*
* 로그인 창 테스트 진행
*/

#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <windows.h>

typedef struct user {
    char id[64];
    char pw[32];
} USER;

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw_box(int x, int y, int width, int height) {
    int i;
    gotoxy(x, y);
    printf("┌");
    for (i = 0; i < width - 2; i++) printf("─");
    printf("┐");

    for (i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);
        printf("│");
        gotoxy(x + width - 1, y + i);
        printf("│");
    }

    gotoxy(x, y + height - 1);
    printf("└");
    for (i = 0; i < width - 2; i++) printf("─");
    printf("┘");
}

void screen() {

    system("cls");
    draw_box(10, 2, 50, 15);  // 박스 그리기

    gotoxy(30, 6);
    printf("L O G I N");

    gotoxy(15, 10);
    printf("ID       :");

    gotoxy(15, 12);
    printf("Password :");

    gotoxy(0, 17); // 커서 아래로 이동 (박스 밑)
}

int main() {
    char file_id[32];
    char file_pw[32];
    int found = 0;
    
    FILE* fp = NULL;
    fp = fopen("User.txt", "r");
    if (fp == NULL) {
        gotoxy(0, 20);
        printf("파일 열기 실패\n");
        return 1;
    }

    USER jgj;

    memset(jgj.pw, 0, sizeof(jgj.pw)); // 특정 배열만 0으로 초기화

    screen();

    gotoxy(26, 10);
    (void)scanf("%s", jgj.id);


    gotoxy(26, 12);
    int count = 0;
    char ch;
    char* p = &jgj.pw;

    while (1) {

        ch = _getch();

        if (ch == '\r') // 엔터 입력 시 로그인 시도
            break;
        else if (ch == '\b') { // 백스페이스 구현
            *(p + --count) = ' ';
            gotoxy(26 + count, 12);
            printf(" ");
            gotoxy(26 + count, 12);
        }
        else { // 문자 입력시 *로 은닉
            *(p + count) = ch;

            gotoxy(26 + count, 12);
            printf("*");

            count++;
            gotoxy(26 + count, 12);
        }
    }
    gotoxy(0, 20);
    while (fscanf(fp, "%s %s", file_id, file_pw) != EOF) {
        if (strcmp(jgj.id, file_id) == 0 && strcmp(jgj.pw, file_pw) == 0) {
            found = 1;
            break;
        }
    }
    if (found) {
        printf("로그인 성공\n");
    }
    else {
        printf("ID 또는 PW가 잘못되었습니다.\n");
    }
    
    fclose(fp);
    
    return 0;
}