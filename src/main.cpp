#include <BluetoothSerial.h>
#include <ESP32Servo.h>
#include <L298N_MotorDriver.h>

// Servo control wire to GPIO 33
#define servoPin 33

// L298N motor driver
#define dcMotorPin 14     // ENA to GPIO 14
#define dcINPin1 26       // IN1 to GPIO 26
#define dcINPin2 27       // IN2 to GPIO 27

// DC motor direction
#define forward true
#define backward false

BluetoothSerial BT;
L298N_MotorDriver DCmotor(dcMotorPin, dcINPin2, dcINPin1);
Servo steer;


const int speeds[] = {63, 104, 145, 186, 226};      // Motor speeds

void setup() {
  BT.begin("Imperfect Scorpion");

  steer.attach(servoPin);

  DCmotor.setSpeed(speeds[0]);
  DCmotor.setDirection(forward);
}

void loop() {
  if(BT.available()){
    char command = BT.read();

    switch(command){
      case 'F':           // Forward
        steer.write(100);
        DCmotor.enable();
        break;

      case 'R':           // Right
        steer.write(125);
        DCmotor.enable();
        break;

      case 'L':           // Left
        steer.write(75);
        DCmotor.enable();
        break;

      case 'S':           // Stop
        DCmotor.disable();
        break;

      case '1':           // Gear 1
        DCmotor.setSpeed(speeds[0]);
        DCmotor.setDirection(forward);
        break;

      case '2':           // Gear 2
        DCmotor.setSpeed(speeds[1]);
        DCmotor.setDirection(forward);
        break;

      case '3':           // Gear 3
        DCmotor.setSpeed(speeds[2]);
        DCmotor.setDirection(forward);
        break;

      case '4':           // Gear 4
        DCmotor.setSpeed(speeds[3]);
        DCmotor.setDirection(forward);
        break;

      case '5':           // Gear 5
        DCmotor.setSpeed(speeds[4]);
        DCmotor.setDirection(forward);
        break;

      case 'B':           // Reverse
        DCmotor.setSpeed(speeds[1]);
        DCmotor.setDirection(backward);
        break;
    }
  }
}
