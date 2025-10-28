#include <stdio.h>
#include <windows.h>

int main(void) {
    HANDLE hInput;
    INPUT_RECORD ir;
    DWORD count;

    // 표준 입력(콘솔 입력 버퍼) 핸들 얻기
    hInput = GetStdHandle(STD_INPUT_HANDLE);

    // 마우스 입력 모드 활성화
    SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    printf("마우스를 클릭하면 좌표가 출력됩니다. (Ctrl+C로 종료)\n");

    while (1) {
        ReadConsoleInput(hInput, &ir, 1, &count);

        if (ir.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mer = ir.Event.MouseEvent;
            if (mer.dwEventFlags == 0 && (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)) {
                printf("마우스 왼쪽 클릭: X=%d, Y=%d\n",
                    mer.dwMousePosition.X, mer.dwMousePosition.Y);
            }
        }
    }

    return 0;
}
