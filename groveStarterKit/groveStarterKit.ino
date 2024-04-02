//arduinoのgrove kit を動かしてみるためのコード

#include <Servo.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include "Ultrasonic.h"
#include <FastLED.h>

#define numberOfLEDs 10
#define TAPEPIN 8 //D8にLEDテープ

CRGB leds[numberOfLEDs];

rgb_lcd lcd;
Servo groveServo;
Ultrasonic ultrasonic(7); //D7に超音波センサ

const int TouchPin = 2; //D2にTouchSensor
const int ledPin = 3; //D3にledPin
const int buzzerPin = 4; //D4にBuzzer
const int buttonPin = 5; //D5にButton
const int servoPin = 6; //D6にサーボ

const int SoundPin = A0; //A0にSoundsensor
const int TempPin = A1; //A1にtemperatureSensor
const int AnglePin = A2; //A2にAngleSensor
const int threshold = 60;

const int B = 3975;
int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

void setup() {
  Serial.begin(9600);

  pinMode(TouchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  FastLED.addLeds<WS2812B, TAPEPIN, GRB>(leds, numberOfLEDs);
  groveServo.attach(servoPin);
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.print("hello, world!");
  delay(1000);
}

void loop() {
  //センサー
  int touchValue = digitalRead(TouchPin);
  int buttonValue = digitalRead(buttonPin);
  int soundValue = analogRead(SoundPin);
  int val = analogRead(TempPin);
  float resistance = (float)(1023 - val) * 10000 / val;
  float temperatureValue = 1 / (log(resistance / 10000) / B + 1 / 298.15) - 273.15;
  int angleValue = analogRead(AnglePin);
  long ultrasonicValue = ultrasonic.MeasureInCentimeters();


  //  int sensorValue = buttonValue;
  //  int sensorValue =touchValue;
  //  int sensorValue =soundValue;
  //  int sensorValue =temperatureValue;
  long sensorValue = ultrasonicValue;
  //  float sensorValue = angleValue;.
  Serial.println(sensorValue);

  //  LED
  //  if (sensorValue > 1)
  //  {
  //    digitalWrite(ledPin, HIGH);
  //
  //  }
  //  else
  //  {
  //    digitalWrite(ledPin, LOW);
  //  }
  //
  //ブザー
  //  シンプルに音を鳴らす
  if (sensorValue < 30) {
    digitalWrite(buzzerPin, HIGH);
  }
  else {
    digitalWrite(buzzerPin, LOW);
  }

  //  音楽
  //  if (sensorValue > 5)
  //  {
  //    for (int i = 0; i < length; i++)
  //    {
  //      if (notes[i] == ' ')
  //      {
  //        delay(beats[i] * tempo); // rest
  //      }
  //      else
  //      {
  //        playNote(notes[i], beats[i] * tempo);
  //      }
  //      delay(tempo / 2);
  //    }
  //    digitalWrite(buzzerPin, HIGH);
  //  }
  //  else {
  //    digitalWrite(buzzerPin, LOW);
  //  }

  //  サーボモーター


  //  angle sensorの値に応じて動かす
  //  int shaftPosition = map(sensorValue, 0, 1023, 0, 179);
  //  Serial.println(shaftPosition);
  //  groveServo.write(shaftPosition++);
  //  delay(15);

  //  近づいたらサーボモーターを伸ばす
    if (sensorValue < threshold) {
      groveServo.write(2000);
      delay(1000);
    }
    else{
      groveServo.write(1050);
      delay(1000);
  }

  //  Grove_RGB_Backlight_LCD
  //  lcd.setCursor(0, 1);
  //  lcd.print(millis() / 1000);
  //  delay(100);

  // LEDテープ
  if (sensorValue < 50) {
    for (int thisLED = 0; thisLED < numberOfLEDs; thisLED++) {
      leds[thisLED].r = 255 - sensorValue * 5;
      leds[thisLED].g = 0;
      leds[thisLED].b = 0;
      FastLED.show();
    }
  }
  else {
    for (int thisLED = 0; thisLED < numberOfLEDs; thisLED++) {
      leds[thisLED].r = 0;
      leds[thisLED].g = 0;
      leds[thisLED].b = 0;
      FastLED.show();
    }
  }

  delay(10);
}



void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
