#include "SignalGenerator.h"

DigitalPin REAL_PIN = 5;
DigitalPin IMAGINARY_PIN = 7;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  SignalGenerator generator(SignalType::COMPLEX, Timer::T1, REAL_PIN, IMAGINARY_PIN);
  generator.print();
}

void loop() {
  // put your main code here, to run repeatedly:

  // Some possible helpful websites:
  // https://forum.arduino.cc/index.php?topic=156330.0 - (how to generate 2/3 PWM signals by 90/120 deg out of phase using 2/3 timers)
  // https://playground.arduino.cc/Main/TimerPWMCheatsheet - Pins and frequencies associated with each timer for PWM
}
