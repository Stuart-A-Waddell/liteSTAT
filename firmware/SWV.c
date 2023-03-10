
/* Project: POTENTIOSTAT FIRMWARE
 * File: LSV.c
 * Created: 04/01/2018
 * Author: Stuart Waddell
 * Robert Gordon University
 * School of Pharmacy and Life Sciences
 */ 

#include "main.h"

void SWV (void)
{
	SCAN_NUMBER = 1;
	SCAN_LED_ON;
	CE_ON;
	CELL_ON;
	_delay_ms(500);
	DAC_LEVEL = GET_INITIAL (DEPOSITION_V);
	SET_DAC();
	MEASURE_START = ACTUAL_MILLIS;
	printf("2222,2222,2222,\n");
	while (ACTUAL_MILLIS < MEASURE_START + DEPOSITION_T)
	{
	}
	PWR_LED_OFF;
	MEASURE_START = ACTUAL_MILLIS;
	printf("3333,3333,3333,\n");
	while (ACTUAL_MILLIS < MEASURE_START + EQUILIBRIUM_T)
	{
	}
	VOLTAGE = MEASURE_VOLTAGE();
	DAC_LEVEL = GET_INITIAL (START_I);
	SET_DAC();
	VOLTAGE = MEASURE_VOLTAGE();
	printf ("5555,5555,5555,\n");
	if (VOLTAGE >= STOP_I)
	{
		 SWV_DOWN ();
	}
	else 
	{
		SWV_UP ();
	}
	INPUT_RECEIVED = 0;
	FIRST_PASS = 1;
	SCAN_LED_OFF;
	PWR_LED_ON;
	DAC_LEVEL = DAC_START;
	SET_DAC();
	CE_OFF;
	CELL_OFF;
	printf("7775,%lu,%d,\n9999,9999,%d,\n", (ACTUAL_MILLIS - RUN_START), SCAN_NUMBER, SCAN_NUMBER);
	
}

void SWV_DOWN (void)
{
	printf ("9876,9876,%d,\n", SCAN_NUMBER);
	while (VOLTAGE > STOP_I)
	{
		MEASURE_START = ACTUAL_MILLIS;
		DAC_LEVEL = DAC_LEVEL - (STEP + PULSE);
		TEST_DAC_RANGE();
		SET_DAC();
		TEST_REF_RANGE();
		while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
		{
		}
		CURRENT_CATHODIC = MEASURE_CURRENT();
		TEST_WE_RANGE();
		MEASURE_START = ACTUAL_MILLIS;
		DAC_LEVEL += PULSE;
		TEST_DAC_RANGE();
		SET_DAC();
		TEST_REF_RANGE();
		while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
		{
		}
		VOLTAGE = MEASURE_VOLTAGE();
		CURRENT_ANODIC = MEASURE_CURRENT();
		TEST_WE_RANGE();
		CURRENT = CURRENT_CATHODIC - CURRENT_ANODIC;
		printf ("%d,%d,%d,\n", VOLTAGE, CURRENT, SCAN_NUMBER);
	}
	
}

void SWV_UP (void)
{
	printf ("6789,6789,%d,\n", SCAN_NUMBER);
	while (VOLTAGE < STOP_I)
	{
		MEASURE_START = ACTUAL_MILLIS;
		DAC_LEVEL = DAC_LEVEL + STEP + PULSE;
		TEST_DAC_RANGE();
		SET_DAC();
		TEST_REF_RANGE();
		while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
		{
		}
		CURRENT_ANODIC = MEASURE_CURRENT();
		TEST_WE_RANGE();
		MEASURE_START = ACTUAL_MILLIS;
		DAC_LEVEL -= PULSE;
		TEST_DAC_RANGE();
		SET_DAC();
		TEST_REF_RANGE();
		while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
		{
		}
		VOLTAGE = MEASURE_VOLTAGE();
		CURRENT_CATHODIC = MEASURE_CURRENT();
		TEST_WE_RANGE();
		CURRENT = CURRENT_ANODIC - CURRENT_CATHODIC;
		printf ("%d,%d,%d,\n", VOLTAGE, CURRENT, SCAN_NUMBER);
	}
	
}