#ifndef USER_H
#define USER_H

#include "config.h"

// 사용자 구조체
typedef struct {
    char id[30];
    char password[30];
    char name[50];
    char phone[20];
} User;

// 함수 선언
int registerUser();
int login(User* loggedInUser);
void changePassword(User* user);
void updateUserInfo(User* user);

#endif // USER_H