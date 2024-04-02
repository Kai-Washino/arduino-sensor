//圧力センサの値からLEDテープの光らせかたを変化する
//もしくは超音波センサからLEDテープの光らせ方を変化する

#include <FastLED.h>

#define numberOfLEDs 10
#define controlPin 5
#define PRESSURE_PIN  1
#define TRIG 3
#define ECHO 2

int pressure_value = 0;
int light_value = 0;
double duration = 0;
double distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25; // 25℃の気温の想定

CRGB leds[numberOfLEDs];

void setup() {
  Serial.begin( 9600 );
  FastLED.addLeds<WS2812B, controlPin, GRB>(leds, numberOfLEDs);

  pinMode(ECHO, INPUT );
  pinMode(TRIG, OUTPUT );
}

void loop() {
//  圧力センサ用のコード
  pressure_value = analogRead(PRESSURE_PIN);
  Serial.println(byte(pressure_value));

//  超音波センサ用のコード
  digitalWrite(TRIG, LOW); 
  delayMicroseconds(2); 
  digitalWrite( TRIG, HIGH );
  delayMicroseconds( 10 ); 
  digitalWrite( TRIG, LOW );
  duration = pulseIn( ECHO, HIGH ); // 往復にかかった時間が返却される[マイクロ秒]

  if (duration > 0) {
    duration = duration / 2; // 往路にかかった時間
    distance = duration * speed_of_sound * 100 / 1000000;
//    Serial.print("Distance:");
//    Serial.println(distance);
//    Serial.println(" cm");
  }

  light_value = pressure_value; // 圧力センサからLEDテープの光らせかたを変化する

//  超音波センサからLEDテープの光らせ方を変化する
//  if(distance > 255){
//    light_value = 255;
//  }
//  else{
//    light_value = distance;
//  }
//  light_value = 255;

  

  for (int thisLED = 0; thisLED < numberOfLEDs; thisLED++) {
    leds[thisLED].r = 255 - light_value;
    leds[thisLED].g = 0;
    leds[thisLED].b = light_value;
    FastLED.show();
  }
  delay(50);


}
