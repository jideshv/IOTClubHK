/*
 * Program to learn about buttons and bounce
 * Needs:
 * 1 Push Button
 * Particle Electron
 * Bread Board
 * Wires (as needed)
 */
 
int sum = 0;

void setup() {
    Particle.variable("sum", sum);
    Particle.function("reset", resetSum);
    
    pinMode(C0, INPUT_PULLUP);
    attachInterrupt(C0, count, RISING);
    //attachInterrupt(C0, count_debounce, RISING);
}

void loop() {

}

int resetSum(String command) {
    sum = 0;
    return 0;
}

void count() {
    sum++;
}

unsigned long last_interrupt = 0;

void count_debounce() {
    if ((last_interrupt + 150) < millis()) {
        sum++;
    }
    last_interrupt = millis();
}
