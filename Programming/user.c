#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "user.h"
#include "file_manager.h"
#include "util.h"
#include "config.h"

#define MAX_USERS 100

int registerUser() {
    User users[MAX_USERS];
    int count = 0;
    loadUsers(users, &count);

    User newUser;

    printf("Enter ID: ");
    fgets(newUser.id, 30, stdin); trim(newUser.id);

    // ID check
    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].id, newUser.id) == 0) {
            printf("ID already exists.\n");
            return 0;
        }
    }

    printf("Enter Password: ");
    fgets(newUser.password, 30, stdin); trim(newUser.password);

    printf("Enter Name: ");
    fgets(newUser.name, 50, stdin); trim(newUser.name);

    printf("Enter Phone: ");
    fgets(newUser.phone, 20, stdin); trim(newUser.phone);

    users[count++] = newUser;
    saveUsers(users, count);

    printf("Registration successful.\n");
    return 1;
}

int login(User* loggedInUser) {
    User users[MAX_USERS];
    int count = 0;
    loadUsers(users, &count);

    char id[30], pw[30];

    printf("ID: ");
    fgets(id, 30, stdin); trim(id);

    printf("PW: ");
    fgets(pw, 30, stdin); trim(pw);

    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].id, id) == 0 && strcmp(users[i].password, pw) == 0) {
            *loggedInUser = users[i];
            return 1;
        }
    }

    printf("Login failed.\n");
    return 0;
}

void changePassword(User* user) {
    char newPw[30];

    printf("New Password: ");
    fgets(newPw, 30, stdin); trim(newPw);

    strcpy(user->password, newPw);

    User users[MAX_USERS];
    int count = 0;
    loadUsers(users, &count);

    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].id, user->id) == 0) {
            users[i] = *user;
            break;
        }
    }

    saveUsers(users, count);
    printf("Password changed.\n");
}

void updateUserInfo(User* user) {
    printf("New Phone: ");
    fgets(user->phone, 20, stdin); trim(user->phone);

    User users[MAX_USERS];
    int count = 0;
    loadUsers(users, &count);

    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].id, user->id) == 0) {
            users[i] = *user;
            break;
        }
    }

    saveUsers(users, count);
    printf("User info updated.\n");
}
    