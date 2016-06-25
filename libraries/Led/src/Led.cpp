/*
 * Led.cpp
 *
 *  Created on: 20.06.2016
 *      Author: Bruce <bruce@playz.rocks>
 */


#include "Led.hpp"


Led::Led(int pin /* =NOT_A_PIN */)
{
	this->_pin=pin;
	this->_lastRunTime=0;
	this->_interval=100;
	this->_function=Led::FN_OFF;
	this->_onMs=0;
	this->_offMs=0;
	this->_blinker=false;
};


bool Led::isPin()
{
	return this->_pin != NOT_A_PIN;
}


void Led::setup(int pin /* =NOT_A_PIN */)
{
	if( !this->isPin() ) return;
	pinMode(this->_pin, OUTPUT);
	this->_digitalWrite(LOW);
	this->_function=Led::FN_OFF;
};


void Led::setOff()
{
	if( this->_digitalWrite(LOW) )
	{
		this->_function=Led::FN_OFF;
		this->_interval=100;
	}
}


void Led::setOn()
{
	if( this->_digitalWrite(HIGH) )
	{
		this->_function=Led::FN_ON;
		this->_interval=100;
	}
}


void Led::setBlinker(unsigned long onMs /* =0 */, unsigned long offMs /* =0 */)
{
	if(onMs > 0)
	{
		//this->_blinker=false;
		this->_function=Led::FN_BLINKER;
		this->_onMs=onMs;
		if(offMs > 0) this->_offMs=offMs;
		else this->_offMs=onMs;
		return;
	}

	if( this->_digitalWrite( this->_blinker=!this->_blinker ) )
	{
		if(this->_blinker) this->_interval=this->_onMs;
		else this->_interval=this->_offMs;
	}
}


void Led::update()
{
	if( (millis() - this->_lastRunTime) > this->_interval )
	{
		this->_lastRunTime=millis();

		switch(this->_function) {
			case Led::FN_OFF:
				this->setOff();
				break;

			case Led::FN_ON:
				this->setOn();
				break;

			case Led::FN_BLINKER:
				this->setBlinker();
				break;

		}
	}

};


bool Led::_digitalWrite(uint8_t val)
{
	if( !this->isPin() ) return false;
	digitalWrite(this->_pin, val);
	return true;
}


