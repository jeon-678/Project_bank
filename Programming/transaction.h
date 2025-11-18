#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct {
    char date[20];
    char type[10];
    int amount;
    int balance;
    int accountNumber;
} Transaction;

void addTransaction(int accountNumber, const char* type, int amount, int balance);
void showTransaction(int accountNumber);

#endif
