#include <stdio.h>
#include <windows.h>

int main(void) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    if (hInput == INVALID_HANDLE_VALUE || hInput == NULL) {
        fprintf(stderr, "GetStdHandle ����. ���� �ڵ�: %lu\n", GetLastError());
        return 1;
    }

    // ���� �ܼ� ��� ����(������)
    DWORD prevMode;
    if (!GetConsoleMode(hInput, &prevMode)) {
        fprintf(stderr, "GetConsoleMode ����. ���� �ڵ�: %lu\n", GetLastError());
        return 1;
    }

    // �ʿ� ��� ����
    if (!SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS)) {
        fprintf(stderr, "SetConsoleMode ����. ���� �ڵ�: %lu\n", GetLastError());
        // �ʿ��ϸ� prevMode�� ���� ����
        return 1;
    }

    INPUT_RECORD ir;
    DWORD count;

    // �̺�Ʈ �б� ���� (����)
    while (1) {
        if (!ReadConsoleInput(hInput, &ir, 1, &count)) {
            fprintf(stderr, "ReadConsoleInput ����. ���� �ڵ�: %lu\n", GetLastError());
            break;
        }
        if (count == 0) continue; // ���� �̺�Ʈ ����
        // ... �̺�Ʈ ó�� ...
    }

    // ��� ���� (������)
    SetConsoleMode(hInput, prevMode);
    return 0;
}
