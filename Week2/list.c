#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Function to create and return a new empty list.
List new_list() {
    List temp;
    temp.head = NULL;
    return temp;
}

// Function to print the contents of a list.
void print_list(List* self) {
    ListNodePtr current = self->head;
    while (current != NULL) {
        printf("%d", current->data);
        current = current->next;

        if (current != NULL)
            printf(", ");
    }
    printf("\n");
}

// Function to insert a new node with given data at the front of the list.
void insert_at_front(List* self, int data) {
    ListNodePtr new_node = malloc(sizeof * new_node);

    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = self->head;
    self->head = new_node;
}

// Function to insert a new node with given data in the list in ascending order.
void insert_in_order(List* self, int data) {
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;

    ListNodePtr new_node = malloc(sizeof * new_node);
    
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = NULL;

    while (current != NULL && current->data < data) {
        prev = current;
        current = current->next;
    }

    if (current == self->head) { // at front
        new_node->next = current;
        self->head = new_node;
    } else { // middle or end
        new_node->next = current;
        prev->next = new_node;
    }
}

// Function to delete the first occurrence of a node with given data from the list.
void delete_list(List* self, int data) {
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (prev == NULL) { // front of list
                self->head = current->next;
                free(current);
                current = self->head;
            } else { // middle of list
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// Function to free the memory allocated to a list and all its nodes.
void destroy_list(List* self) {
    ListNodePtr current = self->head;
    ListNodePtr next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    self->head = NULL;
}

// Function to test the linked list functions.
void list_test() {
    List my_list = new_list();

    // Testing insert_at_front
    printf("Testing insert_at_front...\n");
    insert_at_front(&my_list, 5);
    insert_at_front(&my_list, 3);
    insert_at_front(&my_list, 7);
    insert_at_front(&my_list, 2);
    insert_at_front(&my_list, 0);

    printf("Expected: 0, 2, 7, 3, 5\n");
    printf("Result: ");
    print_list(&my_list);

    // Destroy the list
    destroy_list(&my_list);

    // Testing insert_in_order
    printf("Testing insert_in_order...\n");
    my_list = new_list();
    insert_in_order(&my_list, 5);
    insert_in_order(&my_list, 3);
    insert_in_order(&my_list, 7);
    insert_in_order(&my_list, 2);
    insert_in_order(&my_list, 0);

    printf("Expected: 0, 2, 3, 5, 7\n");
    printf("Result: ");
    print_list(&my_list);

    // Destroy the list
    destroy_list(&my_list);

    // Testing delete_list
    printf("Testing delete_list...\n");
    my_list = new_list();
    insert_in_order(&my_list, 5);
    insert_in_order(&my_list, 3);
    insert_in_order(&my_list, 7);
    insert_in_order(&my_list, 2);
    insert_in_order(&my_list, 0);

    delete_list(&my_list, 5);
    delete_list(&my_list, 2);
    delete_list(&my_list, 7);

    printf("Expected: 0, 3\n");
    printf("Result: ");
    print_list(&my_list);

    // Destroy the list
    destroy_list(&my_list);
}

// Function for ad-hoc testing of the linked list using a simple console menu.
void list_adhoc_test() {
    List my_list = new_list();
    int quit = 0;

    while (!quit) {
        int option;
        printf("\nMenu:\n");
        printf("0 - Quit\n");
        printf("1 - Insert\n");
        printf("2 - Delete\n");
        printf("3 - Print\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 0:
                quit = 1;
                break;
            case 1:
                option_insert(&my_list);
                break;
            case 2:
                option_delete(&my_list);
                break;
            case 3:
                option_print(&my_list);
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }

    destroy_list(&my_list);
}

// Function to insert a new value at the front of the list (used in ad-hoc testing).
void option_insert(List* my_list) {
    int value;
    printf("Enter a value to insert: ");
    scanf("%d", &value);
    insert_at_front(my_list, value);
}

// Function to delete a value from the list (used in ad-hoc testing).
void option_delete(List* my_list) {
    int value;
    printf("Enter a value to delete: ");
    scanf("%d", &value);
    delete_list(my_list, value);
}

// Function to print the contents of the list (used in ad-hoc testing).
void option_print(List* my_list) {
    printf("List contents: ");
    print_list(my_list);
}

// Function to reverse the list and return a new list that is the reverse of the given list.
List reverse(List* self) {
    List reversed = new_list();
    ListNodePtr current = self->head;

    while (current != NULL) {
        insert_at_front(&reversed, current->data);
        current = current->next;
    }

    return reversed;
}

// Function to merge two ordered lists into a new ordered list.
List merge(List* list1, List* list2) {
    List merged = new_list();
    ListNodePtr ptr1 = list1->head;
    ListNodePtr ptr2 = list2->head;

    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1->data <= ptr2->data) {
            insert_in_order(&merged, ptr1->data);
            ptr1 = ptr1->next;
        } else {
            insert_in_order(&merged, ptr2->data);
            ptr2 = ptr2->next;
        }
    }

    while (ptr1 != NULL) {
        insert_in_order(&merged, ptr1->data);
        ptr1 = ptr1->next;
    }

    while (ptr2 != NULL) {
        insert_in_order(&merged, ptr2->data);
        ptr2 = ptr2->next;
    }

    return merged;
}
