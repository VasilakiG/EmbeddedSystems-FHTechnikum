/*

* File: 3_gpio_control.c

* Name: Vasilaki Gjorgjioski

* Date: 15.12.2023

* Version: 3.0

* Description: This source file contains the implementation of functions for controlling GPIO pins. It provides functions for exporting and unexporting GPIO pins, setting their direction, setting their value, and getting their value. It also defines constants for the paths of GPIO export and unexport files, as well as constants for GPIO pin numbers.

*/
#include "3_gpio_control.h" // GPIO control functions

volatile sig_atomic_t stop_flag = 0; // Initialize stop flag
volatile int led_state = 0;          // Initialize LED state

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
    if (signal == SIGALRM) // check if signal is SIGALRM
    {
        // Toggle LED state
        gpio_set_value(GPIO_LED1_PIN, led_state);  // toggle LED1
        gpio_set_value(GPIO_LED2_PIN, !led_state); // toggle LED2
        led_state = !led_state;                    // toggle LED state
    }
    else if (signal == SIGINT || signal == SIGTERM) // check if signal is SIGINT
    {
        // Handle SIGINT/SIGTERM for exiting
        stop_flag = 1;                                      // volatile flag for signal handling
        printf("Signal %d received. Exiting...\n", signal); // print signal number
        exit(EXIT_SUCCESS);                                 // exit with success
    }
}

// Export GPIO pin
int export_gpio(const char *gpio_pin)
{
    int export_fd = open(GPIO_EXPORT_PATH, O_WRONLY); // open GPIO export file
    if (export_fd == FAILURE)                         // check if file open failed
    {
        perror("Error opening export file"); // print error message
        return FAILURE;                      // return with failure
    }

    int len = strlen(gpio_pin);                 // length of GPIO pin string
    if (write(export_fd, gpio_pin, len) != len) // write GPIO pin to export file
    {
        perror("Error exporting GPIO pin"); // print error message
        close(export_fd);                   // close GPIO export file
        return FAILURE;                     // return with failure
    }

    close(export_fd);    // close GPIO export file
    return EXIT_SUCCESS; // return with success
}

// Unexport GPIO pin
int unexport_gpio(const char *gpio_pin)
{
    int unexport_fd = open(GPIO_UNEXPORT_PATH, O_WRONLY); // open GPIO unexport file
    if (unexport_fd == FAILURE)                           // check if file open failed
    {
        perror("Error opening unexport file"); // print error message
        return FAILURE;                        // return with failure
    }

    int len = strlen(gpio_pin);                   // length of GPIO pin string
    if (write(unexport_fd, gpio_pin, len) != len) // write GPIO pin to unexport file
    {
        perror("Error unexporting GPIO pin"); // print error message
        close(unexport_fd);                   // close GPIO unexport file
        return FAILURE;                       // return with failure
    }

    close(unexport_fd);  // close GPIO unexport file
    return EXIT_SUCCESS; // return with success
}

// Set GPIO direction
int gpio_set_dir(const char *gpio_pin, const char *direction)
{
    char dir_path[50];                                               // direction file path
    sprintf(dir_path, "/sys/class/gpio/gpio%s/direction", gpio_pin); // create direction file path

    int dir_fd = open(dir_path, O_WRONLY); // open direction file
    if (dir_fd == FAILURE)                 // check if file open failed
    {
        perror("Error opening direction file"); // print error message
        return FAILURE;                         // return with failure
    }

    if (write(dir_fd, direction, strlen(direction)) != (ssize_t)strlen(direction)) // write direction to direction file
    {
        perror("Error setting GPIO direction"); // print error message
        close(dir_fd);                          // close direction file
        return FAILURE;                         // return with failure
    }

    close(dir_fd);       // close direction file
    return EXIT_SUCCESS; // return with success
}

// Set GPIO value
int gpio_set_value(const char *gpio_pin, int value)
{
    char value_path[50];                                           // value file path
    sprintf(value_path, "/sys/class/gpio/gpio%s/value", gpio_pin); // create value file path

    int value_fd = open(value_path, O_WRONLY); // open value file
    if (value_fd == FAILURE)                   //
    {
        perror("Error opening value file"); // print error message
        return FAILURE;                     // return with failure
    }

    char value_str[2];               // value string
    sprintf(value_str, "%d", value); // create value string

    if (write(value_fd, value_str, strlen(value_str)) != (ssize_t)strlen(value_str))
    {
        perror("Error setting GPIO value"); // print error message
        close(value_fd);                    // close value file
        return FAILURE;                     // return with failure
    }

    close(value_fd);     // close value file
    return EXIT_SUCCESS; // return with success
}

// Get GPIO value
int gpio_get_value(const char *gpio_pin)
{
    char value_path[50];                                       // value file path
    sprintf(value_path, "/sys/class/gpio/%s/value", gpio_pin); // create value file path

    int value_fd = open(value_path, O_RDONLY); // open value file
    if (value_fd == FAILURE)                   // check if file open failed
    {
        perror("Error opening value file"); // print error message
        return FAILURE;                     // return with failure
    }

    char buffer[2];                                            // buffer for reading value
    if (read(value_fd, buffer, sizeof(buffer) - 1) == FAILURE) // read value from value file
    {
        perror("Error reading GPIO value"); // print error message
        close(value_fd);                    // close value file
        return FAILURE;                     // return with failure
    }

    buffer[sizeof(buffer) - 1] = '\0'; // terminate buffer string

    close(value_fd);     // close value file
    return atoi(buffer); // return value
}

// Start timer
void start_timer(int frequency)
{
    struct itimerval timer; // timer struct

    // Set the timer interval for frequency
    timer.it_interval.tv_sec = 0;                   // seconds
    timer.it_interval.tv_usec = 500000 / frequency; // microseconds (half period)
    timer.it_interval = timer.it_value;             // set timer interval equal to timer expiration

    // Set signal handler
    signal(SIGALRM, signal_handler);

    // Start timer
    setitimer(ITIMER_REAL, &timer, NULL); // start timer
}

// Stop timer
void stop_timer()
{
    struct itimerval timer; // timer struct

    // Clear the timer
    timer.it_interval.tv_sec = 0;       // seconds
    timer.it_interval.tv_usec = 0;      // microseconds
    timer.it_interval = timer.it_value; // set timer interval equal to timer expiration

    // Stop timer
    setitimer(ITIMER_REAL, &timer, NULL); // stop timer
}
