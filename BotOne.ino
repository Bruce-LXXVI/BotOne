
#include <Arduino.h>
#include <Servo.h>


const int motorServoPin = 9;
const int steeringServoPin = 10;

Servo motorServo;
Servo steeringServo;



//The setup function is called once at startup of the sketch
void setup()
{
	motorServo.attach(motorServoPin);
	steeringServo.attach(steeringServoPin);

	motorServo.write(90);
	steeringServo.write(90);
}

// The loop function is called in an endless loop
void loop()
{

}
