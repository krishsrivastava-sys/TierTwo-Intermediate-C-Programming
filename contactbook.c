// I have quite a few days of holidays
// So we will binge code today!!!
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME "data.dat"


struct Contact {
    char number[11];//Because phone numbers are unique
    char name[101];// Hundred characters long name is enough ig.
};

int main() {
    FILE *file;
    int capacity = 1;// Start with 1 contact for default.
    struct Contact *contacts = malloc(capacity * sizeof(struct Contact));
    if(contacts == NULL) {
        // We failed to create a struct, we return error.
        printf("{E} Memory Allocation Failed, Please find the root cause.");
    } else {
        // Creation of contacts was successful, we run this code then.
        printf("[Welcome to the contacts book]\n1. Create a new contact\n2. Delete an Existing contact\n3. Get the list of contacts.");
/*
We can think of adding these higher level features in the future.
- Search: Giving a single part of the name sorts out the string and gives the most appropriate Result.
*/
        int choice;
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        if(choice == 1) {
            // NEW CONTACT CREATION
            char num[11];
            char name_[101];
            printf("Enter the name: ");
            scanf(" %100[^\n]", name_);
            printf("Enter the phone number: ");
            scanf(" %10[^\n]", num);
            for (int i = 0; num[i] != '\0'; i++) {
                if(!isdigit(num[i])) {
                    printf("[E] Please provide us with a valid phone number.");
                    return 0;
                }
            }
            strcpy(contacts->name, name_);
            strcpy(contacts->number, num);
            file = fopen(FILENAME, "ab");
            if(!file) {
                printf("{E} Error opening the desired file.");
                return 1;
            } else {
                fwrite(&contacts[0], sizeof(struct Contact), 1, file);
                fclose(file);
                printf("[+] Contact saved to file!\n");
            }
        } else if(choice == 2) {
            // PREVIOUS CONTACT DELETION
            char delnum[11];
            printf("[i] Enter the number of the contact you wish to delete:");
            scanf(" %10[^\n]", delnum);
            for (int i = 0; delnum[i] != '\0'; i++) {
                if(!isdigit(delnum[i])) {
                    printf("[E] Please provide us with a valid phone number.");
                    return 0;
                }
            }
            file = fopen(FILENAME, "rb");
            if(!file) {
                // Error Opening a file, we catch and throw the error.
                printf("{E} Error Opening the file, please look for the problems!");
                return 1;
            } else {
                bool done = false;
                int count = 0; // number of contacts actually read
                while (done == false) {
                    // While the status is still incomplete, we read the file, and store the data.
                    // We already have default capacity as 1, but we still give an extra.
                    if (count >= capacity) {
                        capacity *= 2;
                        struct Contact *temp = realloc(contacts, capacity * sizeof(struct Contact));
                        if (!temp) {
                            printf("{E} Realloc failed!");
                            free(contacts);
                            fclose(file);
                            return 1;
                        }
                        contacts = temp;
                    }
                    if (fread(&contacts[count], sizeof(struct Contact), 1, file) != 1) {
                        done = true; // no more data
                    } else {
                        count++;
                    }
                }
                fclose(file);

                // Now delete the contact
                int found = 0;
                for (int i = 0; i < count; i++) {
                    if (strcmp(contacts[i].number, delnum) == 0) {
                        found = 1;
                        for (int j = i; j < count - 1; j++) {
                            contacts[j] = contacts[j + 1];
                        }
                        count--;
                        break;
                    }
                }

                if (found) {
                    file = fopen(FILENAME, "wb");
                    if (!file) {
                        printf("{E} Could not reopen file for writing.");
                        free(contacts);
                        return 1;
                    }
                    fwrite(contacts, sizeof(struct Contact), count, file);
                    fclose(file);
                    printf("[+] Contact deleted successfully.\n");
                } else {
                    printf("[E] Contact not found.\n");
                }
            }
        } else if(choice == 3) {
            // GETTING THE LIST OF CONTACTS
            file = fopen(FILENAME, "rb");
            if(!file) {
                // Error Opening a file, we catch and throw the error.
                printf("{E} Error Opening the file, please look for the problems!");
                return 1;
            } else {
                // File open, we read the data.
                struct Contact temp;
                printf("[Contact List]\n");
                while (fread(&temp, sizeof(struct Contact), 1, file)) {
                    printf("Name: %s | Number: %s\n", temp.name, temp.number);
                }
                fclose(file);
            }
        } else {
            printf("{E} Please return us with a valid input choice!");
        }
    }
    return 0;
}
