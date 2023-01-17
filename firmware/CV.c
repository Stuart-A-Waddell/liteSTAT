
/* Project: POTENTIOSTAT FIRMWARE
 * File: LSV.c
 * Created: 04/01/2018
 * Author: Stuart Waddell
 * Robert Gordon University
 * School of Pharmacy and Life Sciences
 */ 

#include "main.h"

void CV (void)
{
	SCAN_NUMBER = 1;
	SCAN_LED_ON;
	CE_ON;
	CELL_ON;
	_delay_ms(500);
	DAC_LEVEL = GET_INITIAL (START_I);
	SET_DAC();
	TEST_DAC_RANGE();
	TEST_REF_RANGE();
	PWR_LED_OFF;
	
	VOLTAGE = MEASURE_VOLTAGE();
	{
		if (VOLTAGE >= STOP_I)
		{
			CV_DOWN_FIRST ();
		}
		else
		{
			CV_UP_FIRST ();
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

void CV_DOWN_FIRST (void)
{
	for (CYCLES = 0; CYCLES < CYCLES_I; CYCLES++)
	{
		printf ("9876,9876,%d,\n", SCAN_NUMBER);
		TEST_REF_RANGE();
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
			if (FIRST_PASS)
			{
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
			else
			{
				printf ("%d,%d,%d,\n", VOLTAGE, CURRENT, SCAN_NUMBER);
				TEST_WE_RANGE();
			}
		}
		TEST_REF_RANGE();
		if (FIRST_PASS)
		{
			START_I -= 50;
			FIRST_PASS = 0;
		}
		printf ("6789,6789,%d,\n", SCAN_NUMBER);
		while (VOLTAGE < START_I)
		{
			MEASURE_START = ACTUAL_MILLIS;
			DAC_LEVEL += STEP;
			TEST_DAC_RANGE();
			SET_DAC();
			while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
			{
			}
			VOLTAGE = MEASURE_VOLTAGE();
			CURRENT = MEASURE_CURRENT();
			printf ("%d,%d,%d,\n", VOLTAGE, CURRENT, SCAN_NUMBER);
			TEST_WE_RANGE();
		}
		SCAN_NUMBER++;
		TEST_REF_RANGE();
	}
}

void CV_UP_FIRST (void)
{
	for (CYCLES = 0; CYCLES < CYCLES_I; CYCLES++)
	{
		printf ("6789,6789,%d,\n", SCAN_NUMBER);
		while (VOLTAGE < STOP_I)
		{
			MEASURE_START = ACTUAL_MILLIS;
			DAC_LEVEL += STEP;
			TEST_DAC_RANGE();
			SET_DAC();
			while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
			{
			}
			VOLTAGE = MEASURE_VOLTAGE();
			CURRENT = MEASURE_CURRENT();
			if (FIRST_PASS)
			{
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
			else
			{
				printf ("%d,%d,%d,\n", VOLTAGE, CURRENT, SCAN_NUMBER);
				TEST_WE_RANGE();
			}
		}
		TEST_REF_RANGE();
		if (FIRST_PASS)
		{
			START_I += 50;
			FIRST_PASS = 0;
		}
		printf ("9876,9876,%d,\n", SCAN_NUMBER);
		while (VOLTAGE > START_I)
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
			printf ("%d,%d,%d,\n", VOLTAGE, CURRENT, SCAN_NUMBER);
			TEST_WE_RANGE();
		}
		SCAN_NUMBER++;
		TEST_REF_RANGE();
	}
}
