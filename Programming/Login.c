/*
* �׽�Ʈ ����
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>

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
    printf("��");
    for (i = 0; i < width - 2; i++) printf("��");
    printf("��");

    for (i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);
        printf("��");
        gotoxy(x + width - 1, y + i);
        printf("��");
    }

    gotoxy(x, y + height - 1);
    printf("��");
    for (i = 0; i < width - 2; i++) printf("��");
    printf("��");
}

void screen() {
    system("cls");
    draw_box(10, 5, 50, 10);  // �ڽ� �׸���

    gotoxy(15, 8);
    printf("ID       :");

    gotoxy(15, 10);
    printf("Password :");

    gotoxy(0, 17); // Ŀ�� �Ʒ��� �̵� (�ڽ� ��)
}

int main() {

    USER jgj;
    
    memset(jgj.pw, 0, sizeof(jgj.pw)); // Ư�� �迭�� 0���� �ʱ�ȭ

    screen();

    gotoxy(26, 8);
    (void)scanf("%s", jgj.id);

    gotoxy(26, 10);
    int count = 0;
    char ch;
    char* p = &jgj.pw;

    while (1) {

        ch = _getch();

        if (ch == '\r') // ���� �Է� �� �α��� �õ�
            break;
        else if (ch == '\b') { // �齺���̽� ����
            *(p + --count) = ' ';
            gotoxy(26 + count, 10);
            printf(" ");
            gotoxy(26 + count, 10);
        }
        else { // ���� �Է½� *�� ����
            *(p + count) = ch;

            gotoxy(26 + count, 10);
            printf("*");

            count++;
            gotoxy(26 + count, 10);
        }
    }

    gotoxy(0, 17);
    printf("%s\n", jgj.id);
    printf("%s\n", jgj.pw);

    return 0;
}