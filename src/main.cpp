#include <BluetoothSerial.h>
#include <ESP32Servo.h>
#include <L298N_MotorDriver.h>

// Servo control wire to GPIO 33
#define servoPin 25

// L298N motor driver
#define dcMotorPin 14     // ENA to GPIO 14
#define dcINPin1 27       // IN1 to GPIO 26
#define dcINPin2 26       // IN2 to GPIO 27

// Obstacle Sensor
#define IR_R 32           // Right IR Sensor
#define IR_L 33           // Left IR Sensor
#define trigPin 17        // Ultrasonic Trigger
#define echoPin 16        // Ultrasonic Echo

// Thresholds
#define SAFE_DISTANCE 20
#define IR_DETECTED LOW

// DC motor direction
#define forward true
#define backward false

void manual(char command);
void autoavoid();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
long getDistance();

BluetoothSerial BT;
L298N_MotorDriver DCmotor(dcMotorPin, dcINPin2, dcINPin1);
Servo steer;

const int speeds[] = {100, 140, 178, 216, 255};              // Motor speeds
int currentSpeed;
bool automatic = true;

void setup(){
  BT.begin("Imperfect Scorpion");
  steer.attach(servoPin);

  // Sensor Pins
  pinMode(IR_R, INPUT);
  pinMode(IR_L, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop(){
  while(BT.available()){
    char command = BT.read();

    if(command == 'A') automatic = true;
    if(command == 'M') automatic = false;

    if (automatic) {
      autoavoid();
    }
    else {
      manual(command);
    } 
  }
}

void manual(char command){
  switch(command){
    case 'C': steer.write(100); break;       // Center steering wheel
    case 'R': steer.write(125); break;       // Right steering wheel
    case 'L': steer.write(75); break;        // Left steering wheel
    case 'F':                                // Move forward
      DCmotor.setDirection(forward);
      DCmotor.enable();
      break;

    case 'S': DCmotor.disable(); break;      // Stop
    case 'B':                                // Move backward
      DCmotor.setDirection(backward);
      DCmotor.enable();
      break;

    case '1': DCmotor.setSpeed(speeds[0]); break;          // Gear 1
    case '2': DCmotor.setSpeed(speeds[1]); break;          // Gear 2
    case '3': DCmotor.setSpeed(speeds[2]); break;          // Gear 3
    case '4': DCmotor.setSpeed(speeds[3]); break;          // Gear 4
    case '5': DCmotor.setSpeed(speeds[4]); break;          // Gear 5

    default: break;
  }
}

void autoavoid(){
  long distance = getDistance();
  bool leftObstacle = digitalRead(IR_L) == IR_DETECTED;
  bool rightObstacle = digitalRead(IR_R) == IR_DETECTED;

  if (distance < SAFE_DISTANCE || leftObstacle || rightObstacle) {
    DCmotor.disable(); // Stop first

    if (distance < SAFE_DISTANCE) { // Obstacle in front
      moveBackward();
      delay(1000);
      if(rightObstacle) turnLeft();
      if(leftObstacle) turnRight();
    } else if (leftObstacle) { // Obstacle on the left
      moveBackward();
      turnRight();
    } else if (rightObstacle) { // Obstacle on the right
      moveBackward();
      turnLeft();
    }
  } else {
    moveForward();
  }

  delay(100); // Short delay for stability
}

void moveForward(){
  DCmotor.setSpeed(speeds[0]);
  steer.write(100);
  DCmotor.setDirection(forward);
  DCmotor.enable();
}

void moveBackward(){
  DCmotor.setSpeed(speeds[0]);
  steer.write(100);
  DCmotor.setDirection(backward);
  DCmotor.enable();
}

void turnLeft(){
  DCmotor.setSpeed(speeds[0]);
  DCmotor.setDirection(forward);
  DCmotor.enable();
  steer.write(75);
}

void turnRight(){
  DCmotor.setSpeed(speeds[0]);
  DCmotor.setDirection(forward);
  DCmotor.enable();
  steer.write(125);
}

long getDistance(){
  // Send Trigger Signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure Echo Time
  long duration = pulseIn(echoPin, HIGH);

  // Calculate Distance (cm)
  return duration * 0.034 / 2;
}
