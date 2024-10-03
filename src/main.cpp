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

const float ratio = 6/12.8;                                 // 6v/12.8v for voltage ratio | DC motor Vrate = 6v ; Voltage after voltage drop = 12.8
const int speeds[] = {63, 104, 145, 186, 226};              // Motor speeds
const int scaledSpeeds[] = {  (int)(speeds[0] * ratio),     // Scaled speeds for 12v power supply
                              (int)(speeds[1] * ratio),
                              (int)(speeds[2] * ratio),
                              (int)(speeds[3] * ratio),
                              (int)(speeds[4] * ratio),
};

void setup(){
  BT.begin("Imperfect Scorpion");

  steer.attach(servoPin);
}

void loop(){
  if(BT.available()){
    char command = BT.read();

    switch(command){
      case 'C':           // Center
        steer.write(100);
        break;

      case 'R':           // Right
        steer.write(125);
        break;

      case 'L':           // Left
        steer.write(75);
        break;

      case 'M':           // Move
        DCmotor.enable();

      case 'S':           // Stop
        DCmotor.disable();
        break;

      case '1':           // Gear 1
        DCmotor.setSpeed(scaledSpeeds[0]);
        DCmotor.setDirection(forward);
        break;

      case '2':           // Gear 2
        DCmotor.setSpeed(scaledSpeeds[1]);
        DCmotor.setDirection(forward);
        break;

      case '3':           // Gear 3
        DCmotor.setSpeed(scaledSpeeds[2]);
        DCmotor.setDirection(forward);
        break;

      case '4':           // Gear 4
        DCmotor.setSpeed(scaledSpeeds[3]);
        DCmotor.setDirection(forward);
        break;

      case '5':           // Gear 5
        DCmotor.setSpeed(scaledSpeeds[4]);
        DCmotor.setDirection(forward);
        break;

      case 'B':           // Reverse
        DCmotor.setSpeed(scaledSpeeds[1]);
        DCmotor.setDirection(backward);
        break;
    }
  }
}
