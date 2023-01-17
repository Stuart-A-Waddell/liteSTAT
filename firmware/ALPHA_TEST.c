/*
 * ALPHA_TEST.c
 *
 * Created: 25/07/2018 19:59:52
 *  Author: Stuart
 */ 

/* Project: POTENTIOSTAT FIRMWARE
 * File: main.h
 * Created: 04/01/2018
 * Author: Stuart Waddell
 * Robert Gordon University
 * School of Pharmacy and Life Sciences
 */ 

#include "main.h"

void VOLTAGE_ALPHA_TEST (void)
{
	SCAN_NUMBER = 1;
	SCAN_LED_ON;
	CE_ON;
	CELL_ON;
	_delay_ms(500);
	DAC_LEVEL = GET_INITIAL (START_I);
	SET_DAC();
	PWR_LED_OFF;
	VOLTAGE = MEASURE_VOLTAGE();
	{
		if (VOLTAGE >= STOP_I)
		{
			VOLTAGE_ALPHA_DOWN ();
		}
		else
		{
			VOLTAGE_ALPHA_UP ();
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
	//  For Voltage alpha test only ////////////////////////////////////////////////////////////
	// printf("CELL:\tDummy Cell\tWE:\tNot app\tParameter:\tVoltage\tMeasurements Number:\t%d\tPre-Wait\t%d\tDAC step:\t%d\tPoint Range:\t%d\tTime:\t%lu\n", VOLTAGE_MEASUREMENT_NUMBER, WAIT, STEP, POINT_NUMBER, (ACTUAL_MILLIS - RUN_START));
	printf ("7775,7775,%d,\n", POINT_NUMBER);
	_delay_ms(100);
	printf ("9999,9999,%lu,\n", (ACTUAL_MILLIS - RUN_START));
	///////////////////////////////////////////////////////////////////////////////////////////
	
}

void VOLTAGE_ALPHA_DOWN (void)
{
	RUN_START = ACTUAL_MILLIS;
	POINT_NUMBER = 0;
	while (VOLTAGE > STOP_I)
	{
		MEASURE_START = ACTUAL_MILLIS;
		DAC_LEVEL -= STEP;
		SET_DAC();
		TEST_DAC_RANGE();
		TEST_REF_RANGE();
		for (int WAITER = 0; WAITER < WAIT; WAITER++)
		{
		}
		while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
		{
		}
		for (int i = 0; i < VOLTAGE_MEASUREMENT_NUMBER; i++)
		{
			VOLTAGE = READ_VOLTAGE();
			printf("%d,%d,%d,\n", POINT_NUMBER, i, VOLTAGE);
		}
		POINT_NUMBER++;
	}
}

void VOLTAGE_ALPHA_UP (void)
{
	RUN_START = ACTUAL_MILLIS;
	POINT_NUMBER = 0;
	while (VOLTAGE < STOP_I)
	{
		MEASURE_START = ACTUAL_MILLIS;
		DAC_LEVEL += STEP;
		SET_DAC();
		TEST_DAC_RANGE();
		TEST_REF_RANGE();
		for (int WAITER = 0; WAITER < WAIT; WAITER++)
		{
		}
		while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
		{
		}
		for (int i = 0; i < VOLTAGE_MEASUREMENT_NUMBER; i++)
		{
			VOLTAGE = READ_VOLTAGE();
			printf("%d,%d,%d,\n", POINT_NUMBER, i, VOLTAGE);
		}
		POINT_NUMBER++;
	}
}
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // Current section
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 void CURRENT_ALPHA_TEST (void)
 {
	 SCAN_NUMBER = 1;
	 SCAN_LED_ON;
	 CE_ON;
	 CELL_ON;
	 _delay_ms(500);
	 DAC_LEVEL = GET_INITIAL (START_I);
	 SET_DAC();
	 PWR_LED_OFF;
	 VOLTAGE = MEASURE_VOLTAGE();
	 {
		 if (VOLTAGE >= STOP_I)
		 {
			 CURRENT_ALPHA_DOWN ();
		 }
		 else
		 {
			 CURRENT_ALPHA_UP ();
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
	 printf ("7775,7775,%d,\n", POINT_NUMBER);
	 _delay_ms(100);
	 printf ("9999,9999,%lu,\n", (ACTUAL_MILLIS - RUN_START));	 
 }

 void CURRENT_ALPHA_DOWN (void)
 {
	 RUN_START = ACTUAL_MILLIS;
	 POINT_NUMBER = 0;
	 while (VOLTAGE > STOP_I)
	 {
		 MEASURE_START = ACTUAL_MILLIS;
		 DAC_LEVEL -= STEP;
		 SET_DAC();
		 TEST_DAC_RANGE();
		 TEST_REF_RANGE();
		 for (int WAITER = 0; WAITER < WAIT; WAITER++)
		 {
		 }
		 while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
		 {
		 }
		 VOLTAGE = READ_VOLTAGE();
		 for (int i = 0; i < VOLTAGE_MEASUREMENT_NUMBER; i++)
		 {
			 CURRENT = READ_CURRENT();
			 printf("%d,%d,%d,\n", POINT_NUMBER, i, CURRENT);
		 }
		 POINT_NUMBER++;
	 }
 }

 void CURRENT_ALPHA_UP (void)
 {
	 RUN_START = ACTUAL_MILLIS;
	 POINT_NUMBER = 0;
	 while (VOLTAGE < STOP_I)
	 {
		 MEASURE_START = ACTUAL_MILLIS;
		 DAC_LEVEL += STEP;
		 SET_DAC();
		 TEST_DAC_RANGE();
		 TEST_REF_RANGE();
		 for (int WAITER = 0; WAITER < WAIT; WAITER++)
		 {
		 }
		 while (ACTUAL_MILLIS < (MEASURE_START + WAIT))
		 {
		 }
		 VOLTAGE = READ_VOLTAGE();
		 for (int i = 0; i < VOLTAGE_MEASUREMENT_NUMBER; i++)
		 {
			 CURRENT = READ_CURRENT();
			 printf("%d,%d,%d,\n", POINT_NUMBER, i, CURRENT);
		 }
		 POINT_NUMBER++;
	 }
 }


