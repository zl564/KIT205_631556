// This header file contains declarations for a singly linked list data structure implementation in C.
#pragma once

// Definition of a singly linked list node struct with an integer data field and a pointer to the next node.
typedef struct listNode {
    int data;
    struct listNode* next;
} *ListNodePtr; // Alias for pointer to struct listNode

// Definition of a singly linked list struct with a pointer to the head node.
typedef struct list {
    ListNodePtr head;
} List;

// Function to create and return a new empty list.
List new_list();

// Function to print the contents of a list.
void print_list(List* self);

// Function to insert a new node with given data at the front of the list.
void insert_at_front(List* self, int data);

// Function to insert a new node with given data in the list in ascending order.
void insert_in_order(List* self, int data);

// Function to delete the first occurrence of a node with given data from the list.
void delete_list(List* self, int data);

// Function to free the memory allocated to a list and all its nodes.
void destroy_list(List* self);

// Function to test the linked list functions.
void list_test();

// Function for ad-hoc testing of the linked list using a simple console menu.
void list_adhoc_test();

// Function to reverse the list and return a new list that is the reverse of the given list.
List reverse(List* self);

// Function to merge two ordered lists into a new ordered list.
List merge(List* list1, List* list2);
