/*

* File: main_3_GPIO.c

* Name: Vasilaki Gjorgjioski

* Date: 15.12.2023

* Version: 3.0

* Description: This application controls the blinking rate of two LEDs attached to GPIO pins. The user is able to select the blinking frequency by entering the desired value in Hz. The application is stopped by pressing CTRL+C.

*/
#include "3_gpio_control.h" // GPIO control functions

int main()
{
	// Handle SIGINT
	signal(SIGINT, signal_handler);

	// Handle SIGTERM
	signal(SIGTERM, signal_handler);

	// Handle SIGALRM
	signal(SIGALRM, signal_handler);

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

	// Ask user for frequency input
	int frequency;						   // LED blink frequency
	printf("Enter LED blink frequency: "); // prompt user for frequency
	scanf("%d", &frequency);			   // read frequency from stdin

	// Start the timer with the given frequency
	start_timer(frequency);

	while (!stop_flag)
	{
		// Main loop can be empty as the signal handler will handle the LED toggling
	}

	// Cleanup: Stop timer and unexport GPIO pins
	stop_timer(); // Stop timer

	// Unexport GPIO pins
	if (unexport_gpio(GPIO_LED1_PIN) == FAILURE || unexport_gpio(GPIO_LED2_PIN) == FAILURE)
	{
		fprintf(stderr, "Error unexporting GPIO pins\n"); // print error message
		return FAILURE;									  // return with failure
	}

	return EXIT_SUCCESS; // return with success
}