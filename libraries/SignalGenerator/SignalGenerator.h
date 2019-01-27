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

// Define a pin type for digital signals, which must be positive and are not big numbers.
using DigitalPin = int8_t;

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

/*
Specify whether the signal is real or complex.
*/
enum class SignalType
{
	REAL,
	COMPLEX
};
	
template<ArduinoSize A>
class SignalGenerator
{
	public:
		
		
	SignalGenerator(const SignalType& type, const Timer& timer, DigitalPin real, DigitalPin imaginary = -1);
	~SignalGenerator();
	
	/**
	 * Print the options of the signal generator:
	 * - signal type (real or complex)
	 * - timer choice (T1, T2, or T3)
	 */
	auto print() -> void;
	
	private:
	
	/**
	 * Ensure the inputs to the signal generator are valid for the given 
	 * signal type and timer.
	 */
	auto validate(DigitalPin real, DigitalPin imaginary) -> bool;
	
	SignalType _type;
	Timer _timer;
	DigitalPin _real;
	DigitalPin _imaginary;
};

#endif