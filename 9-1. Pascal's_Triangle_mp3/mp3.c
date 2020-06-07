#include <stdio.h>
#include <stdlib.h>

/* netid: shouria2
   group partners: rajkp2
   In this MP, the objective was to print the set of values in a row of Pascal's Triangle, where the row number
   would be provided by the user. The first step was to scan the user input and store it into the variable 'row'.
   I also declared the variable 'i' which would be used later in the program to compute the values for the inputted
   row. After initializing the answer variable to the initial value of i, which was 1, I printed the intial answer
   variable out and this gave me the first value in the inputted row. After this, I wrote a loop which accounted
   for printing each of the values in the inputted row. The formula I used was provided by the MP, but the 
   important catch was to multiply the formula by the initial answer value. After each value in the row was found,
   I printed it one at a time followed by a space. Once this was done, I printed a new line and returned from the
   main function.
*/

int main()
{
  /* This line of code initializes the row number, provided by the user */
  int row;
 
  /* Asking the user to enter the row in Pascal's Triangle */
  printf("Enter a row index: ");
  /* Scan the user input and store the input into the variable row */
  scanf("%d",&row);
  
  /* Initialize i as a variable which keeps track of how many times values should be printed for inputted row */
  int i = 1;
  /* Setting the answer initially to a value of 1, which accounts for the first value in the inputted row */
  unsigned long ans = i;
  /* Printing the first value in the inputted row */
  printf("%lu ", ans);
  
  /* Begin a loop for the number of values that should be printed for the inputted row */
  for(i = 1; i <= row; i++) {
      /* Implemented the given formula using the previous answer, the row number, and the current i value */
      ans = (ans *((row + 1) - i))/i;
      /* Print the current value of the answer */
      printf("%lu ", ans);
  }
  /* Print a new line for formatting purposes */
  printf("\n");
  /* Return from the main function */
  return 0;
}
