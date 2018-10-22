import controlP5.*;
import java.util.*;
import processing.serial.*;


ControlP5 cp5;

Serial myPort;  // Create object from Serial class
int serialPortNumber=-1;

int movementAmount=0;
int rotationAmount=0;

boolean connected=false;

void setup() {
  size(400, 400);
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

void draw() {
  background(0, 0, 30);
  if (connected) {
    if ( myPort.available() > 0) {  // If data is available,
      print( char(myPort.read()));         // read it and store it in val
    }
  }
}

void selectSerial(int n) {
  println(n);
  serialPortNumber=n;
}

void connect() {
  if (serialPortNumber !=-1) {
    myPort = new Serial(this, Serial.list()[serialPortNumber], 9600);
    connected=true;
  }
}

void turn_right() {
  sendCommand('r', rotationAmount);
}

void turn_left() {
  sendCommand('l', rotationAmount);
}

void move_forward() {
  sendCommand('f', movementAmount);
}

void move_backward() {
  sendCommand('b', movementAmount);
}

void penUp() {
  sendCommand('p', 0);
}
void penDown() {
  sendCommand('p', 1);
}

void sendCommand(char command, int value) {
  String s=""+command+'_'+value+'\n';
  myPort.write(s);
  print(s);
}


void movement_amount(int n) {
  movementAmount=n;
}

void rotation_amount(int n) {
  rotationAmount=n;
}
