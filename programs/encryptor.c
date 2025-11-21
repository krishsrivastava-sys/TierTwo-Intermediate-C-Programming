//@INFO -> This program is highly inefficient! I was learning and hence made this!


// File encryptor/decryptor (XOR method).
#include <stdio.h>
// The standard I/O Library.
#include <stdlib.h>
// The Standard Utils Library.
#include <string.h>
// The Library with all string functions.
#include <stdbool.h>

int main() {
    FILE *file;
    printf("[i] Welcome to the XOR File Encryptor!\n");
    char fname[30];
    printf("Enter the name of the file: ");
    scanf("%[^\n]", fname);

    file = fopen(fname, "r+"); // Open for reading and writing, don't truncate
    if(file == NULL) {
        perror("Error opening file.");
        return 1; // The Error Code, We caught it.
    }

    printf("[i] The program requires a key to perform encryption operations!\n--> Please Enter a key: ");
    char key[101]; // An 100 characters key at max must be enough ig.
    scanf(" %100[^\n]", key);

    int keylen = strlen(key); // The indexing is settled.
    if(keylen == 0) {
        printf("{E} Error! Please enter a valid key input!");
        fclose(file);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    int remainder = file_size % keylen;
    bool solve_extra = false;
    if(remainder != 0) {
        solve_extra = true;
    }

    // We calculate the number of cycles.
    int cyclecount = file_size / keylen;
    if (file_size % keylen != 0) cyclecount++;

    // Now we know the number of cycles we have to run the key to, we now run the cycles.
    /* What we have ready in hand:
    - The Number of Cycles we need to turn for the key to pass through the whole file.
    - The length of the key.
    - The Length of the file.
    */
    long index = 0; // Starting of the file
    for(int i = 0; i < cyclecount; i++) { // First Cycle
        for(int j = 0; j < keylen; j++) {
            if(index >= file_size) break; // Prevent going past EOF

            fseek(file, index, SEEK_SET);
            int ch = fgetc(file); // Use int to safely check EOF
            if(ch == EOF) break;

            char bchar = ch ^ key[j];
            fseek(file, index, SEEK_SET); // Move back to overwrite
            fputc(bchar, file);

            index++;
        }
    }
    printf("[INFO] The File Encryption was successful.");
    fclose(file);
    return 0;
}

// ⚡ CheckZ @ CheckZ Labs | Crafted 2025