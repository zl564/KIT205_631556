#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

// Create an empty BST
BST new_bst() {
    BST temp;
    temp.root = NULL;
    return temp;
}

// Recursive function to find a value and return the containing node
BSTNodePtr find_bst_node(BSTNodePtr self, int n) {
    if (self == NULL || (n == self->data_item)) { /* Not present, or here */
        return self;
    } else if (n < self->data_item) {
        return find_bst_node(self->left, n);
    } else {
        return find_bst_node(self->right, n);
    }
}

// Find a value in the tree and return the node
BSTNodePtr find_bst(BST* self, int n) {
    return find_bst_node(self->root, n);
}

// Recursive function to insert a value
BSTNodePtr insert_bst_node(BSTNodePtr self, int n) {
    if (self == NULL) { /* Found where to put it */
        self = malloc(sizeof *self);
        self->data_item = n;
        self->left = self->right = NULL;
    } else if (n < self->data_item) {
        self->left = insert_bst_node(self->left, n);
    } else if (n > self->data_item) {
        self->right = insert_bst_node(self->right, n);
    }
    return self;
}

// Insert a value into the tree
void insert_bst(BST* self, int n) {
    self->root = insert_bst_node(self->root, n);
}

// Helper function for delete
BSTNodePtr min_node(BSTNodePtr self) {
    BSTNodePtr current = self;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Recursive function to delete a value
BSTNodePtr delete_bst_node(BSTNodePtr self, int n) {
    if (self != NULL) {
        if (n == self->data_item) { // Found item 
            if (self->left != NULL && self->right != NULL) {
                // Two child case 
                BSTNodePtr successor = min_node(self->right);
                self->data_item = successor->data_item;
                self->right = delete_bst_node(self->right, self->data_item);
            } else { // One or zero child case 
                BSTNodePtr to_free = self;
                if (self->left) {
                    self = self->left;
                } else {
                    self = self->right;
                }
                free(to_free);
            }
        } else if (n < self->data_item) {
            self->left = delete_bst_node(self->left, n);
        } else {
            self->right = delete_bst_node(self->right, n);
        }
    }
    return self;
}

// Delete a value from the tree
void delete_bst(BST* self, int n) {
    self->root = delete_bst_node(self->root, n);
}

// Recursive function to print in order
void print_in_order_bst_node(BSTNodePtr self) {
    if (self == NULL) {
        printf("_");
    } else {
        printf("(");
        print_in_order_bst_node(self->left);
        printf(" %d ", self->data_item);
        print_in_order_bst_node(self->right);
        printf(")");
    }
}

// Print the tree in order
void print_in_order_bst(BST *self) {
    print_in_order_bst_node(self->root);
}

// Recursive function to print in pre-order
void print_pre_order_bst_node(BSTNodePtr self) {
    if (self == NULL) {
        printf("_");
    } else {
        printf(" %d ", self->data_item);
        print_pre_order_bst_node(self->left);
        print_pre_order_bst_node(self->right);
    }
}

// Print the tree in pre-order
void print_pre_order_bst(BST *self) {
    print_pre_order_bst_node(self->root);
}

// Recursive function to print in post-order
void print_post_order_bst_node(BSTNodePtr self) {
    if (self == NULL) {
        printf("_");
    } else {
        print_post_order_bst_node(self->left);
        print_post_order_bst_node(self->right);
        printf(" %d ", self->data_item);
    }
}

// Print the tree in post-order
void print_post_order_bst(BST *self) {
    print_post_order_bst_node(self->root);
}

// Recursive function to compute the height of the tree
int height_bst_node(BSTNodePtr self) {
    if (self == NULL) {
        return -1;
    } else {
        int left_height = height_bst_node(self->left);
        int right_height = height_bst_node(self->right);
        return (left_height > right_height ? left_height : right_height) + 1;
    }
}

// Get the height of the tree
int height_bst(BST *self) {
    return height_bst_node(self->root);
}

// Recursive function to destroy all nodes
void destroy_bst_node(BSTNodePtr self) {
    if (self != NULL) {
        destroy_bst_node(self->left);
        self->left = NULL;
        destroy_bst_node(self->right);
        self->right = NULL;
        free(self);
    }
}

// Destroy the tree
void destroy_bst(BST *self) {
    destroy_bst_node(self->root);
    self->root = NULL;
}

// Unit test function
void bst_test() {
    BST tree = new_bst();

    // Testing insertion and printing
    printf("Inserting 5, 3, 7, 2, 0 into BST\n");
    insert_bst(&tree, 5);
    insert_bst(&tree, 3);
    insert_bst(&tree, 7);
    insert_bst(&tree, 2);
    insert_bst(&tree, 0);

    printf("In-order print: ");
    print_in_order_bst(&tree);
    printf("\n");

    printf("Pre-order print: ");
    print_pre_order_bst(&tree);
    printf("\n");

    printf("Post-order print: ");
    print_post_order_bst(&tree);
    printf("\n");

    printf("Tree height: %d\n", height_bst(&tree));

    // Testing deletion
    printf("Deleting 3 from BST\n");
    delete_bst(&tree, 3);

    printf("In-order print after deletion: ");
    print_in_order_bst(&tree);
    printf("\n");

    printf("Tree height after deletion: %d\n", height_bst(&tree));

    destroy_bst(&tree);
}
