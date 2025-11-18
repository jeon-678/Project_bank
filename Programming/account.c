#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "account.h"
#include "file_manager.h"
#include "transaction.h"
#include "util.h"

#define MAX_ACCOUNTS 1000

static int selectAccountNumberForUser(const User* user) {
    Account accounts[MAX_ACCOUNTS];
    int count = 0;
    loadAccounts(accounts, &count);

    int found = 0;

    printf("==== Your Accounts ====\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(accounts[i].ownerId, user->id) == 0) {
            printf("AccountNumber: %d, Type: %s, Balance: %d\n",
                accounts[i].accountNumber, accounts[i].accountType, accounts[i].balance);
            found = 1;
        }
    }

    if (!found) {
        printf("No accounts found.\n");
        return -1;
    }

    int accNo = getIntegerInput("Enter account number: ");
    return accNo;
}

void createAccount(const User* user) {
    Account accounts[MAX_ACCOUNTS];
    int count = 0;
    loadAccounts(accounts, &count);

    Account newAcc;
    int maxNo = 0;

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber > maxNo) {
            maxNo = accounts[i].accountNumber;
        }
    }

    newAcc.accountNumber = maxNo + 1;
    strcpy(newAcc.ownerId, user->id);

    printf("Account Type (e.g. SAVING, CHECKING): ");
    fgets(newAcc.accountType, 20, stdin);
    trim(newAcc.accountType);

    newAcc.balance = getIntegerInput("Initial balance: ");
    if (newAcc.balance < 0) newAcc.balance = 0;

    accounts[count++] = newAcc;
    saveAccounts(accounts, count);

    printf("Account created. Account Number: %d\n", newAcc.accountNumber);
}

void showAccountList(const User* user) {
    Account accounts[MAX_ACCOUNTS];
    int count = 0;
    loadAccounts(accounts, &count);

    int found = 0;
    printf("==== Account List for [%s] ====\n", user->id);
    for (int i = 0; i < count; i++) {
        if (strcmp(accounts[i].ownerId, user->id) == 0) {
            printf("AccountNumber: %d, Type: %s, Balance: %d\n",
                accounts[i].accountNumber, accounts[i].accountType, accounts[i].balance);
            found = 1;
        }
    }

    if (!found) {
        printf("No accounts.\n");
    }
}

void showBalance(const User* user) {
    int accNo = selectAccountNumberForUser(user);
    if (accNo == -1) return;

    Account accounts[MAX_ACCOUNTS];
    int count = 0;
    loadAccounts(accounts, &count);

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accNo && strcmp(accounts[i].ownerId, user->id) == 0) {
            printf("Balance of account %d: %d\n", accNo, accounts[i].balance);
            return;
        }
    }

    printf("Account not found.\n");
}

void deposit(const User* user) {
    int accNo = selectAccountNumberForUser(user);
    if (accNo == -1) return;

    int amount = getIntegerInput("Deposit amount: ");
    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    Account accounts[MAX_ACCOUNTS];
    int count = 0;
    loadAccounts(accounts, &count);

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accNo && strcmp(accounts[i].ownerId, user->id) == 0) {
            accounts[i].balance += amount;
            saveAccounts(accounts, count);

            addTransaction(accNo, "DEPOSIT", amount, accounts[i].balance);
        }
    }
}

void withdraw(const User* user) {
    int accNo = selectAccountNumberForUser(user);
    if (accNo == -1) return;

    int amount = getIntegerInput("Withdraw amount: ");
    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    Account accounts[MAX_ACCOUNTS];
    int count = 0;
    loadAccounts(accounts, &count);

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accNo &&
            strcmp(accounts[i].ownerId, user->id) == 0) {

            if (accounts[i].balance < amount) {
                printf("Not enough balance.\n");
                return;
            }

            accounts[i].balance -= amount;
            saveAccounts(accounts, count);

            addTransaction(accNo, "WITHDRAW", amount, accounts[i].balance);

            printf("Withdraw completed. New balance: %d\n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found.\n");
}
