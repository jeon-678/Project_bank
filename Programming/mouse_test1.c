#include <stdio.h>
#include <windows.h>

int main(void) {
    HANDLE hInput;
    INPUT_RECORD ir;
    DWORD count;

    // ǥ�� �Է�(�ܼ� �Է� ����) �ڵ� ���
    hInput = GetStdHandle(STD_INPUT_HANDLE);

    // ���콺 �Է� ��� Ȱ��ȭ
    SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    printf("���콺�� Ŭ���ϸ� ��ǥ�� ��µ˴ϴ�. (Ctrl+C�� ����)\n");

    while (1) {
        ReadConsoleInput(hInput, &ir, 1, &count);

        if (ir.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mer = ir.Event.MouseEvent;
            if (mer.dwEventFlags == 0 && (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)) {
                printf("���콺 ���� Ŭ��: X=%d, Y=%d\n",
                    mer.dwMousePosition.X, mer.dwMousePosition.Y);
            }
        }
    }

    return 0;
}
