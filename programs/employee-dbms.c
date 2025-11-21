// This program uses linked lists to create an employee DBMS.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    char id[21];
    char name[101];
    int age;
    int salary;
    char department[101];
    struct Employee *next;
};

/*
Write a program to create an employee database including:
ID, name, age, salary, department.
Department is determined by the UID
*/

// Returns the department name as a string based on UID prefix
void getDepartment(const char *uid, char *departmentOut) {
    // Extract department code from UID (positions 2–4, 0-indexed)
    char departmentCode[4];
    strncpy(departmentCode, uid + 2, 3);
    departmentCode[3] = '\0';

    // Match department code
    if (strcmp(departmentCode, "BCS") == 0) {
        strcpy(departmentOut, "Department of Computer Science and Engineering");
    } else if (strcmp(departmentCode, "BAC") == 0) {
        strcpy(departmentOut, "Department of Art and Cultural Affairs");
    } else if (strcmp(departmentCode, "BME") == 0) {
        strcpy(departmentOut, "Department of Mechanical Engineering");
    } else if (strcmp(departmentCode, "BEE") == 0) {
        strcpy(departmentOut, "Department of Electrical Engineering");
    } else if (strcmp(departmentCode, "BBA") == 0) {
        strcpy(departmentOut, "Department of Business Administration");
    } else {
        strcpy(departmentOut, "Unknown Department");
    }
}

// Creates and inserts a new employee node into the linked list
int createEmployee(struct Employee **emp, const char *id, const char *name, int age, int salary) {
    struct Employee *NewEmp = malloc(sizeof(struct Employee));
    if (!NewEmp) return 0; // failed allocation
    strcpy(NewEmp->id, id);
    strcpy(NewEmp->name, name);
    NewEmp->age = age;
    NewEmp->salary = salary;
    // Get department based on UID
    getDepartment(id, NewEmp->department);
    // Insert at the beginning
    NewEmp->next = *emp;
    *emp = NewEmp;
    return 1; // success
}

int deleteEmployee(struct Employee **emp, const char *id) {
    if (*emp == NULL) return 0;
    struct Employee *temp = *emp;
    struct Employee *prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            // Match found
            if (prev == NULL) {
                *emp = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            return 1; // success
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
}

// Display all employees
void displayEmployees(struct Employee *emp) {
    while(emp != NULL) {
        printf("\nID: %s", emp->id);
        printf("\nName: %s", emp->name);
        printf("\nAge: %d", emp->age);
        printf("\nSalary: %d", emp->salary);
        printf("\nDepartment: %s\n", emp->department);
        emp = emp->next;
    }
}

void menu() {
    struct Employee *emp = NULL;
    printf("[i] Welcome to the Employee DBMS - Choose what you wish to do?\n1. Create Employee\n2. Delete Employee\n3. Display Employees\nType anything else to exit: ");
    int choicee;
    scanf("%d", &choicee);
    getchar(); // clear leftover newline from input buffer

    if(choicee == 1) {
        char choice = 'y';
        while (choice == 'y' || choice == 'Y') {
            char uid[21];
            char name[101];
            int age, salary;
            printf("\nEnter the UID of the Employee: ");
            scanf(" %20[^\n]", uid);
            getchar();
            printf("Enter the name of the Employee: ");
            scanf(" %100[^\n]", name);
            getchar();
            printf("Enter the age of the Employee: ");
            scanf("%d", &age);
            printf("Enter the salary of the Employee: ");
            scanf("%d", &salary);
            getchar();
            if (createEmployee(&emp, uid, name, age, salary)) {
                printf("Employee added successfully.\n");
            } else {
                printf("Failed to add employee.\n");
                break;
            }
            printf("Do you wish to add another employee? (y/n): ");
            scanf(" %c", &choice);
        }
    } else if(choicee == 2) {
        char uid[21];
        printf("Enter the UID of the Employee to delete: ");
        scanf(" %20[^\n]", uid);
        getchar();
        int del = deleteEmployee(&emp, uid);
        if(del == 1) {
            printf("Successfully Deleted the employee.");
        } else {
            printf("Unable to delete the employee.");
        }
        char done;
        printf("\nDo you wish to continue? (y/n): ");
        scanf(" %c", &done);
        if(done == 'y' || done == 'Y') {
            menu();
        } else {
            exit(0);
        }
    } else if(choicee == 3) {
         displayEmployees(emp);
         menu();
    } else {
        exit(0);
    }
}

int main() {
    menu();
    return 0;
}
