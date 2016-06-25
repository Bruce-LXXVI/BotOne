
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
unsigned long timeSteer = 0;
int ledState = LOW;
int ledNum = 0;
int headDirection = 0;
int steerDirection = 0;
int speedPercent = 10;


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
	/*
	Console.write('\377');
	Console.write('\375');
	Console.write('\042');
	Console.write('\377');
	Console.write('\373');
	Console.write('\001');
	*/

}

// The loop function is called in an endless loop
void loop()
{
	//if(time == 0) time=millis();
	if(timeSteer == 0) timeSteer=millis();

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

		// q=schneller / y=langsamer
		if(c == 'q') speedPercent=speedPercent + 1;
		if(c == 'y') speedPercent=speedPercent - 1;
		if(speedPercent > 100) speedPercent=100;
		if(speedPercent < 0) speedPercent=0;
		if( (c == 'q') || (c == 'y')) drive.setSpeedPercent(speedPercent);

		// w=vorwärts / s=rückwärts
		if( c == 'w' )
		{
			if( drive.isStopped() )
			{
				drive.setDirection(Drive::DIR_FORWARD);
				drive.startEngine();
				drive.setSpeedPercent(speedPercent);
				drive.drive();
			} else
			{
				drive.stopEngine();
			}
		}
		if( c == 's' )
		{
			if( drive.isStopped() )
			{
				drive.setDirection(Drive::DIR_BACKWARD);
				drive.startEngine();
				drive.setSpeedPercent(speedPercent);
				drive.drive();
			} else
			{
				drive.stopEngine();
			}
		}

		// a=links / d=rechts
		if(c == 'a') steerDirection=steerDirection + 3;
		if(c == 'd') steerDirection=steerDirection - 3;
		if( (c == 'd') || (c == 'a') ) timeSteer=millis();
		if( (c != 'a') && (c != 'd') && (steerDirection > 0) ) steerDirection=steerDirection - 1;
		if( (c != 'a') && (c != 'd') && (steerDirection < 0) ) steerDirection=steerDirection + 1;
		if(steerDirection > 50) steerDirection=50;
		if(steerDirection < -50) steerDirection=-50;
	}
	if( millis() - timeSteer > 150)
	{
		timeSteer=millis();
		if( steerDirection > 0 ) steerDirection=steerDirection - (1 + steerDirection / 3);
		if( steerDirection < 0 ) steerDirection=steerDirection - (1 + steerDirection / 3);
	}

	steeringServo.write(90 + steeringOffset + steerDirection);

	if(drive.isStopped()) ledYellow.setOff();
	else ledYellow.setBlinker(100);


	// Nach 10 Sekunden anhalten
	if( (millis() - time) > 5000 ) {
		//ledBlue.setBlinker(200);

	} else {
		//ledBlue.setOff();

		/*
		// <90 rechts / >90 links
		steeringServo.write(80 + steeringOffset);

		// <90 vorwärts / >90 rückwärts
		motorServo.write(80 + motorOffset);
		*/
	}


}
