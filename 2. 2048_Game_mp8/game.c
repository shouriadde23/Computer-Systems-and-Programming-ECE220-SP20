#include "game.h"
/* netid: shouria2
* In this MP, the objective was to create the 2048 game for an N x N board. In order to create the game
* I had to write the make and remake game which basically set the column, score, and row properties of
* of the game. After that, the next step was to complete the get_cell function which accessed the
* particular value at a given cell location. The next step was to complete all of the moves in the game.
* In order to complete the move up, I looped through all the rows and columns and checked for an empty
* cell. Once an empty cell was found, I checked to see if a slide could happen. Once the slide was done,
* I chccked to see if I could merge any values. The merge was essentially an addition of a cell value
* with the cell above it, followed by a score increment, erasing of copied value, and a decrement in the
* counter for the next sliding/merging process. I applied the sme process for the rest of the moves, but
* changd the boundary conditions. Finally,the is_valid_check added up all of the sums for the move functions
* and checked if it was possible to make a valid move or not. Overall, this MP was time consuming but I
* enjoyed doing it.
*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    // declaring loop variable 'i'
    int i = 0;
    // setting correct initial value to rows * mygame
    mygame->rows = rows;
    // setting correct initial value to cols * mygame
    mygame->cols = cols;
    // setting correct initial value to score of * mygame
    mygame->score = 0;

    // loop through pointer array and set all cell values of * mygame to -1
    for(i = 0; i <= ((rows * cols) - 1); i++) {
        *(mygame->cells + i) = -1;
    }
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any
	memory previously allocated is not lost in this function.
*/
{
    /*Frees dynamically allocated memory used by cells in previous game,
     then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
    free((*_cur_game_ptr)->cells);
    (*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

    // declaring loop variable 'i'
    int i = 0;
    // setting correct initial value to rows for the **_cur_game_ptr
    (*_cur_game_ptr)->rows = new_rows;
    // setting correct initial value to cols for the **_cur_game_ptr
    (*_cur_game_ptr)->cols = new_cols;
    // setting correct initial value of score to -1 for the **_cur_game_ptr
    (*_cur_game_ptr)->score = -1;

    // loop through pointer array and set all cell values of **cur_game_ptr to -1
    for(i = 0; i <= ((new_rows * new_cols)-1); i++) {
        *((*_cur_game_ptr)->cells + i) = -1;
    }
    return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    // check if the given row value is within 0 and curr_game->rows
    if(row < 0 || row >= (cur_game->rows)) {
        return NULL;
    }
    // check if the given row value is within 0 and curr_game->cols
    if(col < 0 || col >= (cur_game->cols)) {
        return NULL;
    }
    // access the current cell value for * cur_game and return the cell
    return cur_game->cells + (row * (cur_game->cols) + col);
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
    //declaring the loop variables i,j
    int i, j;
    // setting k to -1, because this will the column we want to find if cell isn't empty
    int k = -1;
    // setting the last combined row to -1
    int last_combo_row = -1;
    // initializing target as the variable that keeps track of the first empty cell we encounter
    int target;
    // initializing moved as the variable which this function returns
    int moved = 0;
    // loop through every column of * cur_game
    for(j = 0; j < cur_game->cols; j++) {
        // set last_combo_row equal to -1
        last_combo_row = -1;
        // loop through every row of * cur_game
        for(i = 0; i < cur_game->rows; i++) {
            // check if cell at the current row, col of * cur_game isn't empty
            if(*(cur_game->cells + i * cur_game->cols + j) != -1)  {
                // set value of target initially to 0
                target = 0;
                // loop from k to i and check to see if we encounter an empty cell
                for(k = 0; k < i; k++) {
                    // if we run into an empty cell, set target to 1, and break
                    if(*(cur_game->cells + k * cur_game->cols + j) == -1) {
                        target = 1;
                        break;
                    }
                }
                // when we encountered an empty cell, we 'slide up'
                if(target == 1) {
                    // copy the cell at (i,j) to the cell at (k,j)
                    *(cur_game->cells + k * cur_game->cols + j) = *(cur_game->cells + i * cur_game->cols + j);
                    // erase the value at (i, j)
                    *(cur_game->cells + i * cur_game->cols + j) = -1;
                    // set moved equal to 1
                    moved = 1;
                }

                // if the value of k -1 is != last_combo row, we can check if the 'merge' is possible
                if((k - 1) != last_combo_row) {
                    // if the cell value at the k - 1th row is equal to the kth row, we can merge
                    if(*(cur_game->cells + (k - 1) * cur_game->cols + j) == *(cur_game->cells + k * cur_game->cols + j)) {
                        // add the same cell value at the kth row to the k - 1th row
                        *(cur_game->cells + (k - 1) * cur_game->cols + j) *= 2;
                        // add the k-1th row's cell value to the overall score
                        cur_game->score +=  *(cur_game->cells + (k - 1) * cur_game->cols + j);
                        // clear the cell at the kth row because the merge is completed
                        *(cur_game->cells + k * cur_game->cols + j) = -1;
                        // set the last_comb_row to the k-1th value for the next iteration
                        last_combo_row = k - 1;
                        // set moved equal to 1
                        moved = 1;
                    }
                }
            } // end of if
        }
    }
    return moved;
};

int move_s(game * cur_game) //slide down
{
    //declaring the loop variables i,j
    int i, j;
    // setting k to -1, because this will the column we want to find if cell isn't empty
    int k = -1;
    // setting the last combined row to -1
    int last_combo_row = -1;
    // initializing target as the variable that keeps track of the first empty cell we encounter
    int target;
    // initializing moved as the variable which this function returns
    int moved = 0;
    // loop through every column of * cur_game
    for(j = 0; j <= cur_game->cols - 1; j++) {
        // set last_combo_row equal to -1
        last_combo_row = -1;
        // loop through every row of * cur_game backwards
        for(i = cur_game->rows - 1; i >=0; i--) {
            // check if cell at the current row, col of * cur_game isn't empty
            if(*(cur_game->cells + i * cur_game->cols + j) != -1)  {
                // set value of target initially to 0
                target = 0;
                // loop down from rows-1 to i and check to see if we encounter an empty cell
                for(k = cur_game->rows - 1; k > i; k--) {
                    // if we run into an empty cell, set target to 1, and break
                    if(*(cur_game->cells + k * cur_game->cols + j) == -1) {
                        target = 1;
                        break;
                    }
                }
                // when we encountered an empty cell, we 'slide up'
                if(target == 1) {
                    // copy the cell at (i,j) to the cell at (k,j)
                    *(cur_game->cells + k * cur_game->cols + j) = *(cur_game->cells + i * cur_game->cols + j);
                    // erase the value at (i, j)
                    *(cur_game->cells + i * cur_game->cols + j) = -1;
                    // set moved equal to 1
                    moved = 1;
                }

                // if the value of k + 1 is != last_combo row, we can check if the 'merge' is possible
                if((k + 1) != last_combo_row) {
                    // if the cell value at the k + 1th row is equal to the kth row, we can merge
                    if(*(cur_game->cells + (k + 1) * cur_game->cols + j) == *(cur_game->cells + k * cur_game->cols + j)) {
                        // add the same cell value at the kth row to the k + 1th row
                        *(cur_game->cells + (k + 1) * cur_game->cols + j) *= 2;
                        // add the k+1th row's cell value to the overall score
                        cur_game->score +=  *(cur_game->cells + (k + 1) * cur_game->cols + j);
                        // clear the cell at the kth row because the merge is completed
                        *(cur_game->cells + k * cur_game->cols + j) = -1;
                        // set the last_comb_row to the k+1th value for the next iteration
                        last_combo_row = k + 1;
                        // set moved equal to 1
                        moved = 1;
                    }
                }
            }
        }
    }
    return moved;
};

int move_a(game * cur_game) //slide left
{
    //declaring the loop variables i,j
    int i, j;
    // setting k to -1, because this will the col we want to find if cell isn't empty
    int k = -1;
    // setting the last combined col to -1
    int last_combo_col = -1;
    // initializing target as the variable that keeps track of the first empty cell we encounter
    int target;
    // initializing moved as the variable which this function returns
    int moved = 0;
    // loop through every row of * cur_game
    for(i = 0; i <= cur_game->rows - 1; i++) {
        // set last_combo_row equal to -1
        last_combo_col = -1;
        // loop through every col of * cur_game
        for(j = 0; j <= cur_game->cols - 1; j++) {
            // check if cell at the current row, col of * cur_game isn't empty
            if(*(cur_game->cells + i * cur_game->cols + j) != -1)  {
                // set value of target initially to 0
                target = 0;
                // loop from k to i and check to see if we encounter an empty cell
                for(k = 0; k < j; k++) {
                    // if we run into an empty cell, set target to 1, and break
                    if(*(cur_game->cells + i * cur_game->cols + k) == -1) {
                        target = 1;
                        break;
                    }
                }
                // when we encountered an empty cell, we 'slide up'
                if(target == 1) {
                    // copy the cell at (i,j) to the cell at (i,k)
                    *(cur_game->cells + i * cur_game->cols + k) = *(cur_game->cells + i * cur_game->cols + j);
                    // erase the value at (i, j)
                    *(cur_game->cells + i * cur_game->cols + j) = -1;
                    // set moved equal to 1
                    moved = 1;
                }

                // if the value of k -1 is != last_combo col, we can check if the 'merge' is possible
                if((k - 1) != last_combo_col) {
                    // if the cell value at the k - 1th col is equal to the kth col, we can merge
                    if(*(cur_game->cells + i * cur_game->cols + (k-1)) == *(cur_game->cells + i * cur_game->cols + k)) {
                        // add the same cell value at the kth col to the k - 1th col
                        *(cur_game->cells + i * cur_game->cols + (k - 1)) *= 2;
                        // add the k-1th col's cell value to the overall score
                        cur_game->score +=  *(cur_game->cells + i * cur_game->cols + (k - 1));
                        // clear the cell at the kth col because the merge is completed
                        *(cur_game->cells + i * cur_game->cols + k) = -1;
                        // set the last_comb_col to the k-1th value for the next iteration
                        last_combo_col = k - 1;
                        // set moved equal to 1
                        moved = 1;
                    }
                }
            }
        }
    }
    return moved;
};

int move_d(game * cur_game) //slide right
{
    //declaring the loop variables i,j
    int i, j;
    // setting k to -1, because this will the col we want to find if cell isn't empty
    int k = -1;
    // setting the last combined col to -1
    int last_combo_col = -1;
    // initializing target as the variable that keeps track of the first empty cell we encounter
    int target;
    // initializing moved as the variable which this function returns
    int moved = 0;
    // loop through every row of * cur_game
    for(i = 0; i < cur_game->rows; i++) {
        // set last_combo_row equal to -1
        last_combo_col = -1;
        // loop down through every col of * cur_game
        for(j = cur_game->cols; j >= 0; j--) {
            // check if cell at the current row, col of * cur_game isn't empty
            if(*(cur_game->cells + i * cur_game->cols + j) != -1)  {
                // set value of target initially to 0
                target = 0;
                // loop from k to i and check to see if we encounter an empty cell
                for(k = cur_game->cols - 1; k >= j; k--) {
                    // if we run into an empty cell, set target to 1, and break
                    if(*(cur_game->cells + i * cur_game->cols + k) == -1) {
                        target = 1;
                        break;
                    }
                }
                // when we encountered an empty cell, we 'slide up'
                if(target == 1) {
                    // copy the cell at (i,j) to the cell at (i,k)
                    *(cur_game->cells + i * cur_game->cols + k) = *(cur_game->cells + i * cur_game->cols + j);
                    // erase the value at (i, j)
                    *(cur_game->cells + i * cur_game->cols + j) = -1;
                    // set moved equal to 1
                    moved = 1;
                }

                // if the value of k +1 is != last_combo col, we can check if the 'merge' is possible
                if((k + 1) != last_combo_col) {
                    // if the cell value at the k + 1th col is equal to the kth col, we can merge
                    if(*(cur_game->cells + i * cur_game->cols + (k + 1)) == *(cur_game->cells + i * cur_game->cols + k)) {
                        // add the same cell value at the kth col to the k + 1th col
                        *(cur_game->cells + i * cur_game->cols + (k + 1)) *= 2;
                        // add the k + 1th col's cell value to the overall score
                        cur_game->score +=  *(cur_game->cells + i * cur_game->cols + (k + 1));
                        // clear the cell at the kth col because the merge is completed
                        *(cur_game->cells + i * cur_game->cols + k) = -1;
                        // set the last_comb_col to the k + 1th value for the next iteration
                        last_combo_col = k + 1;
                        // set moved equal to 1
                        moved = 1;
                    }
                }
            }
        }
    }
    return moved;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    // initializing loop variable i
    int i = 0;
    // declaring a copy of the current game status by calling make_game on * curr_game
    game * game_copy = make_game(cur_game->rows, cur_game->cols);

    // loop through entire * curr_game board and copy each of the cell values into * game_copy
    for(i = 0; i < ((cur_game->rows) * (cur_game->cols)); i++) {
        *(game_copy->cells + i) = *(cur_game->cells + i);
    }
    // call all of the move functions on game_copy; if sum equals 0, there are no possible legal moves
    if(move_w(game_copy) + move_a(game_copy) + move_d(game_copy) + move_s(game_copy) == 0) {
        return 0;
    }
    return 1;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{

    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }


    //check for an empty cell
    int emptycheck = 0;
    int i;

    for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
        if ((*cell_ptr) == -1){
            emptycheck = 1;
            break;
        }
        cell_ptr += 1;
    }
    if (emptycheck == 0){
        printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
        exit(0);
    }

    int ind,row,col;
    int num;
    do{
        ind = rand()%((cur_game->rows)*(cur_game->cols));
        col = ind%(cur_game->cols);
        row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
    //*get_cell(cur_game, row, col) = 2;
    num = rand()%20;
    if(num <= 1){
        *get_cell(cur_game, row, col) = 4; // 1/10th chance
    }
    else{
        *get_cell(cur_game, row, col) = 2;// 9/10th chance
    }
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;

    printf("\n\n\nscore:%d\n",cur_game->score);


    printf("\u2554"); // topleft box char
    for(i = 0; i < cols*5;i++)
        printf("\u2550"); // top box char
    printf("\u2557\n"); //top right char


    for(i = 0; i < rows; i++){
        printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    default:
                        printf("  X  ");

                }

            }
            cell_ptr++;
        }
        printf("\u2551\n"); //print right wall and newline
    }

    printf("\u255A"); // print bottom left char
    for(i = 0; i < cols*5;i++)
        printf("\u2550"); // bottom char
    printf("\u255D\n"); //bottom right char

    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
    int rows,cols;
    char buf[200];
    char garbage[2];
    int move_success = 0;

    switch ( input_char ) {
        case 'w':
            move_success = move_w(cur_game);
            break;
        case 'a':
            move_success = move_a(cur_game);
            break;
        case 's':
            move_success = move_s(cur_game);
            break;
        case 'd':
            move_success = move_d(cur_game);
            break;
        case 'q':
            destroy_game(cur_game);
            printf("\nQuitting..\n");
            return 0;
            break;
        case 'n':
            //get row and col input for new game
        dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
            while (NULL == fgets(buf,200,stdin)) {
                printf("\nProgram Terminated.\n");
                return 0;
            }

            if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
                rows < 0 || cols < 0){
                printf("Invalid dimensions.\n");
                goto dim_prompt;
            }

            remake_game(&cur_game,rows,cols);

            move_success = 1;

        default: //any other input
            printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

    if(move_success == 1){ //if movement happened, insert new tile and print the game.
        rand_new_tile(cur_game);
        print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
