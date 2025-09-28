#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// declaring functions
void oct_to_bin(const char* oct, char* out);
void oct_to_hex(const char* oct, char* out);
void hex_to_bin(const char* hex, char* out);
void to_sign_magnitude(int n, char* out);
void to_ones_complement(int n, char* out);
void to_twos_complement(int n, char* out);

int main() {
    const char* filename = "../x64/Debug/a2_test.txt"; // the test file
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open %s\n", filename);
        return 1;
    }
    char line[256];
    char result[65];
    int test_number = 1;
    int pass_count = 0;
    int total_tests = 0;

    while (fgets(line, sizeof(line), fp)) {
        // Skip empty lines and comment lines
        if (line[0] == '\n' || line[0] == '#') continue;

        char command[50], extra[50];
        char input[50];
        int scanned = sscanf(line, "%s %s %s", command, input, extra);
        if (scanned < 2) continue;

        // Test oct_to_bin
        if (strcmp(command, "oct_to_bin") == 0 && scanned >= 3) {
            oct_to_bin(input, result);
            int passed = strcmp(result, extra) == 0;
            if (passed) pass_count++;
            printf("Test %d: Oct_to_Bin-Conversion result (%s)-> Expected Answer - \"%s\", Answer: %s [%s]\n",
                test_number++, input, extra, result, passed ? "PASS" : "FAIL");
            total_tests++;
            printf("\n");  // blank line to separate sections
        }
        // Test oct_to_hex
        if (strcmp(command, "oct_to_hex") == 0 && scanned >= 3) {
            oct_to_hex(input, result);
            int passed = strcmp(result, extra) == 0;
            if (passed) pass_count++;
            printf("Test %d: Oct_to_Hex-Conversion result (%s)-> Expected Answer - \"%s\", Answer: %s [%s]\n",
                test_number++, input, extra, result, passed ? "PASS" : "FAIL");
            total_tests++;
            printf("\n");  // blank line to separate sections
        }

        // Test hex_to_bin
        if (strcmp(command, "hex_to_bin") == 0 && scanned >= 3) {
            hex_to_bin(input, result);
            int passed = strcmp(result, extra) == 0;
            if (passed) pass_count++;
            printf("Test %d: Hex_to_Bin-Conversion result (%s)-> Expected Answer - \"%s\", Answer: %s [%s]\n",
                test_number++, input, extra, result, passed ? "PASS" : "FAIL");
            total_tests++;
            printf("\n");  // blank line to separate sections
        }
        // Test to_sign_magnitude
        if (strcmp(command, "to_sign_magnitude") == 0 && scanned >= 3) {
            int n = atoi(input); 
            to_sign_magnitude(n, result);
            int passed = strcmp(result, extra) == 0;
            if (passed) pass_count++;
            printf("Test %d: To_Sign_Magnitude-Conversion result (%d)-> Expected Answer - \"%s\", Answer: %s [%s]\n",
                test_number++, n, extra, result, passed ? "PASS" : "FAIL");
            total_tests++;
            printf("\n");  // blank line to separate sections
        }
        // Test to_ones_complement
        if (strcmp(command, "to_ones_complement") == 0 && scanned >= 3) {
            int n = atoi(input);
            to_ones_complement(n, result);
            int passed = strcmp(result, extra) == 0;
            if (passed) pass_count++;
            printf("Test %d: To_Ones_Complement-Conversion result (%d)-> Expected Answer - \"%s\", Answer: %s [%s]\n",
                test_number++, n, extra, result, passed ? "PASS" : "FAIL");
            total_tests++;
            printf("\n");  // blank line to separate sections
        }
        // Test to_twos_complement
        if (strcmp(command, "to_twos_complement") == 0 && scanned >= 3) {
            int n = atoi(input);
            to_twos_complement(n, result);
            int passed = strcmp(result, extra) == 0;
            if (passed) pass_count++;
            printf("Test %d: To_Twos_Complement-Conversion result (%d)-> Expected Answer - \"%s\", Answer: %s [%s]\n",
                test_number++, n, extra, result, passed ? "PASS" : "FAIL");
            total_tests++;
            printf("\n");  // blank line to separate sections
        }
        
    }
    printf("\nSummary: %d/%d tests passed\n", pass_count, total_tests);
    fclose(fp);
    return 0;
}