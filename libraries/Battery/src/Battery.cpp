/*
 * Battery.cpp
 */

#include "Battery.h"

Battery::Battery()
{
	_pinCell1 = A0;
	_pinCell2 = A1;
	_lastRunTime = 0;
	_blinker = false;
	_blinkCount = 0;
	_v1=0.0;
	_v2=0.0;
	_ledAlarm=NULL;
	_ledCheck=NULL;
};


void Battery::setCheckLed(Led *led)
{
	_ledCheck=led;
}


void Battery::setAlarmLed(Led *led)
{
	_ledAlarm=led;
}


void Battery::update()
{

	if( (millis() - this->_lastRunTime) > INTERVAL )
	{
		this->_lastRunTime=millis();
		_blinkCount++;

		_v1=(_v1 + (analogRead(this->_pinCell1) * 5.0) / 1024.0) / 2.0;
		_v2=(_v2 + (analogRead(this->_pinCell2) * 5.0) / 1024.0) / 2.0;

		if(_blinkCount > reportEveryInterval)
		{
			_blinkCount=0;

			Console.print("Battery report: Cell 1=");
			Console.print(_v1);
			Console.print("V | Cell 2=");
			Console.print(_v2);
			Console.println("V");


			if( (_v1 < MIN_CELL_VOLT) || (_v2 < MIN_CELL_VOLT) )
			{
				Console.println("SHUTDOWN!!");
				if(_ledAlarm != NULL) _ledAlarm->setBlinker(100, 100);
				// http://www.arduino.cc/playground/Learning/ArduinoSleepCode
				//set_sleep_mode(SLEEP_MODE_PWR_DOWN);
				//sleep_enable();
				//sleep_mode();
			}
		}


		if(_blinker)
		{
			if(_ledCheck != NULL) _ledCheck->setOn();
		} else
		{
			if(_ledCheck != NULL) _ledCheck->setOff();
		}
		_blinker=!_blinker;
	};


}


