/*
 * Battery.h
 *
 *  Created on: 18.06.2016
 *      Author: Bruce <bruce@playz.rocks>
 */

#ifndef LIBRARIES_BATTERY_BATTERY_H_
#define LIBRARIES_BATTERY_BATTERY_H_

#include <Arduino.h>
//#include <avr/sleep.h>
#include <Bridge.h>
#include <Console.h>
#include "../../Led/src/Led.hpp"


class Battery
{

public:
	Battery();
	void update();
	void setCheckLed(Led *led);
	void setAlarmLed(Led *led);


private:
	int _pinCell1;
	int _pinCell2;
	unsigned long _lastRunTime;
	bool _blinker;
	int _blinkCount;
	float _v1;
	float _v2;

	Led *_ledAlarm;
	Led *_ledCheck;


	const int reportEveryInterval= 20;
	const unsigned long INTERVAL = 500;
	const float MIN_CELL_VOLT = 3.9;


};



#endif /* LIBRARIES_BATTERY_BATTERY_H_ */
