#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

struct user {
    char name[50];
    char phn[20];
    char add[100];
    char acc[20];
    char pass[20];
    float balance;
} usr;

void file() {
    char filename[30];
    sprintf(filename, "%s.txt", usr.acc);  // Create a filename like "1234567890.txt"

    FILE *fp = fopen(filename, "w"); // Only declare FILE *fp here once
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    fprintf(fp, "%s\n", usr.name);
    fprintf(fp, "%s\n", usr.phn);
    fprintf(fp, "%s\n", usr.add);
    fprintf(fp, "%s\n", usr.acc);
    fprintf(fp, "%s\n", usr.pass);
    fprintf(fp, "%.2f\n", usr.balance);
    fclose(fp);
}

int filer(const char *acc_number) {
    char filename[30];
    sprintf(filename, "%s.txt", acc_number);  // Create the filename based on the entered account number

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Account with number %s does not exist.\n", acc_number);
        return 0;
    }
    fgets(usr.name, sizeof(usr.name), fp);
    usr.name[strcspn(usr.name, "\n")] = 0;

    fgets(usr.phn, sizeof(usr.phn), fp);
    usr.phn[strcspn(usr.phn, "\n")] = 0;

    fgets(usr.add, sizeof(usr.add), fp);
    usr.add[strcspn(usr.add, "\n")] = 0;

    fgets(usr.acc, sizeof(usr.acc), fp);
    usr.acc[strcspn(usr.acc, "\n")] = 0;

    fgets(usr.pass, sizeof(usr.pass), fp);
    usr.pass[strcspn(usr.pass, "\n")] = 0;

    fscanf(fp, "%f", &usr.balance);
    fclose(fp);
    return 1;
}

void details() {
    system(CLEAR); // Clear the screen before displaying details
    printf("Name: %s\n", usr.name);
    printf("Phone: %s\n", usr.phn);
    printf("Address: %s\n", usr.add);
    printf("Account: %s\n", usr.acc);
    printf("Balance: %.2f\n", usr.balance);
}

void withdraw() {
    float amount;
    system(CLEAR); // Clear the screen before withdrawing
    printf("Enter amount to withdraw: ");
    if (scanf("%f", &amount) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }
    if (!isfinite(amount) || amount <= 0) {
    printf("Invalid amount!\n");
    }
    else if (amount > usr.balance) {
        printf("Insufficient balance!\n");
    }
    else {
        usr.balance -= amount;
        printf("Withdrawal successful!");
        printf("\nNew balance: %.2f\n", usr.balance);
    }
}

void credit() {
    float amount;
    system(CLEAR); // Clear the screen before depositing
    printf("Enter amount to deposit: ");
    if (scanf("%f", &amount) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }
    if (!isfinite(amount) || amount <= 0){
    printf("Please enter a valid amount!\n");
    }
    else {
        usr.balance += amount;
        printf("Deposit successful!");
        printf("\nNew balance: %.2f\n", usr.balance);
    }
}

void updatebalance() {
    char filename[30];
    sprintf(filename, "%s.txt", usr.acc);  // Create the filename using account number

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    fprintf(fp, "%s\n", usr.name);
    fprintf(fp, "%s\n", usr.phn);
    fprintf(fp, "%s\n", usr.add);
    fprintf(fp, "%s\n", usr.acc);
    fprintf(fp, "%s\n", usr.pass);
    fprintf(fp, "%.2f\n", usr.balance);
    fclose(fp);
}

int main() {
    int choice, choose;
    char acc1[20], pass1[20];
    srand(time(NULL));

    while (1) {  // Add a loop for main menu
        system(CLEAR); // Clear the screen before showing the main menu
        printf("\t\t1. Register an account.");
        printf("\n\t\t2. Login to existing account.\n");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                system(CLEAR); // Clear the screen before account registration
                printf("\t\tRegister an account\n");
                printf("\t\t___________________\n\n");
                printf("\t\tEnter details of user\n");

                printf("\n\nEnter your name: ");
                fgets(usr.name, sizeof(usr.name), stdin);
                usr.name[strcspn(usr.name, "\n")] = 0;

                printf("Enter your phone number: ");
                fgets(usr.phn, sizeof(usr.phn), stdin);
                usr.phn[strcspn(usr.phn, "\n")] = 0;

                printf("Enter your address: ");
                fgets(usr.add, sizeof(usr.add), stdin);
                usr.add[strcspn(usr.add, "\n")] = 0;

                int random_acc;
                char filename[30];
                FILE *check;

                do {
                    random_acc = rand() % 900000000 + 100000000;

                    sprintf(usr.acc, "%d", random_acc);
                    sprintf(filename, "%s.txt", usr.acc);

                    check = fopen(filename, "r");

                    if (check != NULL) {
                        fclose(check);
                    }

                } while (check != NULL);

                printf("Your generated account number is: %s\n", usr.acc);

                printf("Enter your password: ");
                fgets(usr.pass, sizeof(usr.pass), stdin);
                usr.pass[strcspn(usr.pass, "\n")] = 0;

                usr.balance = 0;
                file();

                printf("\n\t\tAccount created successfully...\n");
                break;

            case 2:
                system(CLEAR); // Clear the screen before login
                printf("Enter your account number: ");
                fgets(acc1, sizeof(acc1), stdin);
                acc1[strcspn(acc1, "\n")] = 0;
                if (strlen(acc1) != 9 || strspn(acc1, "0123456789") != 9) {
                    printf("Invalid account number!\n");
                    break;
                }

                if (filer(acc1) == 0) {
                    printf("Account not found.\n");
                    continue;
                }

                printf("\nEnter your password: ");
                fgets(pass1, sizeof(pass1), stdin);
                pass1[strcspn(pass1, "\n")] = 0;

                if (strcmp(pass1, usr.pass) == 0) {
                    do {
                        system(CLEAR); // Clear the screen before showing the user menu
                        printf("\n\t\tWelcome %s\n", usr.name);
                        printf("\n1. See your details \t\t2. Withdraw money \n3. Deposit money \t\t4. Check balance\n5. Exit");
                        printf("\nEnter choice: ");
                        if (scanf("%d", &choose) != 1) {
                            printf("Invalid input!\n");
                            while (getchar() != '\n');
                            choose = 0;
                        }
                        else {
                            getchar();
                        }

                        switch (choose) {
                            case 1:
                                details();
                                break;

                            case 2:
                                withdraw();
                                updatebalance(); // Update the balance in the file
                                break;

                            case 3:
                                credit();
                                updatebalance(); // Update the balance in the file
                                break;

                            case 4:
                                system(CLEAR); // Clear the screen before checking balance
                                printf("\n\t\tCheck balance\n");
                                printf("\n\t\t_____________\n");
                                printf("Your current balance is %.2f\n", usr.balance);
                                break;

                            case 5:
                                printf("Exiting...\n");
                                break;

                            default:
                                printf("Invalid choice.\n");
                        }

                        if (choose != 5) {
                            printf("\nPress Enter to continue...");
                            getchar();  // Pause to let the user see the result before clearing
                        }

                    } while (choose != 5);
                } else {
                    printf("Incorrect password.\n");
                }
                break;

            default:
                printf("Invalid input.\n");
        }

        printf("\nPress Enter to return to the main menu...");
        getchar(); // Pause before returning to the main menu
    }

    return 0;
}
