#include "palindrome.h"
#include <string.h> // strlen()

#define HALF_LENGTH length / 2 // half the length of the string

// Function to check if a string is a palindrome
/**
 * Checks if a given string is a palindrome.
 *
 * @param string The string to be checked.
 */
void isPalindrome(char string[])
{
    int length = strlen(string); // length of string
    bool palindrome = true;      // assume string is a palindrome

    /*
        check if string is a palindrome, ignoring case
        comparing first and last characters, then second and second last characters, etc.
        until the middle of the string is reached
    */
    for (int i = 0; i < HALF_LENGTH; i++)
    {
        if (tolower(string[i]) != tolower(string[length - i - 1])) // check if characters are not equal
        {
            palindrome = false; // string is not a palindrome
            break;
        }
    }

    // print result
    if (palindrome)
    {
        printf("%s is a palindrome\n", string); // print result
    }
    else
    {
        printf("%s is not a palindrome\n", string); // print result
    }
}