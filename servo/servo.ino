/* 
サーボを動かすプログラム
*/

#include <Servo.h>

#define SERVOPIN 8  //D8にサーボ
Servo myServo;

int pos = 68;
int MAX_POS = 0;
int MIN_POS = 68;

void setup() {
  myServo.attach(SERVOPIN);
}

void loop() {
  pos = MAX_POS;
  myServo.write(pos);
  delay(1000);

  pos = MIN_POS;
  myServo.write(pos);
  delay(1000);
}

