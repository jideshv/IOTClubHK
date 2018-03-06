/*
 * Program to learn about capacitors
 * Needs:
 * 2 LEDs
 * 3 * 360 Ohm resistors
 * Particle Electron
 * Bread Board
 * Wires (as needed)
 * 10000 uF Capacitor
 */

#define LED1 B0
#define LED2 B2

/* Runs only once when device starts */
void setup() {
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    // Sends a 25 hertz PWM square wave
    // we will smooth this out by adding
    // the capacitor.
    tone(LED1,25);
    digitalWrite(LED2,HIGH);
}

/* Runs over and over again as long as the device is on */
void loop() {
    
}
