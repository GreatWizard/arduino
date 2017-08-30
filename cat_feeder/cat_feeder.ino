#include <Servo.h>

#define MOVE_STEP 1
#define MOVE_DELAY 15
#define DROP_DELAY 300
#define WAIT_DELAY (4 * 3600 * 1000) // 4 hours
#define DEBOUNCE_DELAY 10

Servo servo9, servo10, servo11;
int led = 13, button = 6;

void setup() {
  pinMode(led, OUTPUT);
  servo9.attach(9);
  servo10.attach(10);
  servo11.attach(11);
}

void loop() {
  startMove(servo9);
  startMove(servo10);
  startMove(servo11);
  int waiting = WAIT_DELAY;
  while (digitalRead(button) == 0 || waiting > 0) {
    waiting -= DEBOUNCE_DELAY;
    delay(DEBOUNCE_DELAY);
  }
}

void startMove(Servo servo) {
  // activate led
  digitalWrite(led, HIGH);
  // move to open position
  for (int pos = 0; pos <= 180; pos += MOVE_STEP) {
    moveServo(servo, pos);
  }
  // shake
  for (int i = 0; i <= (DROP_DELAY / MOVE_DELAY); i++) {
    if (i && 1) { // odd
      moveServo(servo, 180);
    } else { // even
      moveServo(servo, 140);
    }
  }
  // move to close position
  for (int pos = 180; pos >= 0; pos -= MOVE_STEP) {
    moveServo(servo, pos);
  }
  // deactivate led
  digitalWrite(led, LOW);
}

void moveServo(Servo servo, int pos) {
  servo.write(pos);
  delay(MOVE_DELAY);
}
