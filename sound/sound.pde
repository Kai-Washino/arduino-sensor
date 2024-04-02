

import processing.serial.*;
import ddf.minim.*;

Serial myPort;
Minim minim;
AudioPlayer song;

String data = "";
String text = "近づいてね";

void setup()
{
  size(850, 600);
  println(Serial.list()); 
  myPort = new Serial(this, Serial.list()[4], 9600);
  delay(100);
  myPort.clear();

  PFont font = createFont("Meiryo", 12);
  textFont(font);
  minim = new Minim( this );
  song = minim.loadFile( "donot_touch.mp3" );
}

void draw() {
  background(255, 255, 255);

  if(data != null) {
    fill(0, 0, 255);
    textSize(28);
    textAlign(CENTER);
    print(data);
    
    text(data, width/2, height/2);
    text(text, width/2, height/2 + 30);
  }
}

void stop()
{
  song.close();
  minim.stop();
  super.stop();
}

void keyPressed()
{
  if ( key == 'p' )
  {
    text = "触らないでね";
    song.play();
  }
}

void serialEvent(Serial myPort) {
  if (myPort.available() > 2) {
    data = myPort.readStringUntil('\n');
  }
}
