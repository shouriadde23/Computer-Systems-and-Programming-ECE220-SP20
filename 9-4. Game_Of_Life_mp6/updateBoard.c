/* netid: shouria2
 * In this MP, the objective was to create a Game of Life "simulation" The 3 functions that were implemented in this MP
 * were countLiveNeighbor, updateBoard, and aliveStable. The purpose of countLiveNeighbor was to count the number of live
 * neighbors for each cell on the board. To finish this function, I looped from rows currRow - 1 to currRow + 1 inclusive
 * and currCol - 1 to currCol + 1 inclusive. Then, I checked if the currCol value fell within the col size and if the cell
 * existed on the board and was alive, the board value at that cell would be set equal to 1. In updateBoard, I looped through
 * all rows and columns of the board after storing a copy of it beforehand. I checked the number of live neighbors for each
 * cell by calling countLiveNeighbor and updated the current cell value based off the number of live neighbors. Finally, in
 * the aliveStable function, I made a copy of the original board and looped through the entire board calling updateBoard on
 * each cell. If the "new generation/board" was different from the "original generation/board", then I would return 0. Otherwise,
 * I would return 1. This MP was very interesting and I had fun while doing it.
 */

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    // setting the number of live neighbors to 0
    int num_neighbors = 0;
    // setting loop indices i, j
    int i, j;
    // loops through rows from currRow - 1 to currRow + 1 (inclusive)
    for(i = row - 1; i <= row + 1; i++) {
        // check if currRow falls within the bounds of the given row size
        if(i >= 0  && i < boardRowSize) {
            // loops through rows from currCol - 1 to currCol + 1 (inclusive)
            for(j = col - 1; j <= col + 1; j++) {
                // check if currCol falls within the bounds of given col size
                if(j >= 0 && j < boardColSize) {
                    // if the cell isn't at currRow, currCol
                    if(i != row || j != col) {
                        // if cell is alive then increment the number of neighbors
                        if (board[i * boardColSize + j] == 1) {
                            num_neighbors++;
                        }
                    }
                }
            }
        }
    }
    // return the number of neighbors
    return num_neighbors;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    // store the original copy of the board before it is modified in future generations
    int prev_board[boardRowSize * boardColSize];
    // initializing loop indices i,j,k
    int i, j, k;
    // loop through the entire board and copy prev_board into board
    for(k = 0; k < boardRowSize * boardColSize; k++) {
        prev_board[k] = board[k];
    }
    // loop through the rows
    for(i = 0; i < boardRowSize; i++) {
        // loop through the columns
        for(j = 0; j < boardColSize; j++) {
            // checking if the current cell is alive
            if(board[i * boardColSize + j] == 1) {
                // if the number of neighbors is not 2 or 3 in prev_board, then alive cell dies
                if(countLiveNeighbor(prev_board, boardColSize, boardColSize, i, j) < 2 ||
                countLiveNeighbor(prev_board, boardColSize, boardColSize, i, j) > 3) {
                    board[i * boardColSize + j] = 0;
                }
            }
            // condition where the current cell is dead
            else {
                // if number of live neighbors around the dead cell == 3 in prev_board, dead cell gains life
                if(countLiveNeighbor(prev_board, boardColSize, boardColSize, i, j) == 3) {
                    board[i * boardColSize + j] = 1;
                }
            }
        }
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    // store the original copy of the board before it is modified in future generations
    int prev_board[boardRowSize * boardColSize];
   // initializing loop indices i,j
    int i, j;
    // loop through the entire board and copy prev_board into board
    for(i = 0; i < boardRowSize * boardColSize; i++) {
        prev_board[i] = board[i];
    }
    // call updateBoard on prev_board to update status
    updateBoard(prev_board, boardRowSize, boardColSize);
    // loop through board and check if the prev_board and board hold same values
    for(j = 0; j < boardRowSize * boardColSize; j++) {
        // if prev_board and board hold different values, return 0
        if(board[j] != prev_board[j]) {
            return 0;
        }
    }
    // otherwise return 1
    return 1;
}

				
				
			

