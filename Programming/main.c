/*
* 테스트 진행
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>

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
    system("color 0f");

    system("cls");
    draw_box(10, 2, 50, 15);  // 박스 그리기

    draw_box(12, 3, 18, 3);
    gotoxy(13, 4);
    printf("\t 1. 입금");
    draw_box(12, 6, 18, 3);
    gotoxy(13, 7);
    printf("\t 2. 출금");

    gotoxy(38, 5);
    printf("총 자산: 6조");
    gotoxy(38, 6);
    printf("현 계좌 자산: 5조5억");

    gotoxy(25, 13);
    printf("선택:");
    gotoxy(30, 14);
    printf("──────────────");


    gotoxy(0, 17); // 커서 아래로 이동 (박스 밑)
}

int main() {

    screen();

    return 0;
}