#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "user.h"
#include "account.h"

void loadUsers(User users[], int* count);
void saveUsers(const User users[], int count);

void loadAccounts(Account accounts[], int* count);
void saveAccounts(const Account accounts[], int count);

void appendHistory(int accountNumber, const char* line);

#endif
