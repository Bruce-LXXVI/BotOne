
#include <Arduino.h>
#include <Servo.h>


// LED on board
const int ledPin = 13;

// LEDs on head
const int ledRedPin = 0;
const int ledYellowPin = 1;
const int ledGreenPin = 2;
const int ledBluePin = 4;
const int usPin = 7;
const int headServoPin = 3;

// Drive
const int motorServoPin = 5;
const int steeringServoPin = 6;


// Calibration
const int headOffset = 0;
const int motorOffset = 1;
const int steeringOffset = 3;


// Initialize vars
Servo headServo;
Servo motorServo;
Servo steeringServo;

unsigned long time = 0;
int ledState = LOW;
int ledNum = 0;
int headDirection = 0;


//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(ledPin, OUTPUT);
	pinMode(ledRedPin, OUTPUT);
	pinMode(ledYellowPin, OUTPUT);
	pinMode(ledGreenPin, OUTPUT);
	pinMode(ledBluePin, OUTPUT);
	//pinMode(usPin, OUTPUT);

	headServo.attach(headServoPin);
	headServo.write(90 + headOffset);

	motorServo.attach(motorServoPin);
	motorServo.write(90 + motorOffset);

	steeringServo.attach(steeringServoPin);
	steeringServo.write(90 + steeringOffset);
}

// The loop function is called in an endless loop
void loop()
{
	//if(time == 0) time=millis();

	if( (millis() - time) > 2000 ) {
		time=millis();


		ledNum++;
		if(ledNum > 4) ledNum = 0;
		digitalWrite(ledPin, ledNum==0 ? HIGH : LOW);
		digitalWrite(ledRedPin, ledNum==1 ? HIGH : LOW);
		digitalWrite(ledYellowPin, ledNum==2 ? HIGH : LOW);
		digitalWrite(ledGreenPin, ledNum==3 ? HIGH : LOW);
		digitalWrite(ledBluePin, ledNum==4 ? HIGH : LOW);




		if(ledState == LOW) ledState = HIGH;
		else ledState = LOW;




		if(headDirection > 0) headDirection = -30;
		else headDirection = 30;
		headServo.write(90 + headDirection + headOffset);
	}

/*
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
*/

}
