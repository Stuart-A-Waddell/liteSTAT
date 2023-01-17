/* Project: POTENTIOSTAT FIRMWARE
 * File: main.c
 * Created: 04/01/2018
 * Author: Stuart Waddell
 * Robert Gordon University
 * School of Pharmacy and Life Sciences
 */ 

#include <avr/io.h>
#include "main.h"


ISR (TIMER1_COMPA_vect)
{
	ACTUAL_MILLIS++;
}


int main (void)
{
	SPI_INITIALISE ();
	UART_INITIALISE (MYUBRR);
	BOARD_INITIALISE ();
	INPUT_RECEIVED = 0;
	FIRST_PASS = 1;
	TCCR1B |= (1<<CS11)|(1<<WGM12);
	OCR1AH = (CTC_MATCH_OVERFLOW >> 8);
	OCR1AL = CTC_MATCH_OVERFLOW;
	TIMSK1 |= (1<<OCIE1A);
	sei();
	stdout = &mystdout;
    while (1) 
    {
		UART_RX_STRING ();
 		if (INPUT_RECEIVED)
 		{
 			
 			ACTUAL_MILLIS = 0;			
 			if (COMPLIANCE == 2)
 			{
 				SET_COMPLIANCE_HI;
 			} 
 			else
 			{
 				SET_COMPLIANCE_LO;
 			}
 			switch (METHOD)
 			{
 				case 1:
 					CV ();
 					break;
 				case 2:
 					LSV ();
 					break;
 				case 3:
 					SWV ();
 					break;
 				case 4:
 					// CHRONOAMPEROMETRY
 					break;
				case 5:
					VOLTAGE_ALPHA_TEST();
					break;
				case 6:
					CURRENT_ALPHA_TEST();
					break;
 				case 9:
 					// PORT CHECK
 					break;
 				default:
 					INPUT_RECEIVED = 0;
					UART_TX_STRING("333333");
					break;
			}
 		}
	}
}

void BOARD_INITIALISE (void)
{
	DDRD |= (1<<PWR_LED)|(1<<SCAN_LED)|(1<<CE_RELAY)|(1<<COMPLIANCE_RELAY)|(1<<CELL_RELAY);
	DDRC |= (1<<PORTC0)|(1<<PORTC1)|(1<<PORTC2)|(1<<PORTC3);
	PORTC &= ~(1<<PORTC3);
	FEEDBACK = 4;
	SET_FEEDBACK(FEEDBACK);
	PWR_LED_ON;
	SCAN_LED_OFF;
	SET_COMPLIANCE_LO;
	DAC_LEVEL = 64500;
	SET_DAC();
	CE_OFF;
	CELL_OFF;
}



