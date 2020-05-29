/* netid: shouria2
 * group members: akhatua2
 * In this MP, the object was to print a set of semiprimes in a given set of integers,
 * starting from the integer 'a' to the integer 'b'. In order for this program to work,
 * the first step was to take the two user inputted numbers (a and b) and scan them. Then,
 * the next step was to call the print_semiprimes function on the integers a and b. In
 * addition, I also wrote the is_prime function which was used to check if a number was
 * even or not. Finally, the prime_semiprimes function would print all the primes in the
 * set of a to b by using the is_prime function to check if the current number was prime
 * or not. This MP was relatively easy and it was interesting because it essentially
 * translated the concept of LC3 subroutines into the idea of calling written functions
 * in the C programming style. */

#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   // print_semiprimes(a, b);
   print_semiprimes(a, b);
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
	/* Set up a for loop which loops through the entire 'size' of the number and checks if
	 * it is divisible by the value of i which continues to decrement. If the number is not
	 * divisible, then this means that it is a prime number.
	 */
	for(int i = number - 1; i > 1; i--) {
		if(number % i == 0) {
			return 0;
		}
		else {
			continue;
		}
	}
	return 1;
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
	/* Declare the variable value which is what you check before you return from this function.
	 * Implement the given algorithm: loop from  a to b and from k to n-1 and check if k is
	 * a prime factor, and if n/k is prime as well. If this is the case, then print n and
	 * assign value with 1. Finally, check if value is 1, and if it is then return 1. Else,
	 * return from the function with the value of 0.
	 */
	int value = 0;
	for(int n = a; n <= b; n++) {
		for(int k = 2; k <= n - 1; k++) {
			if((is_prime(n/k)) == 1 && (is_prime(k) == 1) && (n % k == 0)) {
				printf("%d ", n);
				value = 1;
				break;
			}
		}
	}
	if(value == 1) {
		return 1;
	}
	else {
		return 0;
	}
}





