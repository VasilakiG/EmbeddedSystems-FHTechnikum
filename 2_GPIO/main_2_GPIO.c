/*

* File: main_2_GPIO.c

* Name: Vasilaki Gjorgjioski

* Date: 15.12.2023

* Version: 2.0

* Description: This application controls the blinking rate of two LEDs attached to GPIO pins. The user is able to select the blinking frequency by entering the desired value in Hz. The application is stopped by pressing CTRL+C.

*/
#include "2_gpio_control.h" // GPIO control functions

int main()
{
	// Handle SIGINT
	signal(SIGINT, signal_handler);

	// Handle SIGTERM
	signal(SIGTERM, signal_handler);

	// Export GPIO pins
	if (export_gpio(GPIO_LED1_PIN) == FAILURE || export_gpio(GPIO_LED2_PIN) == FAILURE)
	{
		fprintf(stderr, "Error exporting GPIO pins\n"); // print error message
		return FAILURE;									// return with failure
	}

	// Set GPIO direction (Assuming 'out' for LEDs)
	if (gpio_set_dir(GPIO_LED1_PIN, "out") == FAILURE || gpio_set_dir(GPIO_LED2_PIN, "out") == FAILURE)
	{
		fprintf(stderr, "Error setting GPIO direction\n"); // print error message
		return FAILURE;									   // return with failure
	}

	// Toggle LEDs until SIGINT is received
	while (!stop_flag)
	{
		int frequency;						   // LED blink frequency
		printf("Enter LED blink frequency: "); // prompt user for frequency
		scanf("%d", &frequency);			   // read frequency from stdin

		// Toggle LEDs at the specified frequency
		gpio_set_value(GPIO_LED1_PIN, 1); // Turn LED1 ON
		gpio_set_value(GPIO_LED2_PIN, 0); // Turn LED2 OFF

		usleep(1000000 / (2 * frequency)); // Sleep half of the period

		gpio_set_value(GPIO_LED1_PIN, 0); // Turn LED1 OFF
		gpio_set_value(GPIO_LED2_PIN, 1); // Turn LED2 ON

		usleep(1000000 / (2 * frequency)); // Sleep half of the period
	}

	// Unexport GPIO pins
	if (unexport_gpio(GPIO_LED1_PIN) == FAILURE || unexport_gpio(GPIO_LED2_PIN) == FAILURE)
	{
		fprintf(stderr, "Error unexporting GPIO pins\n"); // print error message
		return FAILURE;									  // return with failure
	}

	return EXIT_SUCCESS; // return with success
}