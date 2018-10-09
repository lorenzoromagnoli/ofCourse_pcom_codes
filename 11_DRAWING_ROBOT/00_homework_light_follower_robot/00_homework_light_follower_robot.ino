/*
 * Code to drive a two wheels robot car so that it always 
 * tries to go towards the light source. 
 * It used 4 LDR sensors so that it can decide to move back and forward. 
 * 
 * 
   SENSOR PLACEMENT

         robot front

       1-A0   |   2-A1
              |
   -----------|------------
              |
       3-A2   |   4-A3

         robot back
*/

int lightSensor1 = A0;
int lightSensor2 = A1;
int lightSensor3 = A2;
int lightSensor4 = A3;

// array to store the sensor readings
int sensorValues[4];

// array to store which sensor is in light and which is in shadow
boolean sensorInLight[4];

//if two sensor readings are less that sameValueTresholds apart 
//they are considered either both in light or either both in shadows
int sameValueTresholds = 50;   

void setup() {
  Serial.begin (9600);
  setRobotSpeed(100);
}

void loop() {
  readSensorValues();
  checkSensorsInLight();
  printSensorValues();
  decideMovement();
}


void printSensorValues() {
  for (int i = 0; i < 4; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }

  for (int i = 0; i < 4; i++) {
    Serial.print(sensorInLight[i]);
    Serial.print('\t');
  }
  Serial.println();
}

void readSensorValues() {
  sensorValues[0] = analogRead(lightSensor1);
  sensorValues[1] = analogRead(lightSensor2);
  sensorValues[2] = analogRead(lightSensor3);
  sensorValues[3] = analogRead(lightSensor4);
}

void checkSensorsInLight() {
  
  //find the sensor which is receiving most light
  int heighestIndex = 0;
  for (int i = 0; i < 4; i++) {
    if (sensorValues[i] > sensorValues[heighestIndex]) {
      heighestIndex = i;
    }
  }
  
  //find which other sensor is receiving a similar amount of light and 
  //which one instead is in shadow and update the sensorInLight array.
  for (int i = 0; i < 4; i++) {
    if (sensorValues[heighestIndex] - sensorValues[i] < sameValueTresholds) {
      sensorInLight[i] = true;
    } else {
      sensorInLight[i] = false;
    }
  }
}

//depending on which sensor is in light and which not decide what movement to do.
void decideMovement() {
  if (sensorInLight[0] && sensorInLight[1] && sensorInLight[2] && sensorInLight[3]) {
    stopRobot();

  } else if (sensorInLight[0] && sensorInLight[1] && !sensorInLight[2] && !sensorInLight[3]) {
    moveForward();

  } else if (!sensorInLight[0] && !sensorInLight[1] && sensorInLight[2] && sensorInLight[3]) {
    moveBackward();

  } else if ((sensorInLight[0] && !sensorInLight[1] && !sensorInLight[2] && !sensorInLight[3])
             || (!sensorInLight[0] && !sensorInLight[1] && !sensorInLight[2] && sensorInLight[3])
             || (sensorInLight[0] && !sensorInLight[1] && sensorInLight[2] && !sensorInLight[3])
             || (sensorInLight[0] && sensorInLight[1] && sensorInLight[2] && !sensorInLight[3])
             || (!sensorInLight[0] && sensorInLight[1] && sensorInLight[2] && sensorInLight[3])

            ) {
    
    turnLeft();

  } else if ((!sensorInLight[0] && sensorInLight[1] && !sensorInLight[2] && !sensorInLight[3])
             || (!sensorInLight[0] && sensorInLight[1] && !sensorInLight[2] && sensorInLight[3])
             || (!sensorInLight[0] && !sensorInLight[1] && sensorInLight[2] && !sensorInLight[3])           
             || (sensorInLight[0] && !sensorInLight[1] && sensorInLight[2] && sensorInLight[3])
             || (sensorInLight[0] && sensorInLight[1] && !sensorInLight[2] && sensorInLight[3])
            ) {
              
    turnRight();
  }
}


