#include <BluetoothSerial.h>
#include <ESP32Servo.h>
#include <L298N_MotorDriver.h>

// Servo control wire to GPIO 33
#define servoPin 25

// L298N motor driver
#define dcMotorPin 14     // ENA to GPIO 14
#define dcINPin1 27       // IN1 to GPIO 26
#define dcINPin2 26       // IN2 to GPIO 27

// DC motor direction
#define forward true
#define backward false

void manual();
void autoavoid();

BluetoothSerial BT;
L298N_MotorDriver DCmotor(dcMotorPin, dcINPin2, dcINPin1);
Servo steer;

const int speeds[] = {100, 140, 178, 216, 255};              // Motor speeds
bool automatic = false;

void setup(){
  BT.begin("Imperfect Scorpion");
  steer.attach(servoPin);
}

void loop(){
  if (automatic) ;
  if (!automatic) manual();
}

void manual()}{
  while(BT.available()){
  char command = BT.read();

  switch(command){
    case 'C':           // Center steering wheel
      steer.write(100);
      break;

    case 'R':           // Right steering wheel
      steer.write(125);
      break;

    case 'L':           // Left steering wheel
      steer.write(75);
      break;

    case 'F':           // Move forward
      DCmotor.setDirection(forward);
      DCmotor.enable();
      break;

    case 'S':           // Stop
      DCmotor.disable();
      break;

    case 'B':           // Move facward
      DCmotor.setDirection(backward);
      DCmotor.enable();

    case '1':           // Gear 1
      DCmotor.setSpeed(speeds[0]);
      break;

    case '2':           // Gear 2
      DCmotor.setSpeed(speeds[1]);
      break;

    case '3':           // Gear 3
      DCmotor.setSpeed(speeds[2]);
      break;

    case '4':           // Gear 4
      DCmotor.setSpeed(speeds[3]);
      break;

    case '5':           // Gear 5
      DCmotor.setSpeed(speeds[4]);
      break;
    }
  }
}

void autoavoid(){
  
} 
