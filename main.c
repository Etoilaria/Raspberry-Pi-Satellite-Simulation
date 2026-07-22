#include <stdio.h>
#include <pigpio.h>

#define red 17
#define green 27

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

    // Make sure LEDs are off
    gpioWrite(red, PI_LOW);
    gpioWrite(green, PI_LOW);


    if ((voltage < 10.0 || voltage > 17.0) || // under 10V or above 17V
        (temp < -20.0 || temp > 60.0) || // under -20deg or above 60deg (celsius)
        (signal < -105.0)) // under -105dBm
        {
        gpioWrite(red, PI_HIGH);
        printf("Danger!\n");
    }
    else if ((voltage >= 10.0 && voltage <= 12.0) || (voltage >= 15.0 && voltage <= 17.0) ||
        (temp >= -20.0 && temp <= 0.0) || (temp >= 45.0 && temp <= 60.0) ||
        (signal >= -105.0 && signal <= -85.0))
        {
        gpioWrite(green, PI_HIGH);
        printf("Warning!\n");
    }
    else if ((voltage > 12.0 && voltage < 15.0) &&
        (temp > 0.0 && temp < 45.0) &&
        (signal > -85.0))
        {
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