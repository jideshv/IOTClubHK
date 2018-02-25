/*
 * Simple program that turns on an LED when the room is dark.
 * Needs:
 * Photo Diode
 * LED
 * 100K Ohm resistor
 * 220 Ohm resistor
 * Particle Electron
 * Bread Board
 * Wires (as needed)
 */

#define ONBOARD_LED D7
#define WHITE_LED D6
#define PHOTO_DIODE A0

/* Runs only once when device starts */
void setup() {
    // Let us set the pin mode for the onboard LED and white LED 
    // to be output pins. The Electron can source up 
    // to 25 mA per output and a total of 120 mA added together.
    pinMode(WHITE_LED,OUTPUT);
    pinMode(ONBOARD_LED,OUTPUT);
    
    // To start with we will set both LEDs to be off
    digitalWrite(ONBOARD_LED, LOW);
    digitalWrite(WHITE_LED, LOW);
    
    // We can watch the value of the sensor over the USB port
    // which can help us debug the program if we need to.
    Serial.begin(9600);
}

/* Runs over and over again as long as the device is on */
void loop() {
    // Get the value from the photodiode. Basically
    // we get the voltage between a voltage divider
    // that is between the diode and a 100K Ohm resistor
    int sensor_reading = analogRead(PHOTO_DIODE);
    
    // Write to serial output so we can see what the Analog
    // to Digital converter is doing.
    Serial.write("A0 Reading: ");
    Serial.println(sensor_reading);
    
    // If we read over 1000 (about 0.8 volts)
    // we will assume the room is lit.
    if (sensor_reading > 1000) {
        digitalWrite(ONBOARD_LED, HIGH);
        digitalWrite(WHITE_LED, LOW);
    } else { // Anything below 1000 we assume the room is dark
        digitalWrite(ONBOARD_LED, LOW);
        digitalWrite(WHITE_LED, HIGH);
    }
    // We only want to check once a second so let us delay 
    // Why? Because the product manager said so?
    delay(1000);
}
