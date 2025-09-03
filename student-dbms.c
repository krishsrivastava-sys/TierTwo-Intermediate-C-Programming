// A Simple database management system for storing student data inside of a file.
// I used VS code's format button and now it looks like so different ;-;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * The Standard I/O Library includes the file management operations
 * - FILE *fp = fopen("<file.name>", "mode")
 * -
 */
struct Student {
    int id;
    char name[100];
    int age;
};

int main() {
    int choice;
    int capacity = 2; // Start with 2 for default
    int count = 0;
    struct Student *students = malloc(capacity * sizeof(struct Student));
    if (students == NULL) {
        printf("[ERROR] Memory Allocation Failed.\n");
        exit(1);
    }

    printf("Welcome to the Students Database Management System:\n1. Create a new Student Entry.\n2.Edit an existing student Entry.\n3. Delete an existing student entry.\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Student Entry Creation
        int id;
        char name_[100];
        int age;

        // Determine new ID by reading the last student ID in the file
        FILE *read_fp = fopen("data.txt", "r");
        if (read_fp != NULL) {
            int temp_id, temp_age;
            char temp_name[100];
            id = 0; // default starting ID
            while (fscanf(read_fp, "%d \"%99[^\"]\" %d", &temp_id, temp_name, &temp_age) == 3) {
                id = temp_id; // last valid ID
            }
            fclose(read_fp);
        } else {
            id = 0; // first student
        }
        id++; // new student ID

        printf("Enter the name of the student: ");
        scanf(" %99[^\n]", name_);  // safe scan
        printf("Enter the age of the student: ");
        scanf("%d", &age);

        // Append directly to file
        FILE *fp = fopen("data.txt", "a"); // append mode
        if (fp == NULL) {
            printf("[ERROR] Could not open file for appending.\n");
            free(students);
            exit(1);
        }
        fprintf(fp, "%d \"%s\" %d\n", id, name_, age); // <-- quoted format
        fclose(fp);

        printf("Student added successfully!\n");
    }
    else if (choice == 2 || choice == 3) {
        // Both edit and delete require reading entire file into memory first
        FILE *fp = fopen("data.txt", "r");
        if (fp == NULL) {
            printf("[ERROR] Could not open file for reading.\n");
            free(students);
            exit(1);
        }

        // Read all existing entries into memory
        count = 0; // reset count
        while (fscanf(fp, "%d \"%99[^\"]\" %d", &students[count].id, students[count].name, &students[count].age) == 3) {
            count++;
            if (count >= capacity) {
                capacity *= 2;
                struct Student *temp = realloc(students, capacity * sizeof(struct Student));
                if (temp == NULL) {
                    printf("[ERROR] Memory allocation failed.\n");
                    fclose(fp);
                    free(students);
                    exit(1);
                }
                students = temp;
            }
        }
        fclose(fp);

        if (choice == 2) {
            // Student Entry Modification
            int edit_id;
            printf("Enter the ID of the student to edit: ");
            scanf("%d", &edit_id);

            int found = 0;
            for (int i = 0; i < count; i++) {
                if (students[i].id == edit_id) {
                    found = 1;
                    printf("Editing student: %s, Age: %d\n", students[i].name, students[i].age);
                    printf("Enter new name (or type same name): ");
                    scanf(" %99[^\n]", students[i].name);
                    printf("Enter new age: ");
                    scanf("%d", &students[i].age);
                    break;
                }
            }

            if (!found) {
                printf("[ERROR] Student with ID %d not found.\n", edit_id);
            } else {
                fp = fopen("data.txt", "w"); // truncate file
                if (fp == NULL) {
                    printf("[ERROR] Could not open file for writing.\n");
                    free(students);
                    exit(1);
                }
                for (int i = 0; i < count; i++) {
                    fprintf(fp, "%d \"%s\" %d\n", students[i].id, students[i].name, students[i].age);
                }
                fclose(fp);
                printf("Student updated successfully!\n");
            }
        }
        else if (choice == 3) {
            // Student Entry Deletion
            int del_id;
            printf("Enter the ID of the student to delete: ");
            scanf("%d", &del_id);

            int found = 0;
            for (int i = 0; i < count; i++) {
                if (students[i].id == del_id) {
                    found = 1;
                    // Shift all later entries up
                    for (int j = i; j < count - 1; j++) {
                        students[j] = students[j + 1];
                    }
                    count--;
                    break;
                }
            }

            if (!found) {
                printf("[ERROR] Student with ID %d not found.\n", del_id);
            } else {
                fp = fopen("data.txt", "w");
                if (fp == NULL) {
                    printf("[ERROR] Could not open file for writing.\n");
                    free(students);
                    exit(1);
                }
                for (int i = 0; i < count; i++) {
                    fprintf(fp, "%d \"%s\" %d\n", students[i].id, students[i].name, students[i].age);
                }
                fclose(fp);
                printf("Student deleted successfully!\n");
            }
        }

        free(students);
    }
    else {
        printf("[ERROR] Invalid choice.\n");
        free(students);
    }

    return 0;
}
