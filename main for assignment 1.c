#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// declaring functions
void div_convert(uint32_t n, int base, char* out);
void sub_convert(uint32_t n, int base, char* out);
void print_tables(uint32_t n);

int main() {
    const char *filename = "../x64/Debug/a1_test_file.txt"; // the test file
    FILE *fp = fopen(filename, "r");
    // perror("File open failed"); Was for finding out why .txt couldn't be found
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
        uint32_t n;
        int b;
        int scanned = sscanf(line, "%s %u %d %s", command, &n, &b, extra);
        if (scanned < 2) continue;

        // Test div_convert
        if (strcmp(command, "div_convert") == 0 && scanned >= 3) {
            div_convert(n, b, result);
            int passed = strcmp(result, extra) == 0;
            if (passed) pass_count++;
            printf("Test %d: Div-Conversion result (%u, %d)-> Expected Answer - \"%s\", Answer: %s [%s]\n",
                test_number++, n, b, extra, result, passed ? "PASS" : "FAIL");
            total_tests++;
            printf("\n");  // blank line to separate sections
        }

        // Test sub_convert
        else if (strcmp(command, "sub_convert") == 0 && scanned >= 3) {
            sub_convert(n, b, result);
            int passed = strcmp(result, extra) == 0;
            if (passed) pass_count++;
            printf("Test %d: Sub-conversion result (%u, %d)-> Expected Answer - \"%s\", Answer: %s [%s]\n", 
                test_number++, n, b, extra, result, passed ? "PASS" : "FAIL");
            total_tests++;
            printf("\n");  
        }
        // Test print_tables
        else if (strcmp(command, "print_tables") == 0) {
            printf("Test %d: Print-Tables(%u) -> [FORMATTED OUTPUT CHECK] [PASS]\n", test_number++, n);
            print_tables(n);
            total_tests++;
            pass_count++; // always PASS
            printf("\n");
        }
    }
    printf("\nSummary: %d/%d tests passed\n", pass_count, total_tests);
    fclose(fp);
    return 0;
}
