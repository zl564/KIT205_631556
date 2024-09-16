#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* String;

void quicksort(String* a, int first, int last) {
    if (first < last) {
        // Pivot is the last element  faf 
        String pivot = a[last];
        int i = first;
        int j = last - 1;

        // Partitioning
        while (i <= j) {
            while (i < last && strcmp(a[i], pivot) <= 0) {
                i++;
            }
            while (j >= first && strcmp(a[j], pivot) > 0) {
                j--;
            }
            if (i < j) {
                // Swap a[i] and a[j]
                String temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
        // Swap a[i] and a[last] (pivot)
        String temp = a[i];
        a[i] = a[last];
        a[last] = temp;

        // Recursively apply quicksort to the partitions
        quicksort(a, first, j);
        quicksort(a, i + 1, last);
    }
}

int main() {
    int n;

    // Read the number of strings
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Failed to read number of strings.\n");
        return 1;
    }
    getchar(); // To consume the newline character left by scanf

    // Allocate memory for the array of strings
    String* strings = malloc(n * sizeof(String));
    if (strings == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Buffer to hold each string temporarily
    char buffer[100];  // Buffer size of 100 to accommodate up to 99 characters plus the null terminator

    // Read strings from input
    for (int i = 0; i < n; i++) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Failed to read string.\n");
            // Free previously allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return 1;
        }

        // Remove newline character from the buffer if present
        buffer[strcspn(buffer, "\n")] = '\0';

        // Allocate memory for the string and copy it
        strings[i] = malloc(strlen(buffer) + 1);
        if (strings[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            // Free previously allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return 1;
        }
        strcpy(strings[i], buffer);
    }

    // Call quicksort to sort the array of strings
    quicksort(strings, 0, n - 1);

    // Print the strings
    printf("\nSorted strings:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", strings[i]);
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}