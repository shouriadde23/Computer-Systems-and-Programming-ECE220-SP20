#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* netid: shouria2
* lab partner: rprasad3
* In MP10, the objective was to write functions which would work on a sparse matrix, which was a matrix that consisted of a mix of both zero and non-zero values.
*  In this MP the first function was load_tuples, which would read from a file, and load the matrix by reading line by line and calling set_tuples each time. The 
* next function that was written was gv_tuples, which would give you the value of a node in the sv_tuples_node linked list given the appropriate row and col values.
* After this function, the next function was set_tuples which essentially checked all of the conditions that would be met if a new node were to be either inserted,
* an existing node to be deleted, or overwriting the existing value of a node. In order to accomplish all of these tasks, I wrote a helper function called
* new_insert_node. This function did most of the "heavy lifting" for the set_tuples function. The next function was save_tuples which would go through the entire file
* and make sure that all data was saved. The destroy_tuples function was similar but instead of saving to a file, all the memory was freed. Finally, the add_tuples
* function would add 2 matrices of identical M by N sizes into a new matrix. To help write this function, I made use of the previously written gv_tuples and set_tuples.
* Overall this MP was very time consuming, but I enjoyed doing it.
*/

sp_tuples * load_tuples(char* input_file)
{
    // declaring row, columnm, and value vars
    int row = 0;
    int col = 0;
    double val = 0;

    // reading from the file and making sure the file isn't null
    FILE* fp = fopen(input_file, "r");
    if ( fp == NULL ) {
      printf("Filename %s doesn't exist! \n", input_file) ;
      return NULL ;
    }

    // declaring the tuple properties needed for the *matrix of type sp_tuples
    int mat_m, mat_n;
    sp_tuples * matrix;

    // allocating memory for the matrix using malloc
    matrix = (sp_tuples*)malloc(sizeof(sp_tuples));
    
    // reading from the file the mat_m and mat_n properties and storing them in appropriate address locations
    fscanf(fp, "%d %d \n", &mat_m, &mat_n);
    // setting file read properties
    matrix->m = mat_m;
    matrix->n = mat_n;
    // setting nz count and the tuples_head to NULL initially
    matrix->nz = 0;
    matrix->tuples_head = NULL;
    
    // keep reading from the file until you reach EOF (end of file)
    while(fscanf(fp, "%d %d %lf \n", &row, &col, &val) != EOF) {
        // call set_tuples with the correct row, col, and val values read from file
        set_tuples(matrix, row, col, val);
    }

    // close file and return loaded matrix
    return matrix;
}

double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    // declare a sp_tuples_node which will point to the head of the provided mat_t
    sp_tuples_node *runner = mat_t->tuples_head;
    // while the runner is NULL, run through list
    while(runner != NULL) {
        // check if the row and col properties match up with function inputs, and if so, return the runner->value
        if(runner->row == row && runner->col == col) {
            return runner->value;
        }
        // update the next pointer
        runner = runner->next;
    }
    return 0;
}

void set_tuples(sp_tuples *mat_t, int row, int col, double value)
{
    // variable which holds the value which will be returned by the helper function new_insert_node
    int nz_count = 0 ; 

    // create(with malloc) and initialize a new node
    sp_tuples_node *new_node = malloc(sizeof(sp_tuples_node));
    // update all the row properties with the given function inputs
    new_node->row = row;
    new_node->col = col;
    new_node->value = value;
    new_node->next = NULL;

    // call the new_insert_node helper function, which does a bulk of this function
    nz_count = new_insert_node(&(mat_t->tuples_head), new_node);
    // update the mat_t->nz value based off of what the new_insert_node returns
    mat_t->nz = mat_t->nz + nz_count ;
}

int new_insert_node(sp_tuples_node **head, sp_tuples_node *nn) {
    // declaring 2 sp_tuples_node pointers p and c
    sp_tuples_node *p = NULL;
    sp_tuples_node *c = NULL;

    // if the head is NULL, then check if the new node(nn)->value is NULL
    if(*head == NULL) {
        // if nn->value is not 0, then set the *head to nn, and return 1; otherwise free it and return 0
        if ( nn->value != 0 ) {
            *head = nn;
            return 1;
        } else {
            free(nn) ;
            return 0;
        }
    }
    
    p = *head;
    c = p;

    // Conditions in which we want to add new node as head with the list already populated with elements.
    // Check to see if nn->row is less than first node element. If so set head to nn.
    if ( ( nn->row < p->row) || 
         ( ( nn->row == p->row ) && ( nn->col < p->col ) ) 
       ) 
    {
        if ( nn->value != 0 ) {
            nn->next = p ;
            *head = nn ;
            return 1 ;
        } else { 
            free(nn) ;
            return 0; 
        }
    }

    // 2. Advance till we see the correct row
    while((c != NULL) && (c->row < nn->row)) {
        p = c;
        c = c->next;
    }

    // This is a condition of adding new element to end of linked list.
    // Check if c is null. It will be null if we have reached end of the list, 
    // and all this while the row in list was smaller than row in nn.
    // So now add nn to end of the list.
    if ( c == NULL) {
        if(nn->value != 0) {
            // printf("FIRST cNulll for adding nnrpw(%d) nncol(%d) prow(%d) pcol(%d) nnval(%lf) \n", nn->row, nn->col, p->row, p->col, nn->value) ;
            p->next = nn ;
            return 1;
        }
        else {
            free(nn);
            return 0;
        }
    }

    // At this point c->row could be equal to nn->row OR c->row could be greater than nn->row.
    // Handle the case when c->row is greater than nn->row, in which case put nn between p and c
    if(c->row > nn->row) {
        // insert nn between p and c if nn->value != 0
        if(nn->value != 0) {
            if ( p != c ) {
                p->next = nn;
                nn->next = c;
                return 1;
            }
        }
    }

    // After this point we need not compare nn->row value with the row value of any list node to be less than or greater than it.
    // =========== AFTER THIS we need to handle only nn->row comparision to be equal to node's row value. 
    while((c != NULL) && (c->col < nn-> col) && (c->row == nn->row)) {
        p = c;
        c = c->next;
    }

    // This is a condition of adding new element to end of the list.
    // c could become null here.
    // c becomes null if we have reached end of the list, and all this while, 
    // the col in list was smaller than col in nn and row in list is same as row in nn.
    // So now add nn to the end of the list.
    if ( c == NULL ) {
        if ( nn->value != 0 ) { 
            p->next = nn ; 
            return 1 ;
        } 
        else {
            free(nn) ; 
            return  0 ; 
        }
    }

    // after this point check of col values in list to be equal to or greater than nn->col
    // No need to check for row values less than or greater
    if ( ( c->row == nn->row ) && ( c->col == nn->col ) ) {
        if ( nn->value != 0 ) {
            c->value = nn->value ; 
            free(nn) ;
            return 0 ;
        } else {
            // This means we need to delete, c and nn
            p->next = c->next ;
            free(c) ;
            free(nn);
            return -1 ; 
        }
    }

    // now apply the check to see if c->row == nn->row
    if(p->row == nn->row) {
        if(nn->col > p->col) {
            // Always check for nn->value to be non zero prior to adding it into the list.
            if ( nn->value != 0 ) {
                // insert nn between p and c
                p->next = nn ;
                nn->next = c ;
                return 1 ;
            } else {
                // Do nothing, i.e dont add.
                return 0;
            }
        }
        else if(nn->col == p->col) {
            // Entire block needed.
            if(nn->value != 0) {
                // overwrite the value at c                          
                p->value = nn->value ;
                free(nn) ;
                return 0 ;
            }
            else {
                // delete p
                p->next = c;
                free(p);
                free(nn);
                return -1 ;
            }
        }
    } // end of if c->row == nn->row
    else if(p->row != nn->row) {
        // insert nn between p and c if nn->value != 0
        if(nn->value != 0) {
            if ( p != c ) {
                p->next = nn;
                nn->next = c;
                return 1;
            } 
        } else {
            free(nn) ;
        }
    }
    return 0;    
}

void save_tuples(char *file_name, sp_tuples *mat_t)
{
    // open the file that needs to be written into
    FILE* fp = fopen(file_name, "w");
    // declaring sp_tuples_node pointer runner
    sp_tuples_node *runner;

    // if the file is null, return from function
    if ( fp == NULL ) {
      printf("Filename %s doesn't exist  \n", file_name);
      return;
    }
    
    // write the mat_t->m and the mat_t->n properties to the file
    fprintf(fp, "%d %d \n", mat_t->m, mat_t->n);
    // set the runner to mat_t->tuples_head
    runner = mat_t->tuples_head;

    // loop through till runner is NULL and update runner->row, col, and value properties
    while(runner != NULL) {
        fprintf(fp, "%d %d %lf \n", runner->row, runner->col, runner->value);
        runner = runner->next;
    }
    // close the file
    fclose(fp);
}

sp_tuples *add_tuples(sp_tuples * matA, sp_tuples * matB) 
{
    // declaring double variables
    double aVal, bVal, cVal;
    // declaring sp_tuples pointer matC
    sp_tuples *matC;
    // malloc matC
    matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    // memsetting the matC initially
    memset(matC, 0, sizeof(sp_tuples)) ;

    // settng all the properties of m and n
    matC->m = 0;
    matC->n = 0;
    matC->nz = 0;
    matC->tuples_head = NULL;

    matC->m = matA->m;
    matC->n = matA->n;

    // setting sp_tuples_node pointer aHead tp point to tuples->head of matA
    sp_tuples_node *aHead = matA->tuples_head;

    // loop through matA and access the aHead->value
    while(aHead != NULL) {
        aVal = aHead->value;
        // call set_tuples with appropriate row, col indices, and aVal since matC doesn't presently have anything in it before adding matA
        set_tuples(matC, aHead->row, aHead->col, aVal);
        // update aHead to point to aHead->next
        aHead = aHead->next;
    }

    // setting sp_tuples_node pointer bHead tp point to tuples->head of matB
    sp_tuples_node *bHead = matB->tuples_head;
    
    // loop through matB and access the bHead->value
    while(bHead != NULL) {
        bVal = bHead->value;
        // get the appropriate cVal at the current bHead->row, bHead->col to perform the addition correctly
        cVal = gv_tuples(matC, bHead->row, bHead->col);
        // call set_tuples with appropriate row, col indices, and add values of cVal and bVal as the final value property
        set_tuples(matC, bHead->row, bHead->col, cVal + bVal);
        // update bHead to point to bHead->next
        bHead = bHead->next;
    }

    return matC;
}

// Optional (not graded)
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB) 
{ 
  return NULL;
}
	
void destroy_tuples(sp_tuples * mat_t){
	
    // declaring two sp_tuples_node pointers
    sp_tuples_node *runner;
    sp_tuples_node *prev;
    // set runner to point to mat_t->tuples_head
    runner = mat_t->tuples_head;
    // prev will be used as a reference to runner, while runner traverses through list
    prev = runner;

    // while runner is not null, update runner to runner->next, free runner, and set prev to runner
    while(runner != NULL) {
        runner = runner->next;
        free(prev);
        prev = runner;
    }
    // after freeing the list, free the actual mat_t struct
    free(mat_t);
} 
