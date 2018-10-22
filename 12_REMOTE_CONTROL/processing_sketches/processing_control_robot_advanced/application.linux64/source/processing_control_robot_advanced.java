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

public class processing_control_robot_advanced extends PApplet {






ControlP5 cp5;

Serial myPort;  // Create object from Serial class
int serialPortNumber=-1;

int movementAmount=0;
int rotationAmount=0;

boolean connected=false;

public void setup() {
  
  cp5 = new ControlP5(this);
  List l = Arrays.asList(Serial.list());
  /* add a ScrollableList, by default it behaves like a DropdownList */

  cp5.addSlider("movement_amount")
    .setRange(1, 1000)
    .setValue(100)
    .setPosition(20, 60)
    .setSize(200, 20)
    ;

  cp5.addSlider("rotation_amount")
    .setRange(1, 1000)
    .setValue(100)
    .setPosition(20, 90)
    .setSize(200, 20)
    ;

  cp5.addScrollableList("selectSerial")
    .setPosition(20, 20)
    .setSize(200, 100)
    .setBarHeight(20)
    .setItemHeight(20)
    .addItems(l)
    ;

  cp5.addButton("connect")
    .setPosition(270, 20)
    .setHeight(20)
    ;

  cp5.addButton("turn_right")
    .setPosition(155, 200)
    .updateSize();

  cp5.addButton("turn_left")
    .setPosition(20, 200)
    .updateSize();

  cp5.addButton("move_forward")
    .setPosition(88, 150)
    .updateSize();

  cp5.addButton("move_backward")
    .setPosition(88, 250)
    .updateSize();

  cp5.addButton("penUp")
    .setPosition(270, 150)
    .updateSize();

  cp5.addButton("penDown")
    .setPosition(270, 250)
    .updateSize();
}

public void draw() {
  background(0, 0, 30);
  if (connected) {
    if ( myPort.available() > 0) {  // If data is available,
      print( PApplet.parseChar(myPort.read()));         // read it and store it in val
    }
  }
}

public void selectSerial(int n) {
  println(n);
  serialPortNumber=n;
}

public void connect() {
  if (serialPortNumber !=-1) {
    myPort = new Serial(this, Serial.list()[serialPortNumber], 9600);
    connected=true;
  }
}

public void turn_right() {
  sendCommand('r', rotationAmount);
}

public void turn_left() {
  sendCommand('l', rotationAmount);
}

public void move_forward() {
  sendCommand('f', movementAmount);
}

public void move_backward() {
  sendCommand('b', movementAmount);
}

public void penUp() {
  sendCommand('p', 0);
}
public void penDown() {
  sendCommand('p', 1);
}

public void sendCommand(char command, int value) {
  String s=""+command+'_'+value+'\n';
  myPort.write(s);
  print(s);
}


public void movement_amount(int n) {
  movementAmount=n;
}

public void rotation_amount(int n) {
  rotationAmount=n;
}
  public void settings() {  size(400, 400); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "processing_control_robot_advanced" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
