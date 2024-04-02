//圧力センサの基本的なコード

const int PRESSURE_PIN = 1;
int pressure_value = 0;
void setup() {
  Serial.begin( 9600 );
}

void loop() {
  pressure_value = analogRead(PRESSURE_PIN);
  Serial.println(byte(pressure_value));
  delay(50);
}
