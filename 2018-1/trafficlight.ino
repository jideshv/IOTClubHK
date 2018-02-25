/*
 * Simple program that simulates a traffic light.
 * Needs:
 * Red, Yellow, and Green LEDs
 * 3 * 360 Ohm resistors
 * Particle Electron
 * Bread Board
 * Wires (as needed)
 */

#define RED D0
#define YELLOW D1
#define GREEN D2

/* Runs only once when device starts */
void setup() {
    // Let us set the pin mode for the three LEDs 
    // to be output pins. The Electron can source up 
    // to 25 mA per output and a total of 120 mA added together.
    pinMode(RED,OUTPUT);
    pinMode(YELLOW,OUTPUT);
    pinMode(GREEN,OUTPUT);
    
    // To start with we will set only the red LED to be on
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
}

/* Runs over and over again as long as the device is on */
void loop() {
    // Switch the red light on for 5 seconds
    digitalWrite(RED, HIGH);
    delay(5000);
    digitalWrite(RED, LOW);
    
    // Uncomment the below if you want the Hong Kong style
    // yellow before green.
    // Switch the yellow light on for 750 milliseconds
    //digitalWrite(YELLOW, HIGH);
    //delay(750);
    //digitalWrite(YELLOW, LOW);

    // Switch the green light on for 5 seconds
    digitalWrite(GREEN, HIGH);
    delay(5000);
    digitalWrite(GREEN, LOW);
    
    // Switch the yellow light on for 2 seconds
    digitalWrite(YELLOW, HIGH);
    delay(2000);
    digitalWrite(YELLOW, LOW);
}
