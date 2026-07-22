#include <stdio.h>
#include <pigpio.h>

#define red 17
#define green 27
#define button 23

int main(void){
    double voltage, temp, signal;

    voltage = 14.0;
    temp = 55.0;
    signal = -80.0;

    // Start pigpio library
    if (gpioInitialise() < 0)
    {
        printf("Couldn't initialize pigpio library\n");
        return 1;
    }

    // Set GPIO pins as output for red and green LEDs
    gpioSetMode(red, PI_OUTPUT);
    gpioSetMode(green, PI_OUTPUT);

    // Set GPIO pin as input for the button
    gpioSetMode(button, PI_INPUT);

    // when button isn't pressed, it is set as HIGH
    gpioSetPullUpDown(button, PI_PUD_UP);

    // turn both LEDs off
    gpioWrite(red, PI_LOW);
    gpioWrite(green, PI_LOW);

    printf("Press the button to test satellite dataset\n");

    // Wait until button is pressed (this is looped until button is pressed)
    while(gpioRead(button) == PI_HIGH){
        gpioDelay(10000); //wait 10 000 microseconds (10 milliseconds) at a time
    }

    gpioDelay(50000); //wait 50 milliseconds to avoid button bounce

    // Test dataset
    if ((voltage < 10.0 || voltage > 17.0) || // under 10V or above 17V
        (temp < -20.0 || temp > 60.0) || // under -20deg or above 60deg (celsius)
        (signal < -105.0)) // under -105dBm
        {
        // turn both LEDs off
        gpioWrite(red, PI_LOW);
        gpioWrite(green, PI_LOW);

        // turn red LED on
        gpioWrite(red, PI_HIGH);
        printf("Danger!\n");
    }
    else if ((voltage >= 10.0 && voltage <= 12.0) || (voltage >= 15.0 && voltage <= 17.0) ||
        (temp >= -20.0 && temp <= 0.0) || (temp >= 45.0 && temp <= 60.0) ||
        (signal >= -105.0 && signal <= -85.0))
        {
        // turn both LEDs off
        gpioWrite(red, PI_LOW);
        gpioWrite(green, PI_LOW);

        // turn green LED on
        gpioWrite(green, PI_HIGH);
        printf("Warning!\n");
    }
    else if ((voltage > 12.0 && voltage < 15.0) &&
        (temp > 0.0 && temp < 45.0) &&
        (signal > -85.0))
        {
        // turn both LEDs off
        gpioWrite(red, PI_LOW);
        gpioWrite(green, PI_LOW);

        // turn green LED on
        gpioWrite(green, PI_HIGH);
        printf("Healthy!\n");
    }

    printf("Press ENTER to turn LEDs off\n");
    getchar();
    
    // Turn the LED off before ending
    gpioWrite(red, PI_LOW);
    gpioWrite(green, PI_LOW);

    gpioTerminate();

    return 0;
}