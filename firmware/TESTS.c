
/* Project: POTENTIOSTAT FIRMWARE
 * File: TESTS.c
 * Created: 04/01/2018
 * Author: Stuart Waddell
 * Robert Gordon University
 * School of Pharmacy and Life Sciences
 */ 

#include "main.h"

void SET_FEEDBACK (int FEEDBACK)
{
	PORTC = FEEDBACK;
}

unsigned int GET_INITIAL (int INITIAL_V)
{
	DAC_LEVEL = DAC_START;
	SET_DAC ();
	VOLTAGE = MEASURE_VOLTAGE ();
	if (VOLTAGE > INITIAL_V)
	{
		while (VOLTAGE > INITIAL_V)
		{
			DAC_LEVEL -=50;
			TEST_DAC_RANGE();
			SET_DAC();
			_delay_ms(40);
			VOLTAGE = MEASURE_VOLTAGE();
		}
	}
	else
	{
		while (VOLTAGE < INITIAL_V)
		{
			DAC_LEVEL +=50;
			TEST_DAC_RANGE();
			SET_DAC();
			_delay_ms(40);
			VOLTAGE = MEASURE_VOLTAGE();
		}
	}
	_delay_ms(LONG_WAIT);
	TEST_REF_RANGE();
	VOLTAGE = MEASURE_VOLTAGE();
	if (VOLTAGE > INITIAL_V)
	{
		while (VOLTAGE > INITIAL_V)
		{
			DAC_LEVEL -=10;
			TEST_DAC_RANGE();
			SET_DAC();
			TEST_REF_RANGE();
			_delay_ms(40);
			VOLTAGE = MEASURE_VOLTAGE();
		}
	}
	else
	{
		while (VOLTAGE < INITIAL_V)
		{
			DAC_LEVEL +=10;
			TEST_DAC_RANGE();
			SET_DAC();
			TEST_REF_RANGE();
			_delay_ms(40);
			VOLTAGE = MEASURE_VOLTAGE();
		}
	}
	_delay_ms(LONG_WAIT);
	TEST_REF_RANGE();
	VOLTAGE = MEASURE_VOLTAGE();
	if (VOLTAGE > INITIAL_V)
	{
		while (VOLTAGE > INITIAL_V)
		{
			DAC_LEVEL--;
			SET_DAC();
			TEST_DAC_RANGE();
			_delay_ms(20);
			VOLTAGE = MEASURE_VOLTAGE();
		}
	}
	else
	{
		while (VOLTAGE < INITIAL_V)
		{
			DAC_LEVEL++;
			SET_DAC();
			TEST_DAC_RANGE();
			_delay_ms(20);
			VOLTAGE = MEASURE_VOLTAGE();
		}
	}
	TEST_REF_RANGE();
	return (DAC_LEVEL);
}

void TEST_WE_RANGE (void)
{
	if (HOLD_GAIN > 1)
	{
		
	} 
	else
	{
		if (CURRENT > 1800 || CURRENT < -1800)
		{
			FEEDBACK++;
			if (FEEDBACK > 7)
			{
				FEEDBACK = 7;
			}
			SET_FEEDBACK (FEEDBACK);
			printf ("8765,8765,%d,\n", FEEDBACK);
		}
	}
}

void TEST_DAC_RANGE (void)
{
	if (DAC_LEVEL >= DAC_MAX || DAC_LEVEL <= DAC_MIN)
	{
		DAC_LEVEL = DAC_START;
		SET_DAC();
		UART_TX_STRING("7778,7778,1,\n");
		PWR_LED_ON;
		SCAN_LED_OFF;
		CE_OFF;
		CELL_OFF;
		main();
	}
}
void TEST_REF_RANGE (void)
{
	ADC_SELECT;
	SPI_CHAR (0b00001100);
	ADC_HI = SPI_CHAR (0b10000000);
	ADC_LO = SPI_CHAR (0b00000000);
	ADC_DESELECT;
	ADC_READING = ADC_HI << 8;
	ADC_READING += ADC_LO;
	ADC_READING = ADC_READING << 3;
	ADC_READING = ADC_READING / 8;
	if (ADC_READING > 4090 || ADC_READING < 10)
	{
		DAC_LEVEL = DAC_START;
		SET_DAC();
		UART_TX_STRING("7779,7779,1,\n");
		PWR_LED_ON;
		SCAN_LED_OFF;
		CE_OFF;
		CELL_OFF;
		main();
	}
}
/*
void PRINT_TESTS (void)
{
	UART_TX_STRING("DAC_LEVEL\n");
	printf ("%u", DAC_LEVEL);
	UART_TX_STRING("\n");
	UART_TX_STRING("VOLTAGE, START_I\n");
	TRANSMIT ();
}
*/

/*
void timer_trial (void)
{
	
	while (1)
	{
		MILLIS_START = millis ();
		while ((millis() - MILLIS_START) < 1000)
		{
		}
		UART_TX_STRING("7775,");
		printf("%lu", millis());
		UART_TX_STRING(",\n");
	}
}
*/
/*
void speedTest (void)
{
	SCAN_LED_ON;
	CE_ON;
	CELL_ON;
	_delay_ms(500);
	DAC_LEVEL = GET_INITIAL (START_I);
	SET_DAC();
	PWR_LED_OFF;
	VOLTAGE = MEASURE_VOLTAGE();
	for (CYCLES = 0; CYCLES < CYCLES_I; CYCLES++)
	{
		while (VOLTAGE > STOP_I)
		{
			DAC_LEVEL--;
			SET_DAC();
			_delay_us (100);
			VOLTAGE = READ_VOLTAGE();
			CURRENT = READ_CURRENT();
			if (FIRST_PASS)
			{
				if (VOLTAGE < (START_I - 50))
				{
					TRANSMIT ();
				}
				else
				{
					RUN_START = ACTUAL_MILLIS;
				}
			}
			else
			{
				TRANSMIT ();
			}
		}
		if (FIRST_PASS)
		{
			START_I -= 50;
			FIRST_PASS = 0;
		}
		while (VOLTAGE < START_I)
		{
			DAC_LEVEL++;
			SET_DAC();
			_delay_us (100);
			VOLTAGE = READ_VOLTAGE();
			CURRENT = READ_CURRENT();
			TRANSMIT ();
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
	UART_TX_STRING("7775,");
	printf("%lu", (ACTUAL_MILLIS - RUN_START));
	UART_TX_STRING(",\n");
	UART_TX_STRING("9999,9999,\n");	
}
*/