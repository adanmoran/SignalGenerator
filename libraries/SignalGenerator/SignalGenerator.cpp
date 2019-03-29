/////////////////////////
// SignalGenerator.cpp //
/////////////////////////

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//               SIGNAL_GENERATOR IMPLEMENTATION
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
#include "SignalGenerator.h"

//--------------//
// Constructors //
//--------------//

SignalGenerator::SignalGenerator(const ArduinoSize& arduino, const Timer& timer)
: _arduino(arduino),
  _timer(timer)
{
	Serial.println("Signal Generator here!");

   if (arduino == ArduinoSize::UNO && (timer == Timer::T3 || timer == Timer::T4))
   {
      Serial.println("ArduinoSize/Timer combo is invalid; Uno can only use Timers 0,1,2.");
      _valid = false;
   }
   _valid = true;
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

   Serial.print("Arduino Type specified: ");
   switch(_arduino)
   {
      case ArduinoSize::UNO:
         Serial.println("Uno");
         break;
      case ArduinoSize::DUE:
         Serial.println("Due");
         break;
   }

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

auto SignalGenerator::maxClockSpeed() -> Frequency
{
   switch(_arduino)
   {
      case ArduinoSize::Uno:
         return Frequency(UNO_CLOCK_SPEED);
      case ArduinoSize::Due:
         return Frequency(DUE_CLOCK_SPEED);
   }
   // This will never get here, but let's assume we're on an Uno
   return Frequency(UNO_CLOCK_SPEED);
}

//-------------------//
// Private Functions //
//-------------------//

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//             REAL_SIGNAL_GENERATOR IMPLEMENTATION
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//----------------//
// Public Methods //
//----------------//

auto RealSignalGenerator::setup(Frequency frequency) -> bool
{
   // TODO: Set up the arduino to run on PIN_A for this timer
   // e.g. setup(Frequency, PIN_A) where PIN_A is for this timer
   return setup(frequency, TIMER0_PWM_PIN_A);
}

auto RealSignalGenerator::setup(Frequency frequency, DigitalPin timerPin) -> bool
{
   // If this is an invalid generator, do nothing
   if (!isValid())
   {
      return false;
   }

   // If this pin does not match the chosen timer, do nothing
   if (!pinMatchesTimer(timerPin))
   {
      Serial.println("RealSignalGenerator::setup(): pin given is not controlled by the chosen timer.");
      return false;
   }

   // TODO: Initialize a hardware-only timer using PWM signals.
   // TODO: Verify that the given pin matches the current timer, or return false.
   return false;
}

//-----------------//
// Private Methods //
//-----------------//

auto RealSignalGenerator::pinMatchesTimer(DigitalPin timerPin) -> bool
{
   switch(timer())
   {
      case Timer::T0:
         if (timerPin == TIMER0_PWM_PIN_A || timerPin == TIMER0_PWM_PIN_B)
         { return true; }
         break;
      case Timer::T1:
         if (timerPin == TIMER1_PWM_PIN_A || timerPin == TIMER1_PWM_PIN_B)
         { return true; }
         break;
      case Timer::T2:
         if (timerPin == TIMER2_PWM_PIN_A || timerPin == TIMER2_PWM_PIN_B)
         { return true; }
         break;
      case Timer::T3:
         if (timerPin == TIMER3_PWM_PIN_A || timerPin == TIMER3_PWM_PIN_B || timerPin == TIMER3_PWM_PIN_C)
         { return true; }
         break;
      case Timer::T4:
         if (timerPin == TIMER4_PWM_PIN_A || timerPin == TIMER4_PWM_PIN_B || timerPin == TIMER4_PWM_PIN_C)
         { return true; }
         break;
   }
   return false;
}

// vim: ts=3 sw=3 sts=0 et: 
