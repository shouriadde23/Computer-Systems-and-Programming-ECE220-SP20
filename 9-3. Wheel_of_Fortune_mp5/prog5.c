/* netid: shouria2
 * In this MP, the objective was to create a Wheel of Fortune modified game. As a part of the
 * MP the task was to implement the set_seed, start_game, and make_guess methods. In the set_seed
 * method, I used a sscanf call to check if the user's input was an integer or not. If the user
 * did not enter a number, then the entered expression was invalid and the user would be prompted
 * to enter a value set_seed value. In the start_game method, the objective was to generate a random
 * index copy a string from the "pool" to the "solutions". In order to accomplish this, I used the
 * rand function with the modulus operand to cover the random number range specified. Finally, I looped
 * character by character for each string in the pool to the solutions and set the guess_number value
 * to 1 and the max_score to -1. The last function was the start_game which checked if the user string
 * was valid and counted either perfect or mismatched matches. To start, I broke up the user string into
 * an array of words which I would later call the is_valid method on to check if they were valid or not.
 * After the validity of the strings was checked, the next step was to compare the "guess_words" with the
 * "solutions" words and check to see if the words at the current index were equal or not. After this check,
 * the next step was to account for misplaced matches. Finally, if 4 perfect matches were encountered, the function
 * would return 2, else it would return 1. This MP was relatively straightforward and I enjoyed developing the
 * appropriate logic which would help pass test cases.
 */


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully.
//    Check that the return value is 1 to ensure the user enters only an integer.
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
//    You may need to change the return statement below

	// declaring the integer variable seed
	int seed;
    // declaring a 1-D char array of size 2 called post
	char post[2];
	// using sscanf to see if result == 1, if != 1 then print and return 0
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {
      printf("set_seed:invalid seed\n");
      return 0;
    }
    // call srand on seed value and return 1
    else {
    	srand(seed);
    	return 1;
    }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
	// declaring integer variable called index
	int index = 0;
   // loop through 4 times and generate a random integer from 0 to 7
   // copy each character of each pool word into the solutions pool by using 2-D accessing
	for(int i = 0; i < 4; i++) {
    	index = rand() % 8;
    	for(int j = 0; j < 5; j++) {
    		solutions[i][j] = pool[index][j];
    	}
    }
	// increment guess_number and decrement max_score
	guess_number = 1;
    max_score = -1;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid,
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
  // declare a 2-D array which consists of the guess_str separated by words
	char guess_words[4][10];
	// declare a char array called key which checks for unnecessary information at end of guess_str
	char key[2];
	// intialize variables named currentscore, perfectmatches, and misplaced matches
	int currentscore = 0;
	int perfectmatches = 0;
	int misplacedmatches = 0;

	// splitting the user's string into the 4 words
	int n = sscanf(guess_str, "%s %s %s %s %1s", guess_words[0], guess_words[1], guess_words[2], guess_words[3], key);

	// if key value is not null and there are not 4 valid words, then print "invalid guess" and return 0
	if(key[0] != '\0' && n != 4) {
		printf("make_guess: invalid guess\n");
		return 0;
	}

	// check if each of the guess_words is valid or not by calling the helper method is_valid
	// if is_valid does not return a value of 1, then print "invalid guess" and return 0
	for(int i = 0; i < 4; i++) {
		if(is_valid(guess_words[i]) != 1) {
			printf("make_guess: invalid guess\n");
			return 0;
		}
	}

	// check the condition when at an index, guess_words and solutions have the same value
	// if they both have the same value, then increment the perfectmatches count value by 1
	for(int i = 0; i < 4; i++) {
		if(strcmp(guess_words[i], solutions[i])==0) {
			// mark solution[i] and guess[i] as matched by incrementing the perfectmatches count
			perfectmatches++;
		}
	}
	// check the condition when at an index, guess_words and solutions don't match
	for(int i = 0; i < 4; i++) {
		if(strcmp(guess_words[i], solutions[i])!=0) {
			// declare another loop variable j and check if the guess_words and solutions at this index don't match
			for(int j = 0; j < 4; j++) {
				if(strcmp(guess_words[j], solutions[j])!=0) {
					// check if guess_words[i] == solutions[j] and if this is the case then increment misplacedmatches count
					// after incrementing misplacedmatches count, break out of innermost for-loop
					if(strcmp(guess_words[i], solutions[j])==0) {
						misplacedmatches++;
                        break;
					}
				}
			}
		}
	}

	// calculate score by formula: currentscore = perfectmatches * 1000 + misplacedmatches * 100
	// substitute if current score is larger than current max_score
	currentscore = perfectmatches * 1000 + misplacedmatches * 100;
	if(currentscore > max_score) {
		max_score = currentscore;
	}
	// display information involving guess number, perfect matches, misplaced matches, current score, and current max score
	printf("With guess %d, you got %d perfect matches and %d misplaced matches. \nYour score is %d and current max score is %d.\n", guess_number, perfectmatches, misplacedmatches, currentscore, max_score);
	// increment the guess_number
	guess_number++;
	// check for 4 perfect matches, this means that the user got the correct answer
	// return 2 if there are 4 perfect matches, otherwise return 1
	if(perfectmatches == 4) {
		return 2;
	}
	else {
		return 1;
	}

}
