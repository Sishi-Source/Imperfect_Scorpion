# Imperfect Scorpion
## Materials
1. RC Car Toy
2. ESP32 Dev Module
3. Servo Motor
4. DC Motor (if RC Car's DC motor don't work)
5. L298N Motor Driver Module
6. 18650 Lithium-ion Batteries and Battery Holder

---

## Steps
> [!NOTE]
> Provided steps are not specific as the RC Car Toy you have might be different from the one I used. Read the steps first before doing it yourself.
- **Step 1:** Disassemble the RC Car Toy
- **Step 2:** Replace the steering DC motor with servo motor.
- **Step 3(Optional):** Add a surface for all the components' base if there's not enough room in your RC Car Toy.
- **Step 4:** Connect the positive wire of the battery holder to 12v (VS) terminal in L298N Motor Driver then connect the negative wire to the GND terminal in the L298N. Make sure to consider the voltage rate of your DC motor and your power supply satisfies the requirement. Learn [L298N](https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/)
	![Battery to L298N](diagrams/sceenshots/battery_to_L298N.png)
- **Step 5:** Connect the servo motor's power (positive) wire to L298N's 5v (VSS) terminal, negative wire to L298N' GND, and control wire to one of ESP32's PWM pins.
	![Servo to ESP32 and L298N](diagrams/sceenshots/servo_to_ESP32_L298N.png)
- **Step 6:** Connect the ESP32's GND pin to L298N GND terminal and VIN to 5v (VSS) terminal. 
	![ESP32 to L298N](diagrams/sceenshots/ESP32_to_L298N.png)
- **Step 7:** Connect the DC motor to out 1 & 2 terminal blocks of L298N. L298N's IN1 and IN2 pins to ESP32's GPIO pins, and ENA to ESP32's PWM pin.
	![DC Motor to L298N to ESP32](diagrams/sceenshots/DCmotor_to_L298n_to_ESP32.png)
- **Step 8(Optional):** Change the speed options, servo steering angles, IN1, IN2, ENA, and servo control pins according to your configuration.
```
	// Servo control wire to GPIO 33
	#define servoPin 33

	// L298N motor driver
	#define dcMotorPin 14     // ENA to GPIO 14
	#define dcINPin1 27       // IN1 to GPIO 26
	#define dcINPin2 26       // IN2 to GPIO 27

	const int speeds[] = {50, 66, 82, 98, 114};  // Motor speeds | 0-255


	switch(command){
	  // Angles from 0-180
      case 'C':           // Center steering wheel
        steer.write(100);
        break;

      case 'R':           // Right steering wheel
        steer.write(125);
        break;

      case 'L':           // Left steering wheel
        steer.write(75);
        break;
    }
```
- **Step 9:** Upload the code.
	- **Using Arduino IDE**: Copy the code in src/ directory and paste on your sketch. Then install the libraries ESP32Servo by Kevin Harrington, John K. Bennett, and L298n_MotorDriver by Alex Krieg. After this, you can now upload it to the ESP32. See [Getting Started with ESP32](https://lastminuteengineers.com/getting-started-with-esp32/) to learn more how to setup ESP32 and upload code.
	- **Using PlatformIO**: Clone this github repository and change directory to it like so:
 
		`$ git clone https://github.com/Sishi-Source/Imperfect_Scorpion.git ./Imperfect_Scorpion && cd Imperfect_Scorpion`

  		and upload it using the command:

		`$ pio run -t upload`
- **Step 10:** Install the Scorpion_Remote_Controller.apk.
## Learn about the parts
1. [ESP32](https://lastminuteengineers.com/getting-started-with-esp32/)
2. [L298N](https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/)
3. [Servo Motor](https://lastminuteengineers.com/servo-motor-arduino-tutorial/)

---

## Output
![Output Diagram](diagrams/sceenshots/output_diag.png)

---

## Credits
This project uses the following parts and code libraries:

#### Fritzing Parts
- [L298N Motor Driver](https://forum.fritzing.org/t/h-bridge-with-l298n-motor-driver/7711)
- [18650 Battery Holder](https://forum.fritzing.org/t/18650-battery-holder-part-design/6523/11)
- [ESP32](https://github.com/Atsumitsu/fritzing-parts)
- [DC Motor](https://github.com/fritzing/fritzing-parts)
- [Servo](https://github.com/fritzing/fritzing-parts)

#### Code Libraries
- [ESP32Servo by madhephaestus](https://github.com/madhephaestus/ESP32Servo)
- [L298N_MotorDriver by KROIA](https://github.com/KROIA/L298N_MotorDriver)

Credits to the developers of the libraries and parts. Please visit their GitHub repositories for more information.

---

## License

This project is licensed under the [Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)](https://creativecommons.org/licenses/by-sa/4.0/) license. 

### License for Third-Party Components:
- **Fritzing Parts**: All Fritzing parts used in this project are licensed under **CC BY-SA 4.0**, as per the respective creators' specifications.
- **Code Libraries**: Please check the respective GitHub repositories for the licenses under which the code libraries are distributed. If no explicit license is provided, the authors are still credited above as a sign of respect and acknowledgment.
