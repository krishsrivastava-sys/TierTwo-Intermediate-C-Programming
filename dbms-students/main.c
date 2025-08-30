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
struct Student
{
    int id;
    char name[100];
    int age;
};

int main()
{
    FILE *fp;
    fp = fopen("data.txt", "r+");
    if (fp == NULL)
    {
        printf("[ERROR] Error opening the file.");
        exit(1);
    }
    printf("Welcome to the Students Database Management System:\n1. Create a new Student Entry.\n2.Edit an existing student Entry.\n3. Delete an existing student entry.\n");
    printf("Enter your choice: ");
    int choice;
    int capacity = 2; // Start with 2 for default;
    int count = 0;
    scanf("%d", &choice);
    struct Student *students = NULL; // Creating the default struct.
    students = malloc(capacity * sizeof(struct Student));
    if (students == NULL)
    {
        printf("[ERROR] Memory Allocation Failed.");
        exit(1);
    }
    if (choice == 1)
    {
        // Student Entry Creation
        while (fscanf(fp, "%d %99s %d", &students[count].id, students[count].name, &students[count].age) == 3)
        {
            // If all 3 Were successfully read.
            // Do something.
            count++;
        }
        // Now we even got all of the entries inside our struct.
        // All we need to do is create a new entry and overwrite it.
        int id = count + 1;
        char name_[100];
        printf("Enter the name of the student: ");
        scanf(" %[^\n]", name_);
        printf("Enter the age of the student: ");
        int age;
        scanf("%d", &age);
        // We have the name, age and id, now we need to store it in the struct.
        students[count].id = id;
        strcpy(students[count].name, name_);
        students[count].age = age;
        count++; // To show that we have a new entry.
        // We are now done with the modification of the struct, now we need to overwrite this new struct over whatever was previously stored inside of the file.

        freopen("data.txt", "w", fp);
        for (int i = 0; i < count; i++)
        {
            fprintf(fp, "%d %s %d\n", students[i].id, students[i].name, students[i].age);
        }
        fclose(fp);
        free(students);
        printf("Student added successfully!\n");
    }
    else if (choice == 2)
    {
        // Student Entry Modification
        // First, read all existing entries
        while (fscanf(fp, "%d %99s %d", &students[count].id, students[count].name, &students[count].age) == 3)
        {
            count++;
            if (count >= capacity)
            {
                capacity *= 2;
                students = realloc(students, capacity * sizeof(struct Student));
                if (students == NULL)
                {
                    printf("[ERROR] Memory allocation failed.\n");
                    exit(1);
                }
            }
        }

        // Ask which student to edit
        int edit_id;
        printf("Enter the ID of the student to edit: ");
        scanf("%d", &edit_id);

        int found = 0;
        for (int i = 0; i < count; i++)
        {
            if (students[i].id == edit_id)
            {
                found = 1;
                printf("Editing student: %s, Age: %d\n", students[i].name, students[i].age);
                printf("Enter new name (or type same name): ");
                scanf(" %[^\n]", students[i].name);
                printf("Enter new age: ");
                scanf("%d", &students[i].age);
                break;
            }
        }

        if (!found)
        {
            printf("[ERROR] Student with ID %d not found.\n", edit_id);
        }
        else
        {
            freopen("data.txt", "w", fp);
            for (int i = 0; i < count; i++)
            {
                fprintf(fp, "%d %s %d\n", students[i].id, students[i].name, students[i].age);
            }
            printf("Student updated successfully!\n");
        }

        fclose(fp);
        free(students);
    }
    else if (choice == 3)
    {
        // student entry deletion.
        // Read all entries first
        while (fscanf(fp, "%d %99s %d", &students[count].id, students[count].name, &students[count].age) == 3)
        {
            count++;
            if (count >= capacity)
            {
                capacity *= 2;
                students = realloc(students, capacity * sizeof(struct Student));
                if (students == NULL)
                {
                    printf("[ERROR] Memory allocation failed.\n");
                    exit(1);
                }
            }
        }

        int del_id;
        printf("Enter the ID of the student to delete: ");
        scanf("%d", &del_id);

        int found = 0;
        for (int i = 0; i < count; i++)
        {
            if (students[i].id == del_id)
            {
                found = 1;
                // Shift all later entries up
                for (int j = i; j < count - 1; j++)
                {
                    students[j] = students[j + 1];
                }
                count--;
                break;
            }
        }

        if (!found)
        {
            printf("[ERROR] Student with ID %d not found.\n", del_id);
        }
        else
        {
            freopen("data.txt", "w", fp);
            for (int i = 0; i < count; i++)
            {
                fprintf(fp, "%d %s %d\n", students[i].id, students[i].name, students[i].age);
            }
            printf("Student deleted successfully!\n");
        }

        fclose(fp);
        free(students);
    }
    else
    {
        printf("[ERROR] Invalid choice.\n");
    }
}