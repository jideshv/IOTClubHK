/*
 * Program to learn about PWM
 * Needs:
 * 1 Servo S90
 * LED
 * 220 Ohm Resistor
 * Particle Electron
 * Bread Board
 * Wires (as needed)
 */

int location = 20; // the location for the servo (between 10 and 30 where 20 is the middle)
int max_brightness = 10; // the max brightness you want for the LED (between 0 - 255)
int brightness = 0; // current brightness
int last_step = 0; // last time we changed the brightness
int step_size = 10; // how much to wait between changing brightness by 1 level on ramp up and ramp down

void setup() {
    pinMode(B0, OUTPUT);
    pinMode(C5, OUTPUT);
    Particle.function("command", CommandHandler);
}

void loop() {
    // servo needs 50 hertz signal (20 ms between pulses)
    analogWrite(B0, location, 50);
    
    // calculate the brightness for the light and update
    calcBrightness();
    analogWrite(C5, brightness);
}

void calcBrightness () {
    if ((last_step + step_size) < millis()) {
        if (brightness < max_brightness) {
            brightness++;
        } else if (brightness > max_brightness) {
            brightness--;
        } else {
            brightness = max_brightness;
        }
        last_step = millis();
    }
}

// handles the input from the particle cloud
int CommandHandler (String command) {
  if (command.startsWith("s")) {
    command.remove(0,1);
    location = command.toInt();
    return location;
  } else if (command.startsWith("l")) {
    command.remove(0,1);
    max_brightness = command.toInt();
    return max_brightness;
  }
  return -1;
}
