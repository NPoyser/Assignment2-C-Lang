#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // for abs
#include <ctype.h>  // for toupper

void oct_to_bin(const char *oct, char *out) {
    int pos = 0; // position in output buffer

    while (*oct) {
        int octal_digit = *oct - '0'; // '0'-'7' ? 0-7

        // Build 3-bit binary
        out[pos++] = (octal_digit >> 2) & 1 ? '1' : '0';
        out[pos++] = (octal_digit >> 1) & 1 ? '1' : '0';
        out[pos++] = (octal_digit >> 0) & 1 ? '1' : '0';

        oct++;
    }

    out[pos] = '\0'; // null-terminate
}

void oct_to_hex(const char *oct, char *out) {
    char bin[256];
    oct_to_bin(oct, bin);

    int len = 0;
    while (bin[len]) len++;

    // Pad to multiple of 4 bits
    int pad = (4 - (len % 4)) % 4;
    int pos = 0;
    for (int i = 0; i < pad; i++) out[pos++] = '0';

    for (int i = 0; i < len; i++) out[pos++] = bin[i];
    out[pos] = '\0';

    // convert 4-bit groups to hex
    char hex[100];
    int hex_pos = 0;
    for (int i = 0; i < pos; i += 4) {
        int value = 0;
        value |= (out[i] - '0') << 3;
        value |= (out[i + 1] - '0') << 2;
        value |= (out[i + 2] - '0') << 1;
        value |= (out[i + 3] - '0') << 0;

        if (value < 10) hex[hex_pos++] = '0' + value;
        else hex[hex_pos++] = 'A' + (value - 10);
    }
    hex[hex_pos] = '\0';

    // remove leading zeros
    int start = 0;
    while (hex[start] == '0' && hex[start + 1] != '\0') start++;

    // copys final hex string to out
    int k = 0;
    while ((out[k] = hex[start + k]) != '\0') k++;
}

void hex_to_bin(const char *hex, char *out) {
    int pos = 0;

    while (*hex) {
        char c = toupper(*hex);
        int value;

        if (c >= '0' && c <= '9') value = c - '0';
        else if (c >= 'A' && c <= 'F') value = c - 'A' + 10;
        else {
            printf("Invalid hex: %c\n", c);
            hex++;
            continue;
        }

        out[pos++] = (value >> 3) & 1 ? '1' : '0';
        out[pos++] = (value >> 2) & 1 ? '1' : '0';
        out[pos++] = (value >> 1) & 1 ? '1' : '0';
        out[pos++] = (value >> 0) & 1 ? '1' : '0';

        hex++;
    }

    out[pos] = '\0';
}

void to_sign_magnitude(int n, char *out) {
    unsigned int value = n >= 0 ? n : abs(n);

    if (n < 0) value |= 1U << 31; // set sign bit

    for (int i = 31; i >= 0; i--)
        out[31 - i] = (value & (1U << i)) ? '1' : '0';

    out[32] = '\0';
}

void to_ones_complement(int n, char* out) {
    unsigned int value = n >= 0 ? n : ~abs(n);

    for (int i = 31; i >= 0; i--)
        out[31 - i] = (value & (1U << i)) ? '1' : '0';

    out[32] = '\0';
}

void to_twos_complement(int n, char *out) {
    unsigned int value = n >= 0 ? n : (~abs(n) + 1);

    for (int i = 31; i >= 0; i--)
        out[31 - i] = (value & (1U << i)) ? '1' : '0';

    out[32] = '\0';
}