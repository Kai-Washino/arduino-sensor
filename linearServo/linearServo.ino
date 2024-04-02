#include <Servo.h>

Servo myServo;
#define SERVOPIN A2

void setup() {
  myServo.attach(SERVOPIN, 1050, 2000);
  pinMode(SERVOPIN, OUTPUT);
}

void loop() {
  //  writeMicrosecondsでもwriteでも同じ動きする
  
  digitalWrite(SERVOPIN, HIGH);
  myServo.write(2000);
  //  myServo.writeMicroseconds(2000);
  delay(7000);
  myServo.write(1050);
  //  myServo.writeMicroseconds(1050);
  delay(7000);
}
