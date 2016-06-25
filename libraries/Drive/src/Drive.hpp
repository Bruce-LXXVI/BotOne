/*
 * Drive.hpp
 *
 *  Created on: 25.06.2016
 *      Author: Bruce <bruce@playz.rocks>
 */

#ifndef LIBRARIES_DRIVE_SRC_DRIVE_HPP_
#define LIBRARIES_DRIVE_SRC_DRIVE_HPP_

#include <Arduino.h>
#include "Drive_Motor.hpp"
#include "Drive_Motor_Servo.hpp"

class Drive
{

public:
	Drive(Drive_Motor *motor=NULL);
	void setup(Drive_Motor *motor=NULL);
	void update();

	bool isMotorReady();
	bool isStopped();

	void startEngine();
	void stopEngine();

	void setSpeedPercent(int percent);
	void setDirection(int direction);
	const static int DIR_UNDEF=0;
	const static int DIR_FORWARD=1;
	const static int DIR_BACKWARD=2;

	void stop();
	void drive();


	const static int MOTORTYPE_NONE=0;
	const static int MOTORTYPE_SERVO=0;

private:
	Drive_Motor *_motor;

};



#endif /* LIBRARIES_DRIVE_SRC_DRIVE_HPP_ */
