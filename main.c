// gcc -O0 -fno-stack-protector -no-pie -o puhosos main.c
// FbL3gt7wCpnhC2AB1bwcylbfLeYRrp3x

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void win() {
    char *flag = getenv("FLAG");
    if (flag) {
        printf("[+] Flag: %s\n", flag);
    } else {
        printf("[-] No flag(\n");
    }
    exit(0);
}

void check_password(const char *input) {
    unsigned char expected[32] = {
        0x56, 0x73, 0x5e, 0x20, 0x73, 0x61, 0x21, 0x60, 
        0x5b, 0x69, 0x74, 0x73, 0x5f, 0x2f, 0x5f, 0x5d, 
        0x11, 0x43, 0x55, 0x40, 0x5d, 0x49, 0x44, 0x41, 
        0x64, 0x4c, 0x73, 0x79, 0x5e, 0x5d, 0x1d, 0x57
    };

    for (int i = 0; i < 32; i++) {
        if (input[i] == '\0' || input[i] == '\n') {
            printf("[-] Incorrect puhosos-password\n");
            exit(1);
        }

        unsigned char calc = (unsigned char)input[i] ^ (i + 0x10);
        
        if (calc != expected[i]) {
            printf("[-] Incorrect puhosos-password\n");
            exit(1);
        }
    }

    if (input[32] != '\n' && input[32] != '\0') {
        printf("[-] Incorrect puhosos-password\n");
        exit(1);
    }
}

void update_puhosos() {
    struct Puhosos {
        char puhosos_name[32];
        int is_chief;
    } puhosos;

    puhosos.is_chief = 0;

    printf("Enter length of puhosos-name (<=32): ");

    int input_size;
    scanf("%d", &input_size);

    if (input_size > 32) {
        printf("[-] Too long puhosos-name\n");
        exit(1);
    }

    printf("Enter puhosos-name: ");
    while (getchar() != '\n'); // Очистка буфера от символа '\n' после scanf

    uint8_t final_size = (uint8_t)input_size;

    read(0, puhosos.puhosos_name, final_size);

    printf("[i] Updated puhosos: %s\n", puhosos.puhosos_name);

    if (puhosos.is_chief) {
        printf("[!] You are a chief-puhosos!\n");
    } else {
        printf("[-] You are NOT a chief-puhosos!\n");
        exit(1);
    }
}

int main() {
    setup();
    
    char password[64];

    printf("=== PUHOSOS UPDATE PANEL ===\n");
    printf("Enter puhosos-password: ");

    if (fgets(password, sizeof(password), stdin) == NULL) {
        exit(1);
    }

    check_password(password);

    printf("[+] Correct puhosos-password\nUpdating\n");
    update_puhosos();
    
    return 0;
}