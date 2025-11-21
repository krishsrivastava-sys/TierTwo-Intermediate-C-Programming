// File encryptor/decryptor (XOR method).
#include <stdio.h>
// The standard I/O Library.
#include <stdlib.h>
// The Standard Utils Library.
#include <string.h>
// The Library with all string functions.
#include <stdbool.h>

int main() {
    char fname[200];
    printf("[i] Welcome to the FEAD(File Encryption and Decryption) Tool!\n");
    printf("Please enter the name of the file you wish to Encrypt/Decrypt: ");
    scanf("%199[^\n]", fname);

    int index = 0;
    FILE *file = fopen(fname, "rb+");
    if(file == NULL) {
        printf("[E] The file didn't open? ERROR!!!!!\n");// ive gone mad sigh...
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char key[] = "aZ9bQ2xVtL4mNpR7sYwK1eC6jH8uDfG0iJrB3oS5lXvWqTzA9nM2yE7kP4hU1cO8";
    int key_index = 0;

    while(index < file_size) {
        if(key_index >= strlen(key)) {  // Fix: use strlen to ignore null terminator
            key_index = 0;
        }

        fseek(file, index, SEEK_SET);
        int ch = fgetc(file); // Use int to safely check EOF
        if(ch == EOF) break;

        char bchar = ch ^ key[key_index];
        fseek(file, index, SEEK_SET); // Move back to overwrite
        fputc(bchar, file);

        index++;
        key_index++;
    }

    fclose(file);
    printf("[i] Operation complete!\n");
    return 0;
}
// ⚡ CheckZ @ CheckZ Labs | Crafted 2025
