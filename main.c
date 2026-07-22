#include <stdio.h>
#include <pigpio.h>

#define red 17
#define green 27

int main(void){
    int health = 5;

    // Start pigpio library
    if (gpioInitialise() < 0)
    {
        printf("Couldn't intialize pigpio library\n");
        return 1;
    }

    // Set GPIO 17 as an output pin
    gpioSetMode(red, PI_OUTPUT);
    gpioSetMode(green, PI_OUTPUT);


    if (health <= 0){
        gpioWrite(red, PI_HIGH);
        printf("Danger!\n");
    }
    else if (health > 0 && health < 5){
        gpioWrite(green, PI_HIGH);
        printf("Warning!\n");
    }
    else if (health >= 5){
        gpioWrite(green, PI_HIGH);
        printf("Healthy!\n");
    }

    printf("Press ENTER to turn it off\n");

    getchar();
    
    // Turn the LED off before ending
    gpioWrite(red, PI_LOW);
    gpioWrite(green, PI_LOW);

    gpioTerminate();

    return 0;
}