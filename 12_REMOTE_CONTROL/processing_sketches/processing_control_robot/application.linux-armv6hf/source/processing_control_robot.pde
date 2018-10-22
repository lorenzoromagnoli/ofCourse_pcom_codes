import controlP5.*;
import java.util.*;
import processing.serial.*;


ControlP5 cp5;

Serial myPort;  // Create object from Serial class
int serialPortNumber=-1;

void setup() {
  size(400, 400);
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

void draw() {
  background(240);
}

void selectSerial(int n) {
  println(n);
  serialPortNumber=n;
}

void connect() {
  if (serialPortNumber !=-1) {
    myPort = new Serial(this, Serial.list()[serialPortNumber], 9600);
  }
}

void right() {
  myPort.write("r");
}

void left() {
  myPort.write("l");
}

void up() {
  myPort.write("f");
}

void down() {
  myPort.write("b");
}
