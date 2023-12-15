/*

* File: 3_gpio_control.h

* Name: Vasilaki Gjorgjioski

* Date: 15.12.2023

* Version: 3.0

* Description: This header file contains the definitions and function declarations for controlling GPIO pins. It provides functions for exporting and unexporting GPIO pins, setting their direction, setting their value, and getting their value. It also defines constants for the paths of GPIO export and unexport files, as well as constants for GPIO pin numbers.

*/
#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"
#define GPIO_UNEXPORT_PATH "/sys/class/gpio/unexport"
#define TRUE 1
#define FAILURE -1

#define GPIO_LED1_PIN "87" // GPIO pin for LED1
#define GPIO_LED2_PIN "89" // GPIO pin for LED2

// #include "gpio_control.h" // GPIO control functions
#include <stdio.h>    // Standard input-output functions (printf, scanf)
#include <stdlib.h>   // Standard library functions (exit)
#include <signal.h>   // Signal handling functions (signal)
#include <unistd.h>   // UNIX standard functions (usleep)
#include <fcntl.h>    // File control functions (open, close)
#include <string.h>   // String manipulation functions (strlen)
#include <sys/time.h> // Time functions (gettimeofday)

extern volatile sig_atomic_t stop_flag; // stop flag
extern volatile int led_state;          // Global variable to keep track of the LED state

// Function declarations
void signal_handler(int signal);
int export_gpio(const char *gpio_pin);
int unexport_gpio(const char *gpio_pin);
int gpio_set_dir(const char *gpio_pin, const char *direction);
int gpio_set_value(const char *gpio_pin, int value);
int gpio_get_value(const char *gpio_pin);
// New functions
void start_timer(int frequency);
void stop_timer();

#endif // GPIO_CONTROL_H
