
/* Project: POTENTIOSTAT FIRMWARE
 * File: MEASUREMENTS.c
 * Created: 04/01/2018
 * Author: Stuart Waddell
 * Robert Gordon University
 * School of Pharmacy and Life Sciences
 */ 

#include "main.h"
#include <math.h>

////////////////////////////////////////////////////////////////////
// READ ONLY BEGIN
////////////////////////////////////////////////////////////////////
/*
int MEASURE_VOLTAGE (void)
{
	return (READ_VOLTAGE());
}

int MEASURE_CURRENT (void)
{
	return (READ_CURRENT());
}
*/
////////////////////////////////////////////////////////////////////
// READ ONLY END
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
// BASIC DSP WORKING VERSION START NO ARRAY ALPHA = 3
////////////////////////////////////////////////////////////////////

/*
int MEASURE_VOLTAGE (void)
{
	OLD_VOLTAGE = READ_VOLTAGE();
	ARRAY_COUNTER = 0;
	for (MEASUREMENTS = 0; MEASUREMENTS < VOLTAGE_MEASUREMENT_NUMBER; MEASUREMENTS++)
	{
		VOLTAGE_ADDER = READ_VOLTAGE() + (3 * OLD_VOLTAGE);
		OLD_VOLTAGE = (VOLTAGE_ADDER >> 2);
	}
	return (OLD_VOLTAGE);
}

int MEASURE_CURRENT (void)
{
	OLD_CURRENT = READ_CURRENT();
	for (MEASUREMENTS = 0; MEASUREMENTS < CURRENT_MEASUREMENT_NUMBER; MEASUREMENTS++)
	{
		CURRENT_ADDER = READ_CURRENT() + (3 * OLD_CURRENT);
		OLD_CURRENT = (CURRENT_ADDER >> 2);
	}
	return (OLD_CURRENT);
}

*/

/*////////////////////////////////////////////////////////////////////////////////////////
////////////////////     BASIC DSP WORKING VERSION NO ARRAY END   /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////*/

////////////////////////////////////////////////////////////////////
// BASIC DSP WORKING VERSION START WITHOUT ARRAY ALPHA = 3 WITH AVERAGING
////////////////////////////////////////////////////////////////////
/*

int MEASURE_VOLTAGE (void)
{
	VOLTAGE_ADDER = 0;
	OLD_VOLTAGE = READ_VOLTAGE();
	for (MEASUREMENTS = 0; MEASUREMENTS < VOLTAGE_MEASUREMENT_NUMBER; MEASUREMENTS++)
	{
		NEW_VOLTAGE = (READ_VOLTAGE() + (3 * OLD_VOLTAGE));
		OLD_VOLTAGE = (NEW_VOLTAGE >> 2);
		VOLTAGE_ADDER += OLD_VOLTAGE;
	}
	VOLTAGE = VOLTAGE_ADDER / VOLTAGE_MEASUREMENT_NUMBER;
	return (VOLTAGE);
}

int MEASURE_CURRENT (void)
{
	CURRENT_ADDER = 0;
	OLD_CURRENT = READ_CURRENT();
	for (MEASUREMENTS = 0; MEASUREMENTS < CURRENT_MEASUREMENT_NUMBER; MEASUREMENTS++)
	{
		NEW_CURRENT = (READ_CURRENT() + (3 * OLD_CURRENT));
		OLD_CURRENT = (NEW_CURRENT >> 2);
		CURRENT_ADDER += OLD_CURRENT;
	}
	CURRENT = CURRENT_ADDER / CURRENT_MEASUREMENT_NUMBER;
	return (CURRENT);
}
*/

/*////////////////////////////////////////////////////////////////////////////////////////
////////////////////     BASIC DSP WORKING VERSION END WITHOUT ARRAY  WITH AVERAGNG //////
////////////////////////////////////////////////////////////////////////////////////////*/



/*/////////////////////////////////////////////////////////////////////////////////////////
//  JUST AVERAGING START
//////////////////////////////////////////////////////////////////////////////////////////*/


int MEASURE_VOLTAGE (void)
{
	VOLTAGE_ADDER = 0;
	for (MEASUREMENTS = 0; MEASUREMENTS < VOLTAGE_MEASUREMENT_NUMBER; MEASUREMENTS++)
	{
		VOLTAGE_ADDER += READ_VOLTAGE();
	}
	VOLTAGE = VOLTAGE_ADDER / VOLTAGE_MEASUREMENT_NUMBER;
	return (VOLTAGE);
}

int MEASURE_CURRENT (void)
{
	CURRENT_ADDER = 0;
	for (MEASUREMENTS = 0; MEASUREMENTS < CURRENT_MEASUREMENT_NUMBER; MEASUREMENTS++)
	{
		CURRENT_ADDER += READ_CURRENT();
	}
	CURRENT = CURRENT_ADDER / CURRENT_MEASUREMENT_NUMBER;
	return (CURRENT);
}

/*//////////////////////////////////////////////////////////////////////////////////////////
//  JUST AVERAGING END
////////////////////////////////////////////////////////////////////////////////////////*/