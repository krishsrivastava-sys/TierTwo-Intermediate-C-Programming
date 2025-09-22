// ⚡ CheckZ @ CheckZ Labs | Crafted 2025
/* BANK MANAGEMENT SYSTEM IN C PROGRAMMING LANGUAGE */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME "database.txt"

// Function to authenticate user
int authenticate(int clogin, int* status, bool* admin, char* user_id) {
    FILE *file;
    file = fopen(FILENAME, "a+");
    if(file == NULL) {
        perror("[ERROR] Error opening database file");
        return 1;
    }

    if(clogin == 1) { // Create account
        char id[11];
        char pass[21];
        char line[1024];
        printf("Enter the account id: ");
        scanf(" %10s", id);

        rewind(file);
        while (fgets(line, sizeof(line), file)) {
            char *token = strtok(line, ",");
            if(token && strcmp(id, token) == 0) {
                printf("Error! That ID Already Exists!\n");
                fclose(file);
                return 1;
            }
        }

        printf("Enter the account password: ");
        scanf(" %20s", pass);

        char choice;
        bool is_admin = false;
        printf("Is this an admin account? (y/n): ");
        scanf(" %c", &choice);
        if(choice == 'y' || choice == 'Y') is_admin = true;

        fseek(file, 0, SEEK_END);
        fprintf(file, "%s,%s,%s,0\n", id, pass, is_admin ? "true" : "false");
        fflush(file);
        printf("[i] Account Registration Successful.\n");

        *status = 1;
        *admin = is_admin;
        strcpy(user_id, id);
    } else { // Login
        char lognkey[11];
        char line[1024];
        char prompass[21];

        printf("[*] Enter your login: ");
        scanf(" %10s", lognkey);

        rewind(file);
        bool found = false;
        while(fgets(line, sizeof(line), file)) {
            char *id = strtok(line, ",");
            char *pass = strtok(NULL, ",");
            char *adm  = strtok(NULL, ",");
            char *bal  = strtok(NULL, ",\n");
            if(!id || !pass || !adm) continue;

            if(strcmp(lognkey, id) == 0) {
                found = true;
                printf("[>>] Enter the password: ");
                scanf(" %20s", prompass);

                if(strcmp(prompass, pass) != 0) {
                    printf("[E] Incorrect Password\n");
                    fclose(file);
                    return 1;
                }

                *status = 1;
                *admin = (strcmp(adm, "true") == 0);
                strcpy(user_id, id);

                printf("[i] Logged in as %s.\n", *admin ? "Admin" : "User");
                break;
            }
        }

        if(!found) {
            printf("[E] User not found!\n");
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Utility to get account info
bool get_account(const char* id, char* pass, bool* admin, double* balance) {
    FILE *file = fopen(FILENAME, "r");
    if(!file) return false;

    char line[1024];
    while(fgets(line, sizeof(line), file)) {
        char *t_id = strtok(line, ",");
        char *t_pass = strtok(NULL, ",");
        char *t_admin = strtok(NULL, ",");
        char *t_bal  = strtok(NULL, ",\n");
        if(!t_id || !t_pass || !t_admin || !t_bal) continue;

        if(strcmp(id, t_id) == 0) {
            strcpy(pass, t_pass);
            *admin = (strcmp(t_admin, "true") == 0);
            *balance = atof(t_bal);
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

// Utility to update account balance
bool update_balance(const char* id, double new_balance) {
    FILE *file = fopen(FILENAME, "r");
    if(!file) return false;

    char line[1024];
    char tmp_filename[] = "tempdb.txt";
    FILE *tmp = fopen(tmp_filename, "w");
    if(!tmp) {
        fclose(file);
        return false;
    }

    while(fgets(line, sizeof(line), file)) {
        char *t_id = strtok(line, ",");
        char *t_pass = strtok(NULL, ",");
        char *t_admin = strtok(NULL, ",");
        char *t_bal  = strtok(NULL, ",\n");
        if(!t_id || !t_pass || !t_admin || !t_bal) continue;

        if(strcmp(id, t_id) == 0)
            fprintf(tmp, "%s,%s,%s,%.2f\n", t_id, t_pass, t_admin, new_balance);
        else
            fprintf(tmp, "%s,%s,%s,%s\n", t_id, t_pass, t_admin, t_bal);
    }

    fclose(file);
    fclose(tmp);
    remove(FILENAME);
    rename(tmp_filename, FILENAME);
    return true;
}

int main() {
    int clogin;
    char user_id[11];
    printf("[i] Welcome to the B.M.S Console Dashboard!\n");
    printf(">> 1. Create an account.\n>> 2. Login with your account.\nEnter your choice> ");
    scanf("%d", &clogin);

    if(clogin != 1 && clogin != 2) {
        printf("[!!] Invalid input.\n");
        return 1;
    }

    int status = 0;
    bool admin = false;
    if(authenticate(clogin, &status, &admin, user_id) != 0) return 1;

    if(!status) {
        printf("[-] Authentication failed.\n");
        return 1;
    }

    char pass[21];
    double balance = 0;
    bool is_admin;

    // Main loop: keep user in dashboard until they logout
    while(1) {
        printf("\n[i] Dashboard Options:\n");
        printf("1. Load Your Account\n2. Send Money\n3. Request Money\n");
        if(admin) {
            printf("4. Load Someone's Account\n5. Add Money\n6. Modify Account\n7. Delete Account\n");
        }
        printf("0. Logout\n");
        printf("Enter your choice> ");
        int choice;
        scanf("%d", &choice);

        if(choice == 0) {
            printf("[i] Logging out...\n");
            break;
        }

        switch(choice) {
            case 1: // Load your account
                if(get_account(user_id, pass, &is_admin, &balance))
                    printf("Account: %s | Balance: %.2f\n", user_id, balance);
                else
                    printf("[E] Error loading your account.\n");
                break;
            case 2: // Send Money
                {
                    char target[11];
                    double amt;
                    printf("Enter recipient ID: ");
                    scanf(" %10s", target);
                    printf("Enter amount: ");
                    scanf("%lf", &amt);

                    if(get_account(user_id, pass, &is_admin, &balance) && balance >= amt) {
                        double target_balance;
                        if(get_account(target, pass, &is_admin, &target_balance)) {
                            update_balance(user_id, balance - amt);
                            update_balance(target, target_balance + amt);
                            printf("[i] Transfer successful.\n");
                        } else {
                            printf("[E] Recipient not found.\n");
                        }
                    } else {
                        printf("[E] Insufficient balance.\n");
                    }
                }
                break;
            case 3:
                printf("[i] Money request feature is under development.\n");
                break;
            case 4: // Admin only
                if(admin) {
                    char target[11];
                    printf("Enter account to load: ");
                    scanf(" %10s", target);
                    if(get_account(target, pass, &is_admin, &balance))
                        printf("Account: %s | Balance: %.2f | Admin: %s\n", target, balance, is_admin ? "true" : "false");
                    else
                        printf("[E] Account not found.\n");
                } else printf("[!] Admin only.\n");
                break;
            case 5: // Admin: Add Money
                if(admin) {
                    double amt;
                    printf("Enter amount to add: ");
                    scanf("%lf", &amt);
                    if(get_account(user_id, pass, &is_admin, &balance)) {
                        update_balance(user_id, balance + amt);
                        printf("[i] Money added.\n");
                    }
                } else printf("[!] Admin only.\n");
                break;
            case 6: // Admin: Modify account
                if(admin) {
                    char target[11], newpass[21];
                    printf("Enter account ID to modify: ");
                    scanf(" %10s", target);
                    printf("Enter new password: ");
                    scanf(" %20s", newpass);

                    FILE *file = fopen(FILENAME, "r");
                    FILE *tmp = fopen("tempdb.txt", "w");
                    char line[1024];
                    while(fgets(line, sizeof(line), file)) {
                        char *t_id = strtok(line, ",");
                        char *t_pass = strtok(NULL, ",");
                        char *t_admin = strtok(NULL, ",");
                        char *t_bal  = strtok(NULL, ",\n");
                        if(strcmp(t_id, target) == 0)
                            fprintf(tmp, "%s,%s,%s,%s\n", t_id, newpass, t_admin, t_bal);
                        else
                            fprintf(tmp, "%s,%s,%s,%s\n", t_id, t_pass, t_admin, t_bal);
                    }
                    fclose(file);
                    fclose(tmp);
                    remove(FILENAME);
                    rename("tempdb.txt", FILENAME);
                    printf("[i] Account modified.\n");
                } else printf("[!] Admin only.\n");
                break;
            case 7: // Admin: Delete account
                if(admin) {
                    char target[11];
                    printf("Enter account ID to delete: ");
                    scanf(" %10s", target);

                    FILE *file = fopen(FILENAME, "r");
                    FILE *tmp = fopen("tempdb.txt", "w");
                    char line[1024];
                    while(fgets(line, sizeof(line), file)) {
                        char *t_id = strtok(line, ",");
                        if(strcmp(t_id, target) != 0) fprintf(tmp, "%s", line);
                    }
                    fclose(file);
                    fclose(tmp);
                    remove(FILENAME);
                    rename("tempdb.txt", FILENAME);
                    printf("[i] Account deleted.\n");
                } else printf("[!] Admin only.\n");
                break;
            default:
                printf("[!] Invalid choice.\n");
                break;
        }
    }

    return 0;
}