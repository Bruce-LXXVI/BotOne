/*
 * Drive_Motor.hpp
 *
 *  Created on: 25.06.2016
 *      Author: Bruce <bruce@playz.rocks>
 */

#ifndef LIBRARIES_DRIVE_SRC_DRIVE_MOTOR_HPP_
#define LIBRARIES_DRIVE_SRC_DRIVE_MOTOR_HPP_

#include <Arduino.h>


class Drive_Motor
{

public:
	virtual void setup(){};

	virtual void startEngine(){};
	virtual void stopEngine(){};

	virtual void setSpeedPercent(int percent){};

	virtual void stop(){};
	virtual void forward(){};

	virtual bool isReady(){ return false; };
	virtual bool isRunning(){ return false; };

	virtual ~Drive_Motor(){};

private:


};




#endif /* LIBRARIES_DRIVE_SRC_DRIVE_MOTOR_HPP_ */
