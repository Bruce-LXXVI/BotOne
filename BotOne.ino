
#include <Arduino.h>
#include <Bridge.h>
#include <Console.h>
#include <Servo.h>

#include "libraries/Battery/src/Battery.h"
#include "libraries/Led/src/Led.hpp"
#include "libraries/Drive/src/Drive.hpp"


// LED on board
const int ledPin = 13;

// LEDs on head
const int ledRedPin = 8;
const int ledYellowPin = 9;
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
const int steeringOffset = 4;


// Initialize vars
Battery battery;
Led led(ledPin);
Led ledRed(ledRedPin);
Led ledYellow(ledYellowPin);
Led ledGreen(ledGreenPin);
Led ledBlue(ledBluePin);

Drive_Motor_Servo motorServo(motorServoPin);
Drive drive(&motorServo);


Servo headServo;

Servo steeringServo;


unsigned long time = 0;
int ledState = LOW;
int ledNum = 0;
int headDirection = 0;


//The setup function is called once at startup of the sketch
void setup()
{
	// initialize serial communication:
	Bridge.begin();
	Console.begin();

	led.setup();
	ledRed.setup();
	ledRed.setBlinker(100, 1000);
	ledYellow.setup();
	ledGreen.setup();
	ledBlue.setup();

	//battery.setCheckLed(&ledBlue);
	battery.setAlarmLed(&led);


	drive.setup();



	//pinMode(usPin, OUTPUT);
	//digitalWrite(usPin, LOW);


	headServo.attach(headServoPin);
	headServo.write(90 + headOffset);




	pinMode(steeringOffset, OUTPUT);
	digitalWrite(steeringServoPin, LOW);
	steeringServo.attach(steeringServoPin);
	steeringServo.write(90 + steeringOffset);



	/*
	while (!Console)
	{
		; // wait for Console port to connect.
	}
	*/
	Console.println("You're connected to the Console!!!!");

}

// The loop function is called in an endless loop
void loop()
{
	if(time == 0) time=millis();

	battery.update();

	led.update();
	ledRed.update();
	ledYellow.update();
	ledGreen.update();
	ledBlue.update();

	drive.update();


	if( Console.available() > 0 )
	{
		char c=Console.read();
		if(c == ' ') time=millis();
		if(c == 'a') {
			steeringServo.write(105 + steeringOffset);
		}
		if(c == 'd') {
			steeringServo.write(75 + steeringOffset);
		}
		if(c == 'w') {
			steeringServo.write(90 + steeringOffset);
		}

	}


	// Nach 10 Sekunden anhalten
	if( (millis() - time) > 2000 ) {
		ledBlue.setBlinker(200);
		drive.stopEngine();
	} else {

		ledBlue.setOff();
		drive.startEngine();
		drive.setSpeedPercent(15);
		drive.forward();

		/*
		// <90 rechts / >90 links
		steeringServo.write(80 + steeringOffset);

		// <90 vorwärts / >90 rückwärts
		motorServo.write(80 + motorOffset);
		*/
	}


}
