/*                  
 *
 * prog4.h - header file adapted from 
 * UIUC ECE198KL Spring 2013 Program 4
 * student code by Steven S. Lumetta
 */

#ifndef PROG_5_H
#define PROG_5_H

#include <string.h>


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

extern int guess_number;
extern int max_score;
extern char solutions[4][10];
extern char* pool[];

int is_valid(char* str);

void print_pool();
 
int set_seed (const char seed_str[]);

void start_game ();

int make_guess (const char guess_str[]);


#endif /* PROG_5_H */


