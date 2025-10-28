#include <stdio.h>
#include <windows.h>

int main(void) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    if (hInput == INVALID_HANDLE_VALUE || hInput == NULL) {
        fprintf(stderr, "GetStdHandle 실패. 에러 코드: %lu\n", GetLastError());
        return 1;
    }

    // 현재 콘솔 모드 저장(복원용)
    DWORD prevMode;
    if (!GetConsoleMode(hInput, &prevMode)) {
        fprintf(stderr, "GetConsoleMode 실패. 에러 코드: %lu\n", GetLastError());
        return 1;
    }

    // 필요 모드 설정
    if (!SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS)) {
        fprintf(stderr, "SetConsoleMode 실패. 에러 코드: %lu\n", GetLastError());
        // 필요하면 prevMode로 복원 가능
        return 1;
    }

    INPUT_RECORD ir;
    DWORD count;

    // 이벤트 읽기 루프 (간단)
    while (1) {
        if (!ReadConsoleInput(hInput, &ir, 1, &count)) {
            fprintf(stderr, "ReadConsoleInput 실패. 에러 코드: %lu\n", GetLastError());
            break;
        }
        if (count == 0) continue; // 읽은 이벤트 없음
        // ... 이벤트 처리 ...
    }

    // 모드 복원 (선택적)
    SetConsoleMode(hInput, prevMode);
    return 0;
}
