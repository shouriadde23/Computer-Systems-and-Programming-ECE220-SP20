#include "merge_sort.h"


/*
    Split a linked list in half from the middle point

    ARGS:
        Node* in    -> head of the linked list
        int* length -> pointer to a memory location where the length of the first half of the list can be placed
    RET:
        returns the head of the second half list while the input pointer still points to the first half
*/
Node* split_ll(Node* in, int* length) {

    // @TODO insert your code here
    int i;
    int entered  = 0;
    int count = 0;
    Node *h2;
    Node *h1;
    Node *newNode;
    Node *p_h1;
    Node *r_h2;
    Node *cut_h1;
    Node *n = in;

    while(n != NULL) {
        count++;
        n = n->next;
    }
    *length = count/2;
    h1 = in;

    for(i = 0; i < *length; i++) {
        cut_h1 = h1;
        h1 = h1->next;
    }
    cut_h1->next = NULL;

    h2 = h1;
    return h2;
}

void my_print_list(Node* in) {
    #if 0
    while (in) {
        printf("%d, ", in->val);
        in = in->next;
    }
    printf("\n");
    #endif
}

Node* merge_ordered_ll(Node* heada, Node* headb) {

    // @TODO insert your code here
    
    // printf("Got inside merge_ordered_ll. Values of heada %d and headb %d\n", heada->val, headb->val);
    Node *mergeHead;

    Node *currA = heada;
    Node *currB = headb;
    Node *fA = currA;
    Node *fB = currB;
    unsigned int iter = 0 ;
    Node *ln = NULL ;

    // finding out the head of the merged linked list
    if(heada->val <= headb->val) {
        mergeHead = heada;
    }
    else {
        mergeHead = headb;
    }

    ln = mergeHead ;


    iter = 0 ;
    // printf("mergeHead value %d\n", mergeHead->val);
    // merging the two linked lists together here
    while(currA != NULL && currB != NULL) {
        // printf("IIIIIIIIIITER %d ENTERED ============ \n", iter ) ;
        if(currA->val == currB->val) {
            if ( ln == currA) {
                fA = currA->next;
                currA->next = currB;
                ln = currB ;
                currA = fA;
            } else if ( ln == currB ) {
                fB = currB->next;
                currB->next = currA;
                ln = currA ;
                currB = fB;
            }
        }
        // printf("hi");
        else if(currA->val < currB->val) {
            fA = currA->next;
            if((fA != NULL) && (fA->val < currB->val)) {
                // CA < fA < CB 
                currA = fA;
            }
            else if((fA != NULL) && (fA->val > currB->val)){
                // CA < CB < fA
                currA->next = currB;
                currA = fA;
            }
            else {
                // CA < CB == fA
                currA->next = currB;
                currA = fA;
                ln = currB ;
            }   
        }
        else {
            // CA > CB
            fB = currB->next;
            if((fB != NULL) && (currA->val > fB->val)) {
                // CB < fB < CA
                currB = fB;
            }
            else if((fB != NULL) && (currA->val < fB->val)) {
                // CB < CA < fB
                currB->next = currA;
                currB = fB;
            }
            else {
                // CB < CA == fB
                currB->next = currA;
                currB = fB;
                ln = currA ;
            }
        }
    } 

    return mergeHead;
}




/*
    Recursively sort a linked list

    ARGS:
        Node* head -> linked list head
    RET:
        returns the head of the sorted list
*/
Node* merge_sort(Node* head) {

    // @TODO insert your code here
    Node *a = head;
    Node *sortedA;
    Node *sortedB;
    if(head == NULL || head->next == NULL){
        return head;
    }
    int len;
    Node *b = split_ll(head, &len);
    sortedA = merge_sort(a);
    sortedB = merge_sort(b);

    return merge_ordered_ll(sortedA,sortedB);
}
