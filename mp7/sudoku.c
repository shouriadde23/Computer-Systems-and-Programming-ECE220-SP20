#include "sudoku.h"

/* netid: shouria2
 * In this MP, the objective was to create a Sudoku Solver using a backtracking algorithm and
 * completing other functions which would be used later in determining if a solution was possible
 * or not. The is_val_in_row and is_val_in_col methods were used to check if val already existed
 * in the respective row and col. The is_val_in_3x3_zone function was used to check if val existed
 * in the respective 3 by 3 zone by starting at the left-most corner and traversing through all 9
 * elements in the appropriate square. To make sure if a cell was filled or not, the is_val_valid
 * function checked all of the 3 previous functions. Before I wrote the backtracking algorithm to
 * solve the sudoku puzzle, I wrote a helper function called cellassign which checked if all the
 * cells were assigned with a value or not. Finally, I implemented the solve_sudoku function which
 * used both the cellassign and is_val_valid functions and the given backtracking algorithm. This
 * MP was fun and I enjoyed developing all  of the functions which enabled the solve_sudoku function
 * to work appropriately.
*/


// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

    assert(i>=0 && i<9);
    // loop through all of the columns for the 'ith' row
    for(int k = 0; k < 9; k++) {
        // if current row and col value == val, return 1
        if(sudoku[i][k] == val) {
            return 1;
        }
    }
    return 0;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

    assert(j>=0 && j<9);
    // loop through all of the rows for the 'jth' col
    for(int k = 0; k < 9; k++) {
        // if the current col and row value == val, return 1
        if(sudoku[k][j] == val) {
            return 1;
        }
    }
    return 0;
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

    assert(i>=0 && i<9);
    // declare currrow and currcol values as the top left corner values of 3 x 3 square
    int currrow = 3 * int(i/3);
    int currcol = 3 * int(j/3);
    // initialize startrow and startcol as currrow and currcol and loop 3 times
    for(int startrow = currrow; startrow < currrow + 3; startrow++) {
        for(int startcol = currcol; startcol < currcol + 3; startcol++) {
            // if 'val' exists at current location, then return 1
            if(sudoku[startrow][startcol] == val) {
                return 1;
            }
        }
    }
    return 0;
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

    assert(i>=0 && i<9 && j>=0 && j<9);
    // if all of these functions return 0, then there is an empty cell that can be filled
    if((is_val_in_row(val, i, sudoku) == 0) && (is_val_in_col(val, j, sudoku) == 0)
      && (is_val_in_3x3_zone(val, i, j, sudoku) == 0)) {
        // return 1 as long as there is an empty cell available
        return 1;
    }
    return 0;
}

// This is a helper function that I worte which would check if all of the cells were assigned
int cellassign(int sudoku[9][9]) {
    int i, j;
    // loop through all rows and columns of sudoku array
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            // if any of the elements are not filled, automatically return 0
            if(sudoku[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
  // declaring variables to be used in this function
  int i, j, emptyrow, emptycol, num;
  // making use of the previous helper function to check all cells are assigned
  if(cellassign(sudoku) == 1) {
    return 1;
  }
  else {
    // loop through the entire sudoku 2D array
    for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++) {
        // current entry empty, copy ith and jth indices into emptyrow & emptycol
        if (sudoku[i][j] == 0) {
          emptyrow = i;
          emptycol = j;
          // since index is found, break out of loop
          break;
        }
      }
    }
  }
  // loop through all of the num values
  for(num = 1; num <= 9; num++) {
    // if there is an empty cell, fill sudoku[emptyrow][emptycol] with num
    if(is_val_valid(num, emptyrow, emptycol, sudoku) == 1) {
      sudoku[emptyrow][emptycol] = num;
        // if the sudoku can be solved with prev assignment, return 1
        if(solve_sudoku(sudoku) == 1) {
          return 1;
        }
        // otherwise, set sudoku[emptyrow][emptycol] with value of 0
        sudoku[emptyrow][emptycol] = 0;
      }
    }
    return 0;
}


// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
    int i, j;
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            printf("%2d", sudoku[i][j]);
        }
        printf("\n");
    }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
    FILE *reader = fopen(fpath, "r");
    assert(reader != NULL);
    int i, j;
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            fscanf(reader, "%d", &sudoku[i][j]);
        }
    }
    fclose(reader);
}
