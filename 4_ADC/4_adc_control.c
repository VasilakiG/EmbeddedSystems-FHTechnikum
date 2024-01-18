/*

* File: 4_adc_control.c

* Name: Vasilaki Gjorgjioski

* Date: 17.1.2024

* Version: 4.0

* Description: This source file contains the implementation of functions for ADC. It implements a signal handler function that handles SIGINT and SIGTERM signals for graceful program termination. It also implements a function to read the value from the ADC.

*/

#include "4_adc_control.h"

volatile sig_atomic_t stop_flag = 0; // Initialize stop flag

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
    if (signal == SIGINT || signal == SIGTERM) // check if signal is SIGINT
    {
        // Handle SIGINT/SIGTERM for exiting
        stop_flag = TRUE;                                   // volatile flag for signal handling
        printf("Signal %d received. Exiting...\n", signal); // print signal number
        exit(EXIT_SUCCESS);                                 // exit with success
    }
}

/**
 * @brief Get the value from the ADC.
 *
 * This function reads the value from the ADC.
 *
 * @return The value from the ADC.
 */
int ain_get_value()
{
    int file_descriptor, value; // file descriptor and value
    char buffer[BUFFERSIZE];    // buffer for reading the value

    // Open the ADC file
    file_descriptor = open(ADC_PATH, O_RDONLY);

    // Check if file is opened
    if (file_descriptor == FAILURE)
    {
        perror("Error opening ADC file"); // print error message
        exit(TRUE);
    }

    // Read the ADC value from the file
    if (read(file_descriptor, buffer, sizeof(buffer)) == FAILURE)
    {
        perror("Error reading ADC value"); // print error message
        close(file_descriptor);            // close if the read fails
        exit(TRUE);
    }

    // Close the ADC file
    close(file_descriptor);

    // Convert the buffer value (string) to an integer
    sscanf(buffer, "%d", &value);

    // Return the converted ADC value
    return value;
}