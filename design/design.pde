//データの値を表示するorデータ次第で表示の文字を変えるだけのシンプルなコード

import processing.serial.*;
Serial myPort;

String data = "";
String text = "近づいてね";

void setup() {
  size(850, 600);
  println(Serial.list()); 
  myPort = new Serial(this, Serial.list()[4], 9600);
  delay(100);
  myPort.clear();

  PFont font = createFont("Meiryo", 12);
  textFont(font);
}

void draw() {
  background(255, 255, 255);

  ////センサ値をそのまま表示///////////////////
  if (data != null) {
    fill(0, 0, 255);
    textSize(28);
    textAlign(CENTER);
    print(data);
    if (data == null) {
      data = "0";
    } else {
      text(data, width/2, height/2);
    }
  }
  //////////////////////////////////////////////

  ////文字を表示///////////////////////////////
  //if (data != null) {
  //  if (int(data) > 100) {
  //    text = "近づいてね";
  //  } else {
  //    text = "触らないでね";
  //  }
  //  fill(0, 0, 255);
  //  textSize(28);
  //  textAlign(CENTER);
  //  text(text,  width/2, height/2);
  //}
  //////////////////////////////////////////////
}



void serialEvent(Serial myPort) {
  if (myPort.available() > 2) {
    data = myPort.readStringUntil('\n');
  }
}
