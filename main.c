#include <stdio.h>
#include <pigpio.h>

#define red 17

int main(void){
    char key;

    // Start pigpio library
    if (gpioInitialise() < 0)
    {
        printf("Couldn't intialize pigpio library\n");
        return 1;
    }

    // Set GPIO 17 as an output pin
    gpioSetMode(red, PI_OUTPUT);

    // Turn on LED
    gpioWrite(red, PI_HIGH);

    printf("Red LED on!\n");
    printf("Press ENTER to turn it off\n");

    key = getchar();
    
    // Turn the LED off before ending
    gpioWrite(red, PI_LOW);

    gpioTerminate();

    printf("Red LED off!");

    return 0;
}