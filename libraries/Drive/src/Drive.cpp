/*
 * Drive.cpp
 *
 *  Created on: 25.06.2016
 *      Author: Bruce <bruce@playz.rocks>
 */

#include "Drive.hpp"


Drive::Drive(Drive_Motor *motor /*=NULL*/)
{
	this->_motor=motor;
};


void Drive::setup(Drive_Motor *motor /*=NULL*/)
{
	if(motor != NULL) this->_motor=motor;
	this->_motor->setup();
};


bool Drive::isMotorReady()
{
	return (this->_motor != NULL) && this->_motor->isReady();
}

void Drive::update()
{
};


void Drive::startEngine()
{
	if(this->isMotorReady()) this->_motor->startEngine();
};


void Drive::stopEngine()
{
	if(this->isMotorReady()) this->_motor->stopEngine();
};


void Drive::setSpeedPercent(int percent)
{
	if(this->isMotorReady()) this->_motor->setSpeedPercent(percent);
};


void Drive::stop()
{
	if(this->isMotorReady()) this->_motor->stop();
};


void Drive::forward()
{
	if(this->isMotorReady()) this->_motor->forward();
};

