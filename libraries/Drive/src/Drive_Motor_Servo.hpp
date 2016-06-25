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
#include "Drive.hpp"
#include "Drive_Motor.hpp"

class Drive_Motor_Servo: public Drive_Motor
{

public:
	Drive_Motor_Servo(int pin=NOT_A_PIN);
	void setPin(int pin);

	void startEngine();
	void stopEngine();

	void setSpeedPercent(int percent);
	void setDirection(int direction);

	void stop();
	void drive();

	bool isReady();
	bool isRunning();
	bool isStopped();


private:
	int _pin;
	Servo *_servo;
	int _motorOffset;
	int _servoValue;
	int _direction;
	bool _stopped;

};



#endif /* LIBRARIES_DRIVE_SRC_DRIVE_MOTOR_SERVO_HPP_ */
