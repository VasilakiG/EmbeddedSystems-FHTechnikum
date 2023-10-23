#include <stdio.h>	 // printf(), scanf()
#include <string.h>	 // strlen()
#include <stdbool.h> // bool
#include <signal.h>	 // signal()
#include <stdlib.h>	 // exit()
#include <ctype.h>	 // tolower()

void isPalindrome(char string[])
{
	int length = strlen(string); // length of string
	bool palindrome = true;		 // assume string is a palindrome

	/*
		check if string is a palindrome, ignoring case
		comparing first and last characters, then second and second last characters, etc.
		until the middle of the string is reached
	*/
	for (int i = 0; i < length / 2; i++)
	{
		if (tolower(string[i]) != tolower(string[length - i - 1]))
		{
			palindrome = false;
			break;
		}
	}

	// print result
	if (palindrome)
	{
		printf("%s is a palindrome\n", string);
	}
	else
	{
		printf("%s is not a palindrome\n", string);
	}
}

// signal handler for SIGINT
void signal_handler(int signal)
{
	printf("Signal %d received\n", signal);
	exit(0);
}

// main function
int main(int argc, char *argv[])
{
	signal(SIGINT, signal_handler); // register signal handler for SIGINT

	char string[100]; // string to check

	// loop until SIGINT is received
	while (1)
	{
		printf("Enter a string: "); // prompt user for string
		scanf("%s", string);		// read string from stdin

		isPalindrome(string); // check if string is a palindrome
	}

	return 0; // exit with success
}