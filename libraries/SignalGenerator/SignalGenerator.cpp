/////////////////////////
// SignalGenerator.cpp //
/////////////////////////

#include "SignalGenerator.h"

//--------------//
// Constructors //
//--------------//

SignalGenerator::SignalGenerator(const Timer& timer)
: _type(type),
  _timer(timer)
{
	Serial.println("Signal Generator here!");
}

SignalGenerator::~SignalGenerator()
{}

//----------------//
// Public Methods //
//----------------//

auto SignalGenerator::print() -> void
{
	Serial.println("---------------------");
	Serial.println("Signal Generator v1.0");
	Serial.println("---------------------");

	Serial.print("Timer Used: ");
	switch(_timer)
	{
		case Timer::T0:
			Serial.println("Timer 0");
			break;
		case Timer::T1:
			Serial.print("Timer 1");
			break;
		case Timer::T2:
			Serial.println("Timer 2");
			break;
	}
}

//-------------------//
// Private Functions //
//-------------------//

/*
auto SignalGenerator::validate(DigitalPin real, DigitalPin imaginary) -> bool
{
	// Check validity of pins
	if(real > NUM_DIGITAL_PINS)
	{
		Serial.println("SignalGenerator: INVALID REAL PIN");
		return false;
	}
	if(_type == SignalType::COMPLEX && imaginary < 0 || imaginary > NUM_DIGITAL_PINS)
	{
		Serial.println("SignalGenerator: INVALID IMAGINARY PIN");
		return false;
	}
	
	// Assign values to save the pins
	_real = real;
	_imaginary = imaginary;
	
	return true;
}
*/

