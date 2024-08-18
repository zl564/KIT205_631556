#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

// Function prototypes
void f1(long n);
void f2(long n);
void f3(long n);
void f4(long n);
void f5(long n);
void f6(long n);
void f7(long n);

int main() {
    int quit = 0;

    while (!quit) {
        int option;
        printf("\nMenu:\n");
        printf("0 - Quit\n");
        printf("1 - Test insert_at_front\n");
        printf("2 - Test insert_in_order\n");
        printf("3 - Test delete_list\n");
        printf("4 - Test reverse\n");
        printf("5 - Test merge\n");
        printf("6 - Test list_test\n");
        printf("7 - Test list_adhoc_test\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        if (option != 0) {
            long n;
            printf("Enter a value for n: ");
            scanf("%ld", &n);
            clock_t start = clock(); // Start timer

            // Call the appropriate function based on option
            switch (option) {
                case 1:
                    f1(n);
                    break;
                case 2:
                    f2(n);
                    break;
                case 3:
                    f3(n);
                    break;
                case 4:
                    f4(n);
                    break;
                case 5:
                    f5(n);
                    break;
                case 6:
                    f6(n);
                    break;
                case 7:
                    f7(n);
                    break;
                default:
                    printf("Invalid option. Please try again.\n");
                    break;
            }

            // Stop timer and calculate elapsed time
            clock_t diff = clock() - start;
            long msec = diff * 1000 / CLOCKS_PER_SEC;
            printf("Operation took %ld milliseconds\n\n", msec);
        } else {
            quit = 1; // Exit the loop
        }
    }

    return 0;
}

// Function implementations for timing tests

// Example implementation for f1 (insert_at_front)
void f1(long n) {
    List list = new_list();
    for (long i = 0; i < n; i++) {
        insert_at_front(&list, (int)i);
    }
    destroy_list(&list);
}

// Example implementation for f2 (insert_in_order)
void f2(long n) {
    List list = new_list();
    for (long i = 0; i < n; i++) {
        insert_in_order(&list, (int)i);
    }
    destroy_list(&list);
}

// Example implementation for f3 (delete_list)
void f3(long n) {
    List list = new_list();
    for (long i = 0; i < n; i++) {
        insert_in_order(&list, (int)i);
    }
    for (long i = 0; i < n; i++) {
        delete_list(&list, (int)i);
    }
    destroy_list(&list);
}

// Example implementation for f4 (reverse)
void f4(long n) {
    List list = new_list();
    for (long i = 0; i < n; i++) {
        insert_in_order(&list, (int)i);
    }
    List reversed = reverse(&list);
    destroy_list(&list);
    destroy_list(&reversed);
}

// Example implementation for f5 (merge)
void f5(long n) {
    List list1 = new_list();
    List list2 = new_list();
    for (long i = 0; i < n; i++) {
        insert_in_order(&list1, (int)i);
        insert_in_order(&list2, (int)(i + n)); // Different range for the second list
    }
    List merged = merge(&list1, &list2);
    destroy_list(&list1);
    destroy_list(&list2);
    destroy_list(&merged);
}

// Example implementation for f6 (list_test)
void f6(long n) {
    for (long i = 0; i < n; i++) {
        List my_list = new_list();
        insert_in_order(&my_list, (int)i);
        delete_list(&my_list, (int)i);
        destroy_list(&my_list);
    }
}

// Example implementation for f7 (list_adhoc_test)
void f7(long n) {
    List my_list = new_list();
    for (long i = 0; i < n; i++) {
        insert_in_order(&my_list, (int)i);
    }
    destroy_list(&my_list);
}
