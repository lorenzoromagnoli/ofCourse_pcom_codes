import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import controlP5.*; 
import java.util.*; 
import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class processing_control_robot extends PApplet {






ControlP5 cp5;

Serial myPort;  // Create object from Serial class
int serialPortNumber=-1;

public void setup() {
  
  cp5 = new ControlP5(this);
  List l = Arrays.asList(Serial.list());
  /* add a ScrollableList, by default it behaves like a DropdownList */
  cp5.addScrollableList("selectSerial")
    .setPosition(20, 20)
    .setSize(200, 100)
    .setBarHeight(20)
    .setItemHeight(20)
    .addItems(l)
    ;

  cp5.addButton("connect")
    .setPosition(240, 20)
    .setHeight(20)
    ;

  cp5.addButton("right")
    .setPosition(230, 197)
    .setImage(loadImage("arrow_right.png"))
    .updateSize();

  cp5.addButton("left")
    .setPosition(70, 197)
    .setImage(loadImage("arrow_left.png"))
    .updateSize();

  cp5.addButton("up")
    .setPosition(150, 120)
    .setImage(loadImage("arrow_up.png"))
    .updateSize();

  cp5.addButton("down")
    .setPosition(150, 275)
    .setImage(loadImage("arrow_down.png"))
    .updateSize();
}

public void draw() {
  background(240);
}

public void selectSerial(int n) {
  println(n);
  serialPortNumber=n;
}

public void connect() {
  if (serialPortNumber !=-1) {
    myPort = new Serial(this, Serial.list()[serialPortNumber], 9600);
  }
}

public void right() {
  myPort.write("r");
}

public void left() {
  myPort.write("l");
}

public void up() {
  myPort.write("f");
}

public void down() {
  myPort.write("b");
}
  public void settings() {  size(400, 400); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "processing_control_robot" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
