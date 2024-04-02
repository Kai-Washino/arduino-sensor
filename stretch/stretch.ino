
const int stretchPin = A0;

void setup() {
  Serial.begin(9600);ss
}

void loop() {
  int stretchValue = analogRead(stretchPin);
  int sensorValue = stretchValue;
  Serial.println(sensorValue);
}
