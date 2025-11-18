#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "util.h"

// date/time
void getCurrentTime(char* buffer) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    sprintf(buffer, "%04d-%02d-%02d %02d:%02d",
        t->tm_year + 1900,
        t->tm_mon + 1,
        t->tm_mday,
        t->tm_hour,
        t->tm_min);
}

// safe integer input
int getIntegerInput(const char* msg) {
    char input[100];
    int value;

    while (1) {
        printf("%s", msg);
        fgets(input, sizeof(input), stdin);

        int valid = 1;
        int start = 0;

        if (input[0] == '-') start = 1;

        for (int i = start; input[i] != '\0' && input[i] != '\n'; i++) {
            if (!isdigit((unsigned char)input[i])) {
                valid = 0;
                break;
            }
        }

        if (valid) {
            sscanf(input, "%d", &value);
            return value;
        }

        printf("Invalid input. Enter numbers only.\n");
    }
}

void trim(char* str) {
    int start = 0;
    int end = strlen(str) - 1;

    while (isspace((unsigned char)str[start])) start++;
    while (end >= start && isspace((unsigned char)str[end])) end--;

    int j = 0;
    for (int i = start; i <= end; i++) str[j++] = str[i];
    str[j] = '\0';
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
