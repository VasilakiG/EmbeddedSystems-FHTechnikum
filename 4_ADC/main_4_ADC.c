/*

* File: main_4_ADC.c

* Name: Vasilaki Gjorgjioski

* Date: 17.1.2024

* Version: 4.0

* Description: This file contains the main application for ADC functionality. The application continuously reads the ADC value, converts it to voltage, and prints the voltage value. The application runs in an infinite loop until it is stopped by pressing CTRL+C or receiving a SIGTERM signal. It includes the "4_adc_control.h" header file for ADC control functions and signal handling.

*/
#include "4_adc_control.h" // GPIO control functions

int main()
{
    // Handle SIGINT
    signal(SIGINT, signal_handler);

    // Handle SIGTERM
    signal(SIGTERM, signal_handler);

    while (!stop_flag)
    {
        // Get ADC value
        int adc_value = ain_get_value();

        // Convert ADC value to voltage
        double voltage = (adc_value * ADC_REF_VOLTAGE) / ADC_MAX_VALUE;

        // Print the voltage value
        printf("ADC Value: %d, Voltage: %.2f V\n", adc_value, voltage);

        // Sleep for 1 second
        sleep(1);
    }

    return EXIT_SUCCESS; // return with success
}