/*
 * Drive_Motor_Servo.hpp
 *
 *  Created on: 25.06.2016
 *      Author: Bruce <bruce@playz.rocks>
 */

#ifndef LIBRARIES_DRIVE_SRC_DRIVE_MOTOR_SERVO_HPP_
#define LIBRARIES_DRIVE_SRC_DRIVE_MOTOR_SERVO_HPP_

#include <Arduino.h>
#include <Servo.h>
#include "Drive_Motor.hpp"

class Drive_Motor_Servo: public Drive_Motor
{

public:
	Drive_Motor_Servo(int pin=NOT_A_PIN);
	void setPin(int pin);

	void startEngine();
	void stopEngine();

	void setSpeedPercent(int percent);

	void stop();
	void forward();

	bool isReady();
	bool isRunning();


private:
	int _pin;
	Servo *_servo;
	int _motorOffset;
	int _servoValue;

};



#endif /* LIBRARIES_DRIVE_SRC_DRIVE_MOTOR_SERVO_HPP_ */
