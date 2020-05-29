#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"
/*
 * netid: shouria2
 * partners: hb10, rajkp2
 * In this MP, the objective was to use a Depth-First Search Algorithm to find a possible set of solutions to
 * solve a given maze text file. The first part of this MP involved creating a maze given the appropriate maze
 * text file. In the first function, there was malloc done for the new maze_struct, each of the 'cells' values
 * in the new maze_struct, and for each row of values in the new maze_struct. After the mallocs and appropriate
 * file reading processes were completed, the next step was to handle newline scenarios and to make sure that
 * if the current indices equaled the start or end values, to set the current cell value accordingly. After this
 * function, the next steps were to write functions to print and destroy the maze. After that the next step was
 * to implement the DFS algorithm which first checked the base cases, and then tried to create a valid path. If
 * the current step in the path failed, then the algorithm would use backtracking to go back to a valid solution
 * which would continue to recursively check for valid solutions till the endpoint was reached. Overall, this MP
 * was interesting and I enjoyed doing it.
 */

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // declaring loop variables i and j
    int i, j;


    FILE* fp = fopen(fileName, "r");
    if ( fp == NULL ) {
      printf("Filename %s doesn't exist  \n", fileName) ;
      return NULL ;
    }

    // declaring maze properties which will be filled by reading from the file
    int fileRows, fileCols;
    // declare variable which will store current cell value
    char cellVal;
    // initialize file reader to start reading fileName
    maze_t *maze_struct ;

    // dynamically allocate memory for the maze_t structure
    maze_struct = (maze_t*)malloc(sizeof(maze_t));

    // use fscanf to get store the col and row dimensions of the maze
    fscanf(fp, "%d %d \n", &fileCols, &fileRows);
    // update row and col parameters of maze_struct into declared row and col properties
    maze_struct->height = fileRows;
    maze_struct->width = fileCols;
    // dynamically allocate memory for all cells in the maze_t structure
    maze_struct->cells = (char**)malloc(fileRows * sizeof(char*));


    // call malloc to allocate memory for each individual row
    for(i = 0; i < fileRows; i++) {
        maze_struct->cells[i] = (char*)malloc(fileCols * sizeof(char));
    }
    // loop through all of the cells and fill the newly created maze: maze_struct
    for(i = 0; i < fileRows; i++) {
        for(j = 0; j < fileCols; j++) {
            // call fgetc to get the current char and store that char val in cellVal
            cellVal = fgetc(fp);
            // check to see if you encountered a newline, and if so, decrement the fileCols index
            if(cellVal == '\n') {
                j--;
            }
            // otherwise, set the cells[i][j] value to cellVal
            else {
                maze_struct->cells[i][j] = cellVal;
            }
            // as long as you have a positive column index begin this check
            if(j >= 0) {
                // if the cells[i][j] value equals start, adjust the startRow and startColumn indices
                if(maze_struct->cells[i][j] == 'S') {
                    maze_struct->startRow = i;
                    maze_struct->startColumn = j;
                }
                // if the cells[i][j] value equals start, adjust the startRow and startColumn indices
                if(maze_struct->cells[i][j] == 'E') {
                    maze_struct->endRow = i;
                    maze_struct->endColumn = j;
                }
            }
        }
    }
    // stop reading from the file
    fclose(fp);
    // return the created maze
    return maze_struct;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    if(maze == NULL) {
      printf("You can't destroy this maze!\n");
      return;
    }
    // initializing loop variable i
    int i = 0;
    // loop through every row in cells and free every row
    for(i = 0; i < maze->height; i++) {
        free(maze->cells[i]);
    }
    // free cells
    free(maze->cells);
    // free maze
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // declaring the loop variables i and j
    int i, j;
    if(maze == NULL) {
      printf("You can't print this maze!\n");
      return ;
    }
    // printing the maze width and height at the beginning of the maze
    printf("%d %d\n", maze->width, maze->height);
    // loop through all the rows and cols and print out the cell values at the row, col indices
    for(i = 0; i < maze->height; i++) {
        for(j = 0; j < maze->width; j++) {
            printf("%c", maze->cells[i][j]);
        }
        // print a new line after the end of each row
        printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeDFS(maze_t * maze, int col, int row)
{
    if(maze == NULL) {
      printf("You can't solve this maze!\n");
      return 0;
    }
    // Begin the base cases for the DFS algorithm

    // if (col, row) is outside bounds of maze, return false
    if(col < 0 || col >= maze->width || row < 0 || row >= maze->height) {
        return 0;
    }
    // if (col, row) is not an empty cell, return false
    if(maze->cells[row][col] == '%' || maze->cells[row][col] == '*' || maze->cells[row][col] == '~') {
        return 0;
    }
    // if (col, row) is the end of the maze return true
    if(maze->cells[row][col] == 'E') {
        maze->cells[maze->startRow][maze->startColumn] = 'S';
        return 1;
    }

    // set (col, row) as part of the solution path in the maze, try the path so far
    if(maze->cells[row][col] != 'E') {
        maze->cells[row][col] = '*';
    }

    // Begin all the possible recursive cases

    // if (solveMaze(left of (col, row) ) == true) return true
    if(solveMazeDFS(maze, col - 1, row) == 1) {
        return 1;
    }
    // if (solveMaze(right of (col, row) ) == true) return true
    if(solveMazeDFS(maze, col + 1, row) == 1) {
        return 1;
    }
    // if (solveMaze(up of (col, row) ) == true) return true
    if(solveMazeDFS(maze, col, row + 1) == 1) {
        return 1;
    }
    // if (solveMaze(down of (col, row) ) == true) return true
    if(solveMazeDFS(maze, col, row - 1) == 1) {
        return 1;
    }

    // Begin the backtracking portion, if you've reached dead end/invalid solution

    // unmark (col, row) as part of solution and mark as visited
    if((maze->cells[row][col] != 'S') && (maze->cells[row][col] != 'E')) {
        maze->cells[row][col] = '~';
    }
    // return false
    return 0;
}
