#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Made by devilz or bypasser0x2 :)

#define ELF_HEADER_SIZE 64 


void corrupt_elf_header(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    // Nullify magic bytes slightly 
    fseek(file, 1, SEEK_SET);
    fputc(0x00, file);  // Corrupt ELF magic bytes

    // Nullify section header table offset
    fseek(file, 0x28, SEEK_SET);
    for (int i = 0; i < 8; i++) {
        fputc(0x00, file);  
    }

    fseek(file, 0x30, SEEK_SET);
    for (int i = 0; i < 2; i++) {
        fputc(0x00, file);  // Corrupt number of section headers
    }

    fclose(file);
    printf("ELF header & section table successfully corrupted.\n");
}

void overwrite_section_headers(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0x40, SEEK_SET); 
    for (int i = 0; i < 256; i++) {
        fputc(0x00, file);  // Overwriting a large chunk of section headers
    }

    fclose(file);
    printf("[*]Section headers wiped.\n");
}

void remove_symbol_table(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0x50, SEEK_SET);  // Overwrite potential .symtab section
    for (int i = 0; i < 256; i++) {
        fputc(0x00, file);
    }

    fclose(file);
    printf("[*]Symbol table removed.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <elf_binary>\n", argv[0]);
        return 1;
    }

    printf("[*]Processing ELF: %s\n", argv[1]);
    corrupt_elf_header(argv[1]);
    overwrite_section_headers(argv[1]);
    remove_symbol_table(argv[1]);

    printf("[*]Binary modification complete! Harder to reverse now.\n");
    printf("[*]Thankx for using our tool :), kindly don't forget to give it a star ");
    return 0;
}
                                      
