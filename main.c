// gcc -O0 -fno-stack-protector -no-pie -o puhosos main.c

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
    puts("win");
    char *flag = getenv("FLAG");
    if (flag) {
        printf("[+] Flag: %s\n", flag);
    } else {
        printf("[-] No flag(\n");
    }
    exit(0);
}

int check_password(const char *input) {
    const char *expected = "SuperPuhosos";
    int expected_len = strlen(expected);

    if (strncmp(input, expected, expected_len) == 0) {
        if (input[expected_len] == '\n' || input[expected_len] == '\0') {
            return 1;
        }
    }
    
    return 0;
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
    while (getchar() != '\n');

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
    char password[32];

    printf("=== PUHOSOS UPDATE PANEL ===\n");
    printf("Enter puhosos-password: ");

    if (fgets(password, sizeof(password), stdin) == NULL) {
        exit(1);
    }

    if (!check_password(password)) {
        printf("[-] Incorrect puhosos-password\n");
        exit(1);
    }

    printf("[+] Correct puhosos-password\nUpdating\n");

    update_puhosos();
    
    return 0;
}