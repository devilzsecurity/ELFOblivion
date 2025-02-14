#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

// Made by devilz or bypasser0x2 :)

#define ELF_HEADER_SIZE 64 

void corrupt_elf_header(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 1, SEEK_SET);
    fputc(0x00, file);
    
    fseek(file, 0x28, SEEK_SET);
    for (int i = 0; i < 8; i++) {
        fputc(0x00, file);
    }
    
    fseek(file, 0x30, SEEK_SET);
    for (int i = 0; i < 2; i++) {
        fputc(0x00, file);
    }

    fclose(file);
    printf("[+] ELF header & section table successfully corrupted.\n");
}

void overwrite_section_headers(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0x40, SEEK_SET);
    for (int i = 0; i < 256; i++) {
        fputc(0x00, file);
    }

    fclose(file);
    printf("[+] Section headers wiped.\n");
}

void remove_symbol_table(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0x50, SEEK_SET);
    for (int i = 0; i < 256; i++) {
        fputc(0x00, file);
    }

    fclose(file);
    printf("[+] Symbol table removed.\n");
}

void self_destruct(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    srand(time(NULL));
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < 1024; i++) {
        fputc(rand() % 256, file);
    }
    
    fclose(file);
    unlink(file_path);
    printf("[!] Binary successfully self-destructed.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <elf_binary> <mode>\n", argv[0]);
        printf("Modes: \n");
        printf("1 - Basic ELF corruption\n");
        printf("2 - Advanced (Self-Destruction)\n");
        return 1;
    }

    int mode = atoi(argv[2]);

    printf("[*] Processing ELF: %s\n", argv[1]);
    
    if (mode == 1) {
        corrupt_elf_header(argv[1]);
        overwrite_section_headers(argv[1]);
        remove_symbol_table(argv[1]);
        printf("[+] Binary modification complete! Harder to reverse now.\n");
    } else if (mode == 2) {
        printf("[+] Applying self-destruction techniques...\n");
        corrupt_elf_header(argv[1]);
        overwrite_section_headers(argv[1]);
        remove_symbol_table(argv[1]);
        self_destruct(argv[1]);
        printf("[+] Binary completely destroyed.\n");
    } else {
        printf("[!] Invalid mode selected.\n");
        return 1;
    }

    return 0;
}
