/*
SignalGenerator.h

Arduino library for generating a square wave, complex-valued signal using
any of the timers on the Arduino Uno/Nano platform.

Copyright Adan Moran-MacDonald
Last Modified 22 Jan 2018
*/
#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H
#pragma once

#include "Arduino.h" // Required to be able to use Arduino library

/**
 * Define timer constants. While we do not usually like to use a define in c++,
 * here we do it to save space on the Arduino ROM (since having a static const will take up 
 * valuable memory space). 
 * We may  not need these, but they're here for convenience.
 */
#define TIMER0_PWM_PIN_A 4
#define TIMER0_PWM_PIN_B 13
#define TIMER1_PWM_PIN_A 11
#define TIMER1_PWM_PIN_B 12
#define TIMER2_PWM_PIN_A 9
#define TIMER2_PWM_PIN_B 10
#define TIMER3_PWM_PIN_A 2
#define TIMER3_PWM_PIN_B 3
#define TIMER3_PWM_PIN_C 5
#define TIMER4_PWM_PIN_A 6
#define TIMER4_PWM_PIN_B 7
#define TIMER4_PWM_PIN_C 8

/**
 * Define clock speed constants for handling different
 * Arduinos. Like was mentioned above, we do this instead of static consts
 * to save memory space.
 */
#define UNO_CLOCK_SPEED = 16000000 //16MHz
#define DUE_CLOCK_SPEED = 84000000 //84MHz

// Define a pin type for digital signals, which must be positive and are not big numbers.
using DigitalPin = int8_t;

// Define a type for frequency values in Hz, which must be positive.
using Frequency = uint64_t;

/*
Enumeration object to define which timers to use for signal generation
- Uno/Nano has access to T0,T1,T2 only
- Due has access to all
*/
enum class Timer
{
	T0,
	T1,
	T2,
	T3,
	T4
};

/*
Enumeration object to define which Arduino we are using, since this modifies the maximum frequency of Timers.
- Uno/Nano/Mega/Leonardo has 16MHz clock
- Due has 84MHz clock
*/
enum class ArduinoSize
{
	UNO,
	DUE
};
	
/* Base SignalGenerator class
 * This will be extended into Real and Complex signal generators
 */
class SignalGenerator
{
	public:
   /**
    * Initialize a SignalGenerator for this arduino type, on this timer.
    * Note that the UNO only has access to Timer0, Timer1, Timer2 and 
    * so the combination will only be valid for Uno if it is one of those timers.
    */
	SignalGenerator(const ArduinoSize& arduino, const Timer& timer);
	~SignalGenerator();
	
	/**
	 * Print the options of the signal generator:
	 * - signal type (real or complex)
	 * - timer choice (T1, T2, or T3)
	 */
	auto print() -> void;

	/**
    * Get the clock speed for this arduino, in Hz
    */
   auto maxClockSpeed() -> Frequency;
	/**
	 * Read which timer the signal generator is using`
	 */

	auto timer() -> const Timer& 
	{ return timer_; }

   /**
    * Tell which type of Arduino this is.
    */
   auto type() -> const ArduinoSize&
   { return _arduino; }

   /**
    * Returns true if the ArduinoSize/Timer combination inputted is valid.
    */
   auto isValid() -> bool
   { return _valid; }

   /**
    * Set up the timer to run at a given frequency on PIN_A
    */
   virtual auto setup(Frequency) -> bool = 0;

   /**
    * Run the signal generator
    */
   virtual auto run() -> bool = 0;

   /**
    * Stop the signal generator
    */
   virtual auto stop() -> bool = 0;
	
	private:
	Timer _timer;
   ArduinoSize& _arduino;
   bool _valid = false;
};

/* RealSignalGenerator
 * Uses the timer from the SignalGenerator class and generates
 * a real-valued signal.
 */
class RealSignalGenerator : public SignalGenerator
{
   public:
   /**
    * Initialize a Signalgenerator to start at the gien timer.
    */
   RealSignalGenerator(const ArduinoSize& arduino, const Timer& timer)
      : SignalGenerator(arduino, timer) {}

   /** 
    * Set up the signal to run on PIN_A at the inputted frequency.
    */
   auto setup(Frequency frequency) -> bool;

   /**
    * Set up the signal to run on the given pin. This must match one of the
    * pins available to the timer.
    */
   auto setup(Frequency frequency, DigitalPin timerPin) -> bool;

   private:

   /** 
    * Verify that the given digital pin matches the pins for this timer
    */
   auto pinMatchesTimer(DigitalPin) -> bool;

   
};

 // TODO: the signal should always be on a hardwware pin (no ISR routines here). How do we enforce that? How do users choose whether it's on PIN_A,B, or C??? 
 // TODO: the signal should have a default frequency, plus they should be allowed to modify the frequency at runtime. How to do this?
 // TODO: make a complex signal generator that uses two real signal generators, and allow the user to choose PIN_A, B, or C as the real and another as complex.
 // TODO: Alternatively, make a complex signal generator that toggles the two pins using one timer with hardware, as we did for the heart rate monitor in February.
 

#endif
// vim: ts=3 sw=3 sts=0 et: 
