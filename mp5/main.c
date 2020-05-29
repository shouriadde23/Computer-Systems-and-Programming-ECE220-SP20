#include <stdio.h>
#include <string.h>

/* 
 * Your code is included as part of this file.
 */
#include "prog5.h"

/* This is the main code for the program, which calls the functions in prog4.c */
int main ()
{
    char buf[200]; //Character array to get string from user
    int number; //Tracks guess number, game terminates after 12
    int retval = 0;

    //Get seed and call set_seed
    do {
      printf ("Please enter a seed: ");
      if (NULL == fgets (buf, 200, stdin)) {
        printf ("\nProgram terminated.\n");
        return 3;
      }
    } while (!set_seed (buf));
    
    //Show valid guessing pool
    print_pool();
    
    //Call start game to get solution
    start_game();

    //Go until 10 guesses, or user wins
    for (number = 1; 10 >= number; number++) {
      printf ("Guess %d\n", number);
      do {
        printf ("Enter your guess: ");
        if (NULL == fgets (buf, 200, stdin)) {
          printf ("\nProgram terminated.\n");
          return 3;
        }
        retval = make_guess (buf);
      } while (retval <= 0);
        //If guess is correct, we are done
      if (retval == 2) {
        printf ("You guessed correctly in %d guesses.\n", guess_number);
        printf ("The solution was %s %s %s %s.\n", solutions[0], solutions[1], solutions[2], solutions[3]);
        return 0;
      }
    }
    //User has lost, print solution
    printf ("You failed to guess correctly in 10 guesses.\n");
    printf ("The solution was %s %s %s %s.\n", solutions[0], solutions[1], solutions[2], solutions[3]);

    return 0;
}

