#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "transaction.h"
#include "util.h"
#include "file_manager.h"

void addTransaction(int accountNumber, const char* type, int amount, int balance) {
    char line[256];
    char timeStr[20];
    getCurrentTime(timeStr);

    // format: date,type,amount,balance
    sprintf(line, "%s,%s,%d,%d\n", timeStr, type, amount, balance);
    appendHistory(accountNumber, line);
}

void showTransaction(int accountNumber) {
    char filename[64];
    sprintf(filename, "history_%d.txt", accountNumber);

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("No transaction history for account %d.\n", accountNumber);
        return;
    }

    char line[256];
    printf("==== Transaction History for %d ====\n", accountNumber);
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}
