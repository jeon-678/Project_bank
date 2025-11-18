// mouse_console.c
#include <windows.h>
#include <stdio.h>

void mouse_click(void)
{
    HANDLE hInput;
    INPUT_RECORD ir;
    DWORD events;

    // 표준 입력(콘솔 입력 버퍼) 핸들 얻기
    hInput = GetStdHandle(STD_INPUT_HANDLE);

    // 마우스 이벤트를 받도록 설정
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT);

    while (1)
    {
        // 입력 이벤트 1개 읽기
        ReadConsoleInput(hInput, &ir, 1, &events);

        // 마우스 이벤트인 경우만 처리
        if (ir.EventType == MOUSE_EVENT)
        {
            MOUSE_EVENT_RECORD mouse = ir.Event.MouseEvent;

            // 왼쪽 버튼 클릭 감지
            if (mouse.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                    mouse.dwMousePosition.X,
                    mouse.dwMousePosition.Y;
            }
            if (mouse.dwMousePosition.X > 5 && mouse.dwMousePosition.X < 10 &&
                mouse.dwMousePosition.Y > 5 && mouse.dwMousePosition.Y < 10) {

                printf("test");
            }
            // 오른쪽 버튼 클릭 감지
            //else if (mouse.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
            /*{
                    mouse.dwMousePosition.X,
                    mouse.dwMousePosition.Y);
            }*/
        }
    }
}
