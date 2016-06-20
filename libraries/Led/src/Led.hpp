/*
 * Led.hpp
 *
 *  Created on: 20.06.2016
 *      Author: Bruce <bruce@playz.rocks>
 */

#ifndef LIBRARIES_LED_SRC_LED_HPP_
#define LIBRARIES_LED_SRC_LED_HPP_

#include <Arduino.h>

class Led
{

public:
	Led(int pin=NOT_A_PIN);
	void setup(int pin=NOT_A_PIN);
	void update();
	bool isPin();

	void setOn();
	void setOff();
	void setBlinker(unsigned long onMs=0, unsigned long offMs=0);

	static const int FN_OFF=0;
	static const int FN_ON=1;
	static const int FN_BLINKER=2;

private:
	bool _digitalWrite(uint8_t val);
	int _pin;
	unsigned long _lastRunTime;
	unsigned long _interval;
	int _function;
	unsigned long _onMs;
	unsigned long _offMs;
	bool _blinker;



};




#endif /* LIBRARIES_LED_SRC_LED_HPP_ */
