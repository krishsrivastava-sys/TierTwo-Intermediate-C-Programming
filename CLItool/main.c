#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    int id;
    char name[100];
    char class[4]; // max XII
    char grade;// A, B etc.
} Student;

void pull_entries(FILE *file) {
    printf("[i] Pulling all student entries...\n");

    Student student;
    int scount = 1;

    rewind(file); // Important: start from the beginning

    while(fread(&student, sizeof(Student), 1, file) == 1) {
        printf("[Student #%d]\n", scount);
        printf("[Name: %s]\n", student.name);
        printf("[ID: %d]\n", student.id);
        printf("[Class: %s]\n", student.class);
        printf("[Grade: %c]\n", student.grade);
        printf("-------------------------\n");
        scount++;
    }
    if(scount == 1) printf("[i] No student records found.\n");
}

int std_entry(FILE *file) {
    printf("[i] Creating a new student entry...\n");
    Student student;
    printf("[-->] Enter the student id: ");
    scanf("%d", &student.id);
    printf("[-->] Enter the student name: ");
    scanf(" %99[^\n]", student.name);
    printf("[-->] Enter the student class: ");
    scanf(" %3s", student.class);
    printf("[-->] Enter the student grade: ");
    scanf(" %c", &student.grade);// The student grade, %c is required because not an array.
    printf("[i] Creating the student entry...\n");
    size_t written = fwrite(&student, sizeof(student), 1, file);
    if(written != 1) { // The file data was not written?
        // We Error Handle.
        perror("[ERROR] The file data appendation was not successful!\n");
        return 1;
    } else {
        printf("[i] The file data was written successfully.\n");
    }
    return 0;
}

int fetch_entry(FILE *file) {
    printf("[i] Enter the student id to fetch: ");
    int fid;
    Student student;
    scanf("%d", &fid);
    bool found = false;
    printf("[i] Searching the database...\n");// Linear Search
    rewind(file);
    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if(student.id == fid) {
            // if the student was found, stop the code execution.
            found = true;
            break;
        }
    }
    if(found == true) {
        printf("[i] Search was successfull, student id found in the database. Pulling the records...\n");
        printf("[STUDENT STATUS]\n[ID: %d]\n[Name: %s]\n[Class: %s]\n[Grade: %c]\n", student.id, student.name, student.class, student.grade);
    } else {
        printf("[!] Search was unsuccessfull, student id was not found to be recorded in the database!");
        return 0;
    }
    return 0;
}


FILE *del_entry(FILE *file) {
    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        perror("[ERROR] Unable to create the temporary file. Terminating the process.");
        return file; // return original so main doesn’t break
    }
    printf("[i] Please enter the student id: ");
    int did;
    scanf("%d", &did);
    Student student;
    bool found = false;
    rewind(file);
    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.id == did) {
            found = true;
            continue;
        }
        fwrite(&student, sizeof(Student), 1, temp);
    }

    fclose(file);
    fclose(temp);

    remove("records.dat");
    rename("temp.dat", "records.dat");

    if(found) {
        printf("[i] Record with ID %d deleted successfully.\n", did);
    } else {
        printf("[!] Record with ID %d not found.\n", did);
    }

    file = fopen("records.dat", "ab+");
    if (file == NULL) {
        perror("[ERROR] Unable to reopen updated file!");
        exit(1);
    }
    return file;
}


int main() {
    int choice;
    char onechoice;
    FILE *file;

    file = fopen("records.dat", "ab+");// Append Binary creates the file if it doesn't exists.
    if(file == NULL) {
        perror("[ERROR] Unable to open file. Terminating the process.");
        return 1;
    }
    int cmdone = 0;
    do {
        printf("[i] Welcome to the student management system. (Enter anything else to exit.)\n1. Create a new student entry.\n2. Fetch a student entry.\n3. Delete a student entry.\n4. View all student entries.\nEnter Your choice: ");
        scanf("%d", &choice);
        if(choice == 1) {
            int fin = 0;
            do {
                std_entry(file);
                printf("Create a new student entry? (y/n):");
                scanf(" %c", &onechoice);
                if(tolower(onechoice) == 'n') fin = 1;
            } while(fin == 0);
        } else if(choice == 2) {
            int fin = 0;
            do {
                fetch_entry(file);
                printf("Fetch another student's entry? (y/n):");
                scanf(" %c", &onechoice);
                if(tolower(onechoice) == 'n') fin = 1;
            } while(fin == 0);
        } else if(choice == 3) {
            // Deleting a student entry...
            file = del_entry(file);
        } else if(choice == 4) {
            // Pulling all student entries...
            pull_entries(file);
        } else {
            perror("[i] Program execution Terminated.");
            cmdone = 1;
            break;
        }
    } while (cmdone != 1);
    fclose(file);
    return 0;
}