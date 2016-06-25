/*
 * Drive_Motor_Servo.cpp
 *
 *  Created on: 25.06.2016
 *      Author: Bruce <bruce@playz.rocks>
 */

#include "Drive_Motor_Servo.hpp"

Drive_Motor_Servo::Drive_Motor_Servo(int pin /*=NOT_A_PIN*/)
{
	this->_servo=new Servo();
	this->_pin=NOT_A_PIN;
	this->_motorOffset=0;
	this->_servoValue=90;
	this->_direction=Drive::DIR_UNDEF;
	this->_stopped=true;

	this->setPin(pin);
}


void Drive_Motor_Servo::setPin(int pin)
{
	this->_pin=pin;
	this->stopEngine();
}


void Drive_Motor_Servo::stopEngine()
{
	if(!this->isRunning()) return;
	this->stop();
	this->_servo->detach();
	pinMode(this->_pin, OUTPUT);
	digitalWrite(this->_pin, LOW);
}


void Drive_Motor_Servo::startEngine()
{
	if(this->isRunning()) return;
	this->stop();
	this->_servo->attach(this->_pin);
}


void Drive_Motor_Servo::setSpeedPercent(int percent)
{
	this->_servoValue=(percent * 90) / 100;
	if( !this->isStopped() ) this->drive();
}


void Drive_Motor_Servo::setDirection(int direction)
{
	this->_direction=direction;
}


void Drive_Motor_Servo::stop()
{
	if(!this->isReady()) return;
	this->_servo->write(90 + _motorOffset);
	this->_stopped=true;
}


void Drive_Motor_Servo::drive()
{
	if(!this->isReady()) return;
	this->_stopped=false;

	if(this->_direction == Drive::DIR_FORWARD)
		this->_servo->write(90 - this->_servoValue);

	if(this->_direction == Drive::DIR_BACKWARD)
		this->_servo->write(90 + this->_servoValue);
}


bool Drive_Motor_Servo::isRunning()
{
	return this->isReady() && this->_servo->attached();
}


bool Drive_Motor_Servo::isReady()
{
	return this->_servo != NULL;
}


bool Drive_Motor_Servo::isStopped()
{
	return !this->isReady() || this->_stopped;
}

