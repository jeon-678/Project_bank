#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "user.h"

typedef struct {
    int accountNumber;
    char ownerId[30];
    char accountType[20];
    int balance;
} Account;

void createAccount(const User* user);
void showAccountList(const User* user);
void showBalance(const User* user);
void deposit(const User* user);
void withdraw(const User* user);

// optional (stubs in account.c)
void transferMoney(const User* user);
void deleteAccount(const User* user);

#endif
