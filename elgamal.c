#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "eg.h"  
#include "eg_params.h"

//gcc -std=c11 -o eg_program elgamal.c eg.c eg_params.c -lm

void print_array(const char *label, const uint64_t arr[], size_t size) {
    printf("%s:\n", label);
    for (size_t i = 0; i < size; i++) {
        printf("%016llx ", arr[i]);
        if ((i + 1) % 4 == 0)  
            printf("\n");
    }
    printf("\n");
}

int main() {
    uint64_t a[20] = {0}; // Initialize with zeros
    uint64_t aux[20] = {0}; // Initialize with zeros

    print_array("Initial Private Key X", x, 20);
    print_array("Prime number", p, 20);
    print_array("Generator G", g, 20);

    // Perform ElGamal key generation
    printf("Performing ElGamal key generation...\n");
    if (!expoAndMod(y, g, x, p)) {
        printf("ElGamal key generation failed.\n");
        return 1;  // Exit if encryption fails.
    }
    print_array("Public Key Y", y, 20);
    

    printf("Performing ElGamal message encryption...\n");
    printf("\n");
    print_array("Message to encrypt", m, 20);
    print_array("Random integer, private key of the sender", k, 20);
    

    printf("Calculating a = g^k mod p...\n");
    if (!expoAndMod(a, g, k, p)) {
        printf("Calculation of a failed.\n");
        return 1;
    }
    print_array("Value of a", a, 20);

    printf("Calculating b = m * (y^k mod p) mod p...\n");
    if (!mexpoAndMod(b, y, k, p, m)) {
        printf("Modular multiplication failed.\n");
        return 1;
    }
    print_array("Encrypted message part b", b, 20);

    // Output encrypted message parts
    print_array("Encrypted message part a", a, 20);
    print_array("Encrypted message part b", b, 20);

    
    printf("Calculating s = a^x mod p...\n");
    if (!expoAndMod(s, a, x, p)) {
        printf("Calculation of a failed.\n");
        return 1;
    }
    print_array("Value of s", a, 20);


    uint64_t p_minus_2[20] = {0}; // Initialize with zeros
    
    for (int i = 0; i < 20; i++) {
        p_minus_2[i] = p[i];
    }
    p_minus_2[0] -= 2;

    printf("Calculating s^-1 mod p...\n");
    uint64_t x_inv[20] = {0}; // To store the inverse of x
    if (!expoAndMod(x_inv, s, p_minus_2, p)) {
        printf("Calculation of x^-1 mod p failed.\n");
        return 1;
    }
    print_array("Value of x^-1 mod p", x_inv, 20);

    printf("Decrypted Message (m):\n");
    if (!mexpoAndMod(res, s, p_minus_2, p, b)) {
        printf("Modular multiplication failed.\n");
        return 1;
    }
    print_array("Decrypted message", res, 20);

    return 0;
}
