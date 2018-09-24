/*
 * Security System
 * Needs:
 * 4 White LEDs
 * 2 LEDs any color
 * 4 100 Ohm resistors
 * 2 3904 NPN Transistors
 * 1 8 Ohm 0.3 watt speaker
 * 1 1N4001 Diode
 * 1 HC-SR505 Motion Sensor
 * 1 push button
 * 1 5V Boost Converter -- Attach the VIN to the side of the breadboard with 3.3 volts from the electron, attach the OUT to the other side of the breadboard to create a 5V rail.
 * Particle Electron
 * Bread Board
 * Wires (as needed)
 */

// Pin Definitions
#define SPEAKER B0
#define MOTION B5
#define LIGHT C0
#define BUTTON D1
#define MOTION_LED D2
#define ARM_LED D3

// Light Related Settings
#define LIGHT_DELAY 10000 // How long the light stays on after motion stops (milliseconds)

// Alarm Related Settings
#define ALARM_TONE_DELAY 300 // How fast the notes switch in the alarm
#define ALARM_NOTES_COUNT 2 // How many notes are in the alarm
int alarm_notes[ALARM_NOTES_COUNT] = {1908, 2551}; // The notes to play using above settings

// Tracking varibles for the alarm player
unsigned long alarm_toggle_time = 0; 
unsigned int current_alarm_note = 0;

// Tracking variables for button behavior
unsigned long last_button_interrupt = 0;

// Tracking variable for light
unsigned long light_on_time = 0;

// Settings for arming system
#define ARM_DELAY 10000

// Tracking variables for arming the system
unsigned long armed_time = 0;
bool alarm_armed = false;
bool alarm_state = false;

void setup() {
 pinMode(SPEAKER, OUTPUT);
 pinMode(MOTION, INPUT_PULLDOWN);
 pinMode(LIGHT, OUTPUT);
 pinMode(BUTTON, INPUT_PULLUP);
 pinMode(MOTION_LED, OUTPUT);
 pinMode(ARM_LED, OUTPUT);
 digitalWrite(ARM_LED, LOW);
 attachInterrupt(BUTTON, arm_button_pressed, RISING);
}

void loop() {
    // check to see if the motion sensor saw something move
    // the function is defined below
    int motion_detected = check_motion_detected();
    
    // if we detect motion run the following
    if (motion_detected == HIGH) {
        if (alarm_armed) { 
            // if the alarm is armed we first check if we are in the delay period
            // basically we try to wait till all motion stops for the delayed amount
            // of time. this lets you leave without setting off the alarm.
            if ((armed_time + ARM_DELAY) < millis()) {
                alarm_state = true; // if the delay period has passed and the system is armed trigger the alarm state
            } else {
                armed_time = millis(); // if motion is detected in the delay period extend the delay
            }
        }
        // if motion is detected turn on the light and keep track of the time
        digitalWrite(LIGHT, HIGH);
        light_on_time = millis();
    }
    
    // if the alarm is turned off then also reset the alarm state to false incase the alarm was already triggered
    if (!alarm_armed) {
        alarm_state = false;
    }
    
    // blink the armed led, see definition below
    blink_armed_led();
    
    // if the alarm_state is true we were armed and there was motion detected
    // sound the alarm!!
    if (alarm_state) {
        // after each tone delay switch the tone to the next one in the list
        if ((alarm_toggle_time + ALARM_TONE_DELAY) < millis()) {
            // if we past the end of the set of tones start from the begining
            if (current_alarm_note == ALARM_NOTES_COUNT) {
                current_alarm_note = 0;
            }
            // play the current note for the alarm
            tone(SPEAKER, alarm_notes[current_alarm_note], 0);
            current_alarm_note++;
            alarm_toggle_time = millis();
        }
    } else {
        // if the alarm_state is false that means the alarm is disabled 
        // stop playing incase the alarm was triggered already.
        noTone(SPEAKER);
    }
    
    // check how long the light has been on since motion was no longer detected
    // if we have passed the delay turn off the light.
    if ((light_on_time + LIGHT_DELAY) < millis()) {
        digitalWrite(LIGHT, LOW);
    }
}

// function to arm the system
// HINT: you could register this with a Particle.function call
// and enable arming from the internet
void arm_alarm () {
    armed_time = millis();
    alarm_armed = true;
}

// fucntion to disarm the system
// HINT: you could register this with a Particle.function call
// and enable disarming from the internet
void disarm_alarm () {
    alarm_armed = false;
}

// Helper variables for keeping track of how the armed light blinks
int arm_led_state = LOW;
unsigned long last_arm_led_change = 0;

// function to blink the armed led
void blink_armed_led () {
    // only blinks the led if the alarm is armed
    if (alarm_armed) {
        // by default we blink using a 2 second period
        int toggle_time = 2000;
        // if we are inside the ARM_DELAY we blink faster
        // to show that the system is waiting for you to leave
        if ((armed_time + ARM_DELAY) > millis()) {
            toggle_time = 200;
        }
        
        // checks the last time and state of the led and toggles
        // it at the toogle_time interval set above.
        if ((last_arm_led_change + toggle_time) < millis()) {
            if (arm_led_state == LOW) {
                arm_led_state = HIGH;
            } else {
                arm_led_state = LOW;
            }
            digitalWrite(ARM_LED, arm_led_state);
            last_arm_led_change = millis();
        }
    } else {
        digitalWrite(ARM_LED, LOW);
    }
}

// this is the function that is called by the interrupt we attached to the button
// We toggle between armed and disarmed.
void arm_button_pressed () {
    if ((last_button_interrupt + 200) < millis()) {
        alarm_armed = !alarm_armed;
        if (alarm_armed) {
            arm_alarm();
        } else {
            disarm_alarm();
        }
        last_button_interrupt = millis();
    }
}

// check if the motion sensor is giving us a high signal
// high signal from this motion sensor means there was motion 
// detected within the last 8 seconds.
int check_motion_detected () {
    // read the sensor pin. by default we pull it low
    // so the sensor will set it high when motion is found.
    int motion_detected = digitalRead(MOTION);
    // there is a motion detected led that we light when motion
    // is detected
    digitalWrite(MOTION_LED, motion_detected);
    return motion_detected;
}
