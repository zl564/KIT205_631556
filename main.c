#include "list.h"

int main() {
    // Uncomment the function you want to test
    // list_test();
    list_adhoc_test();
    
    // Optionally test the reverse and merge functions
    // test_reverse_and_merge();

    return 0;
}

// Function to test reverse and merge functions.
void test_reverse_and_merge() {
    // Test reverse
    List list = new_list();
    insert_in_order(&list, 1);
    insert_in_order(&list, 2);
    insert_in_order(&list, 3);

    printf("Original list: ");
    print_list(&list);

    List reversed = reverse(&list);
    printf("Reversed list: ");
    print_list(&reversed);

    destroy_list(&list);
    destroy_list(&reversed);

    // Test merge
    List list1 = new_list();
    List list2 = new_list();

    insert_in_order(&list1, 1);
    insert_in_order(&list1, 3);
    insert_in_order(&list1, 5);

    insert_in_order(&list2, 2);
    insert_in_order(&list2, 4);
    insert_in_order(&list2, 6);

    List merged = merge(&list1, &list2);
    printf("Merged list: ");
    print_list(&merged);

    destroy_list(&list1);
    destroy_list(&list2);
    destroy_list(&merged);
}
