#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_manager.h"
#include "config.h"
#include "util.h"

void loadUsers(User users[], int* count) {
    FILE* fp = fopen(USER_FILE, "r");
    char line[256];
    *count = 0;

    if (!fp) {
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        trim(line);
        if (line[0] == '\0') continue;

        User u;
        char* token = strtok(line, ",");
        if (!token) continue;
        strncpy(u.id, token, sizeof(u.id)); u.id[sizeof(u.id) - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(u.password, token, sizeof(u.password)); u.password[sizeof(u.password) - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(u.name, token, sizeof(u.name)); u.name[sizeof(u.name) - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(u.phone, token, sizeof(u.phone)); u.phone[sizeof(u.phone) - 1] = '\0';

        users[(*count)++] = u;
    }

    fclose(fp);
}

void saveUsers(const User users[], int count) {
    FILE* fp = fopen(USER_FILE, "w");
    if (!fp) {
        printf("Failed to open user file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s\n",
            users[i].id,
            users[i].password,
            users[i].name,
            users[i].phone
        );
    }

    fclose(fp);
}

void loadAccounts(Account accounts[], int* count) {
    FILE* fp = fopen(ACCOUNT_FILE, "r");
    char line[256];
    *count = 0;

    if (!fp) {
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        trim(line);
        if (line[0] == '\0') continue;

        Account a;
        char* token = strtok(line, ",");
        if (!token) continue;
        a.accountNumber = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(a.ownerId, token, sizeof(a.ownerId)); a.ownerId[sizeof(a.ownerId) - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(a.accountType, token, sizeof(a.accountType)); a.accountType[sizeof(a.accountType) - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        a.balance = atoi(token);

        accounts[(*count)++] = a;
    }

    fclose(fp);
}

void saveAccounts(const Account accounts[], int count) {
    FILE* fp = fopen(ACCOUNT_FILE, "w");
    if (!fp) {
        printf("Failed to open account file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%d\n",
            accounts[i].accountNumber,
            accounts[i].ownerId,
            accounts[i].accountType,
            accounts[i].balance);
    }

    fclose(fp);
}

void appendHistory(int accountNumber, const char* line) {
    char filename[64];
    sprintf(filename, "history_%d.txt", accountNumber);

    FILE* fp = fopen(filename, "a");
    if (!fp) {
        printf("Failed to open history file for writing.\n");
        return;
    }

    fputs(line, fp);
    fclose(fp);
}
