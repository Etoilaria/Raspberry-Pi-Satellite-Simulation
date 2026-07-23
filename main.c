#include <stdio.h>
#include <pigpio.h>

#define red 17
#define green 27
#define button 23

int main(void){
    // set 3 datasets and set counter
    double voltage[3] = {14, 13, 18};
    double temp[3] = {20, 55, 58};
    double signal[3] = {-80.0, -90.0, -65.0};

    int dataset = 0;

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
    while(1){

        printf("Press the button to test satellite dataset\n");

        // Wait until button is pressed (this is looped until button is pressed)
        while(gpioRead(button) == PI_HIGH){
            gpioDelay(10000); //wait 10 000 microseconds (10 milliseconds) at a time
        }

        gpioDelay(100000); //wait 50 milliseconds to avoid button bounce

        printf("Testing dataset %d\n", (dataset+1));

        // Test dataset
        if ((voltage[dataset] < 10.0 || voltage[dataset] > 17.0) || // under 10V or above 17V
            (temp[dataset] < -20.0 || temp[dataset] > 60.0) || // under -20deg or above 60deg (celsius)
            (signal[dataset] < -105.0)) // under -105dBm
            {
            // turn both LEDs off
            gpioWrite(red, PI_LOW);
            gpioWrite(green, PI_LOW);

            // turn red LED on
            gpioWrite(red, PI_HIGH);
            printf("Danger!\n");
        }
        else if ((voltage[dataset] >= 10.0 && voltage[dataset] <= 12.0) || (voltage[dataset] >= 15.0 && voltage[dataset] <= 17.0) ||
            (temp[dataset] >= -20.0 && temp[dataset] <= 0.0) || (temp[dataset] >= 45.0 && temp[dataset] <= 60.0) ||
            (signal[dataset] >= -105.0 && signal[dataset] <= -85.0))
            {
            // turn both LEDs off
            gpioWrite(red, PI_LOW);
            gpioWrite(green, PI_LOW);

            printf("Warning!\n");

            //flash the red LED 5 times

            for (int i = 0; i < 5; i++){
                gpioWrite(red, PI_HIGH);
                gpioDelay(500000); // keep on for .5 secs
                gpioWrite(red, PI_LOW);
                gpioDelay(500000); // keep on for .5 secs
            }

            gpioWrite(green, PI_HIGH);
        }
        else if ((voltage[dataset] > 12.0 && voltage[dataset] < 15.0) &&
            (temp[dataset] > 0.0 && temp[dataset] < 45.0) &&
            (signal[dataset] > -85.0))
            {
            // turn both LEDs off
            gpioWrite(red, PI_LOW);
            gpioWrite(green, PI_LOW);

            // turn green LED on
            gpioWrite(green, PI_HIGH);
            printf("Healthy!\n");

        }
        while(gpioRead(button) == PI_HIGH){//wait for button release
            gpioDelay(10000); //wait 10 000 microseconds (10 milliseconds) at a time
        }
        
        gpioDelay(100000); 
        dataset++;

        if (dataset == 3){dataset = 0;}
    }

    printf("Press ENTER to turn LEDs off\n");
    getchar();
    
    // Turn the LED off before ending
    gpioWrite(red, PI_LOW);
    gpioWrite(green, PI_LOW);

    gpioTerminate();

    return 0;
}