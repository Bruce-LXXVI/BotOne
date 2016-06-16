
#include <Arduino.h>
#include <Servo.h>


const int motorServoPin = 9;
const int steeringServoPin = 10;
const int ledPin = 13;


// Kalibration
const int motorOffset = 1;
const int steeringOffset = 3;

Servo motorServo;
Servo steeringServo;

unsigned long time = 0;


//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(ledPin, OUTPUT);

	motorServo.attach(motorServoPin);
	motorServo.write(90 + motorOffset);

	steeringServo.attach(steeringServoPin);
	steeringServo.write(90 + steeringOffset);

}

// The loop function is called in an endless loop
void loop()
{
	if(time == 0) time=millis();


	// Nach 5 Sekunden anhalten
	if( (millis() - time) > 5000 ) {
		motorServo.write(90 + motorOffset);
		steeringServo.write(90 + steeringOffset);
		digitalWrite(ledPin, HIGH);
	} else {
		// <90 rechts / >90 links
		steeringServo.write(80 + steeringOffset);

		// <90 vorwärts / >90 rückwärts
		motorServo.write(80 + motorOffset);
	}


}
