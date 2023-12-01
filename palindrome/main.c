#include <stdio.h>		// printf(), scanf()
#include <stdlib.h>		// exit()
#include <signal.h>		// signal()
#include <limits.h>		// INT_MAX
#include "palindrome.h" // isPalindrome()

#define TRUE 1 // true value

// Signal handler function
/**
 * @brief Signal handler function.
 *
 * This function is called when a signal is received.
 *
 * @param signal The signal number.
 */
void signal_handler(int signal)
{
	printf("Signal %d received\n", signal); // print signal number
	exit(EXIT_SUCCESS);						// exit with success
}

// main function
int main(int argc, char *argv[])
{
	// Handle SIGINT
	signal(SIGINT, signal_handler);

	// Handle SIGTERM
	signal(SIGTERM, signal_handler);

	int stringLength; // length of string to check

	printf("Enter the number of characters in the string:\n"); // prompt user for string length
	if (scanf("%d", &stringLength) != 1)					   // read string length from stdin
	{
		printf("Error: Invalid input\n"); // print error message
		return EXIT_FAILURE;			  // exit with failure
	}

	if (stringLength <= 0 || stringLength > INT_MAX) // check if string length is valid
	{
		printf("Error: Invalid string length\n"); // print error message
		return EXIT_FAILURE;					  // exit with failure
	}

	char *string = malloc(stringLength + 1); // string to check
	if (string == NULL)						 // check if memory allocation failed
	{
		printf("Error: Memory allocation failed\n"); // print error message
		return EXIT_FAILURE;						 // exit with failure
	}

	// loop until SIGINT is received
	while (TRUE) // infinite loop (until SIGINT is received)
	{
		printf("Enter a string: "); // prompt user for string
		scanf("%s", string);		// read string from stdin

		isPalindrome(string); // check if string is a palindrome
	}

	free(string);		 // free memory allocated for string
	return EXIT_SUCCESS; // exit with success
}