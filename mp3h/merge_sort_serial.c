#include "merge_sort.h"



int main() {
    Node* head = make_ll_from_file("input.txt");
    
    Node *result;
    result = merge_sort(head);
    print_list(result,"serial_output.txt");
    free_list(result);
    return 0;
}
