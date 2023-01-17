/* Project: POTENTIOSTAT FIRMWARE
 * File: main.h
 * Created: 04/01/2018
 * Author: Stuart Waddell
 * Robert Gordon University
 * School of Pharmacy and Life Sciences
 */ 

#include "main.h"

void LSV (void)
{
	SCAN_NUMBER = 1;
	SCAN_LED_ON;
	CE_ON;
	CELL_ON;
	_delay_ms(500);
	DAC_LEVEL = GET_INITIAL (START_I);
	TEST_DAC_RANGE();
	SET_DAC();
	TEST_REF_RANGE();
	PWR_LED_OFF;
	VOLTAGE = MEASURE_VOLTAGE();
	{
		if (VOLTAGE >= STOP_I)
		{
			LSV_DOWN ();
		}
		else
		{
			LSV_UP ();
		}
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

void LSV_DOWN (void)
{
	printf ("9876,9876,%d,\n", SCAN_NUMBER);
	while (VOLTAGE > STOP_I)
	{
		MEASURE_START = ACTUAL_MILLIS;
		DAC_LEVEL -= STEP;
		TEST_DAC_RANGE();
		SET_DAC();
		while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
		{
		}
		VOLTAGE = MEASURE_VOLTAGE();
		CURRENT = MEASURE_CURRENT();
		if (VOLTAGE < (START_I - 50))
		{
			printf ("%d,%d,%d,\n", VOLTAGE, CURRENT, SCAN_NUMBER);
			TEST_WE_RANGE();
		}
		else
		{
			RUN_START = ACTUAL_MILLIS;
			TEST_WE_RANGE();
		}
	}
}

void LSV_UP (void)
{
	printf ("6789,6789,%d,\n", SCAN_NUMBER);
	while (VOLTAGE < STOP_I)
	{
		MEASURE_START = ACTUAL_MILLIS;
		DAC_LEVEL += STEP;
		SET_DAC();
		TEST_DAC_RANGE();
		while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
		{
		}
		VOLTAGE = MEASURE_VOLTAGE();
		CURRENT = MEASURE_CURRENT();
		if (VOLTAGE > (START_I + 50))
		{
			printf ("%d,%d,%d,\n", VOLTAGE, CURRENT, SCAN_NUMBER);
			TEST_WE_RANGE();
		}
		else
		{
			RUN_START = ACTUAL_MILLIS;
			TEST_WE_RANGE();
		}
	}
}
