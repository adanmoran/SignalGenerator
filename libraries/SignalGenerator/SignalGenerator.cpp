/////////////////////////
// SignalGenerator.cpp //
/////////////////////////

#include "SignalGenerator.h"

//--------------//
// Constructors //
//--------------//

SignalGenerator::SignalGenerator(const SignalType& type, const Timer& timer, DigitalPin real, DigitalPin imaginary)
: _type(type),
  _timer(timer)
{
	Serial.println("Signal Generator here!");
	if(!validate(real, imaginary))
	{
		// TODO: something went wrong: emit an exception or fail.
	}
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
	Serial.print("Signal Type: ");
	switch(_type)
	{
		case SignalType::REAL:
			Serial.println("Real");
			break;
		case SignalType::COMPLEX:
			Serial.println("Complex");
			break;
	}
	
	Serial.print("Timer Used: ");
	switch(_timer)
	{
		case Timer::T0:
			Serial.println("Timer 0");
			break;
		case Timer::T1:
			Serial.print("Timer 1 (Real Pin = ");
			Serial.print(_real);
			Serial.print("; Imaginary Pin = ");
			Serial.print(_imaginary);
			Serial.println(")");
			break;
		case Timer::T2:
			Serial.println("Timer 2");
			break;
	}
}

//-------------------//
// Private Functions //
//-------------------//

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

