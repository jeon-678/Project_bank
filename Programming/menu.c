#include <stdio.h>
#include "menu.h"
#include "user.h"
#include "account.h"
#include "transaction.h"
#include "util.h"

void showAccountMenu(User* user);

void showMainMenu() {
    while (1) {
        int choice;
        User loggedInUser;

        printf("\n==== Main Menu ====\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("0. Exit\n");

        choice = getIntegerInput("Select: ");

        switch (choice) {
        case 1:
            registerUser();
            break;

        case 2:
            if (login(&loggedInUser)) {
                printf("Login success. Welcome, %s\n", loggedInUser.id);
                showUserMenu(&loggedInUser);
            }
            break;

        case 0:
            printf("Bye.\n");
            return;

        default:
            printf("Invalid menu.\n");
            break;
        }
    }
}

void showUserMenu(User* user) {
    while (1) {
        int choice;

        printf("\n==== User Menu (%s) ====\n", user->id);
        printf("1. Account Menu\n");
        printf("2. Change Password\n");
        printf("3. Update User Info\n");
        printf("0. Logout\n");

        choice = getIntegerInput("Select: ");

        switch (choice) {
        case 1:
            showAccountMenu(user);
            break;

        case 2:
            changePassword(user);
            break;

        case 3:
            updateUserInfo(user);
            break;

        case 0:
            printf("Logout.\n");
            return;

        default:
            printf("Invalid menu.\n");
            break;
        }
    }
}

void showAccountMenu(User* user) {
    while (1) {
        int choice;

        printf("\n==== Account Menu ====\n");
        printf("1. Create Account\n");
        printf("2. Show Account List\n");
        printf("3. Show Balance\n");
        printf("4. Deposit\n");
        printf("5. Withdraw\n");
        printf("6. Show Transaction History\n");
        printf("0. Back\n");

        choice = getIntegerInput("Select: ");

        switch (choice) {
        case 1:
            createAccount(user);
            break;

        case 2:
            showAccountList(user);
            break;

        case 3:
            showBalance(user);
            break;

        case 4:
            deposit(user);
            break;

        case 5:
            withdraw(user);
            break;

        case 6: {
            int accNo = getIntegerInput("Enter account number: ");
            showTransaction(accNo);
            break;
        }

        case 0:
            return;

        default:
            printf("Invalid menu.\n");
            break;
        }
    }
}
