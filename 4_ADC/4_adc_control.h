/*

* File: 4_adc_control.h

* Name: Vasilaki Gjorgjioski

* Date: 17.1.2024

* Version: 4.0

* Description: This header file contains the definitions and function declarations for ADC. It defines the path to the ADC device file, maximum value for a 12-bit ADC, reference voltage for the ADC, and other constants. It also includes necessary libraries and declares a signal handler function and a function for reading the ADC value.

*/
#pragma once

#define ADC_PATH "/sys/bus/iio/devices/iio:device0"
#define ADC_MAX_VALUE 4095  // Maximum value for a 12-bit ADC
#define ADC_REF_VOLTAGE 1.8 // Reference voltage for the ADC
#define TRUE 1
#define FAILURE -1
#define BUFFERSIZE 10 // Buffer size for reading the ADC value, 10 characters are enough for 4 digits

// INCLUDES
#include <stdio.h>  // Standard input-output functions (printf, scanf)
#include <stdlib.h> // Standard library functions (exit)
#include <signal.h> // Signal handling functions (signal)
#include <unistd.h> // UNIX standard functions (usleep)
#include <fcntl.h>  // File control functions (open, close)

extern volatile sig_atomic_t stop_flag; // stop flag

// Function declarations
void signal_handler(int signal);
int ain_get_value();
