/*
 * Program to learn how to use an Ultrasound Sensor
 * Needs:
 * 3 LEDs
 * 3 * 360 Ohm resistors
 * HC-SR04+ (3.3v Ultrasound Sensor)
 * Particle Electron
 * Bread Board
 * Wires (as needed)
 *
 * You can find the documentation for the methods we use
 * in this program at:
 * https://docs.particle.io/reference/firmware/electron/
 */

#define RED    B2
#define YELLOW B1
#define GREEN  B0

#define TRIGGER C0
#define ECHO    C1

// We are going to stop using delay()
// as much as possible going forward.
// The loop should return as fast as
// possible. So we keep track of the 
// lastrun and skip running if it 
// hasn't been long enough. Benefit of 
// doing it this way is that the OS
// can do other things vs. waiting
// for us to finish.
unsigned long lastrun = 0;

// Both of these variables are global
// This allows us to tell Particle
// Cloud about them and we can get the
// current values online when we want.
int duration = 0;
int distance = 0;

void setup() {
    pinMode(GREEN, OUTPUT);
    digitalWrite(GREEN, LOW);

    pinMode(YELLOW, OUTPUT);
    digitalWrite(YELLOW, LOW);

    pinMode(RED, OUTPUT);
    digitalWrite(RED, LOW);

    pinMode(TRIGGER, OUTPUT);
    digitalWrite(TRIGGER, LOW);
    
    pinMode(ECHO, INPUT);

    Particle.variable("duration", duration);
    Particle.variable("distance", distance);
}

void loop() {
    // Only run the below code every 500 ms
    if ((lastrun+500) < millis()) {
        // The HC-SR04 needs a 10 microsecond pulse
        // to tell it to make a measurement.
        digitalWrite(TRIGGER, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIGGER, LOW);
        
        // We listen for the response on the ECHO pin
        // The HC-SR04 sends a pulse that tells you 
        // how many microseconds the sound travelled 
        // to the object and back.
        duration = pulseIn(ECHO, HIGH);
        
        // Since the sound went there and back divide by two.
        // Next we multiply by the number of centimeters sound
        // travels per microsecond
        distance = ((duration / 2) * 0.0343);
        
        // Set the LEDs based on the distance we calculated
        if (distance < 20) {
            digitalWrite(GREEN, LOW);
            digitalWrite(YELLOW, LOW);
            digitalWrite(RED, HIGH);
        } else if (distance < 40) {
            digitalWrite(GREEN, LOW);
            digitalWrite(YELLOW, HIGH);
            digitalWrite(RED, LOW);
        } else {
            digitalWrite(GREEN, HIGH);
            digitalWrite(YELLOW, LOW);
            digitalWrite(RED, LOW);
        }
        // remember when we last ran so we can run every 500 ms
        lastrun = millis();
    }
}
