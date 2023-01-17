/* Project: POTENTIOSTAT FIRMWARE
 * File: UART.c
 * Created: 04/01/2018
 * Author: Stuart Waddell
 * Robert Gordon University
 * School of Pharmacy and Life Sciences
 */ 
#include "main.h"

void UART_INITIALISE(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	
}

void UART_TX_STRING (char* StringPtr)
{
	while(*StringPtr != 0x00)			// Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null char
	{
		UART_TX_CHAR (*StringPtr);		// Using the simple send function we send one char at a time
		StringPtr++;					// We increment the pointer so we can read the next char
	}
}

void UART_TX_CHAR (unsigned char data)  // Transmit character through UART
{
	UDR0 = data;					//put the data to be transmitted into the UDR register
	while(!(UCSR0A&(1<<UDRE0)));	//wait until the transmission is completed
}

//Receive a character through UART
unsigned char UART_RX_CHAR (void)
{
	//wait for the character
	while(!(UCSR0A & (1<<RXC0)));

	//return the received character
	return(UDR0);
}

//Receive string through UART
unsigned char * UART_RX_STRING (void)
{
	INPUT_COUNTER = 0;
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) )
	{
		dummy = UDR0;
	}
	//receive the characters until exclamation mark (ASCII for "!" = 33)
	while((INPUT_CHAR = UART_RX_CHAR ()) != 33)
	{
		//and store the received characters into the array string[] one-by-one
		INPUT_STRING[INPUT_COUNTER++] = INPUT_CHAR;
	}
	INPUT_RECEIVED = 1;
	//insert NULL to terminate the string
	INPUT_STRING[INPUT_COUNTER] = '\0';
	//length = strlen(string);
	METHOD = 0;
	COMPLIANCE = 0;
	POT_I = 0;
	START_I = 0;
	STOP_I = 0;
	CYCLES_I = 0;
	RATE_I = 0;
	WAIT = 0;
	STEP = 0;
	DEPOSITION_V = 0;
	DEPOSITION_T = 0;
	EQUILIBRIUM_T = 0;
	PULSE = 0;
	HOLD_GAIN = 0;
	ALPHA = 0;
	ALPHA_SHIFT = 0;
	VOLTAGE_SHIFTER = 0;
	CURRENT_SHIFTER = 0;
	VOLTAGE_MEASUREMENT_NUMBER = 0;
	CURRENT_MEASUREMENT_NUMBER = 0;
	METHOD = INPUT_STRING[0] - '0';
	COMPLIANCE = INPUT_STRING[1] - '0';
	for(INPUT_COUNTER=2; INPUT_COUNTER<6; INPUT_COUNTER++){
		POT_I = POT_I * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=6; INPUT_COUNTER<10; INPUT_COUNTER++){
		START_I = START_I * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=10; INPUT_COUNTER<14; INPUT_COUNTER++){
		STOP_I = STOP_I * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=14; INPUT_COUNTER<17; INPUT_COUNTER++){
		CYCLES_I = CYCLES_I * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=17; INPUT_COUNTER<21; INPUT_COUNTER++){
		WAIT = WAIT * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=21; INPUT_COUNTER<25; INPUT_COUNTER++){
		VOLTAGE_MEASUREMENT_NUMBER = VOLTAGE_MEASUREMENT_NUMBER * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=25; INPUT_COUNTER<29; INPUT_COUNTER++){
		CURRENT_MEASUREMENT_NUMBER = CURRENT_MEASUREMENT_NUMBER * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=29; INPUT_COUNTER<33; INPUT_COUNTER++){
		STEP = STEP * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=33; INPUT_COUNTER<37; INPUT_COUNTER++){
		DEPOSITION_V = DEPOSITION_V * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	} 
	for(INPUT_COUNTER=37; INPUT_COUNTER<41; INPUT_COUNTER++){
		DEPOSITION_T = DEPOSITION_T * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=41; INPUT_COUNTER<45; INPUT_COUNTER++){
		EQUILIBRIUM_T = EQUILIBRIUM_T * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=45; INPUT_COUNTER<49; INPUT_COUNTER++){
		PULSE = PULSE * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=49; INPUT_COUNTER<50; INPUT_COUNTER++){
		HOLD_GAIN = HOLD_GAIN * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=50; INPUT_COUNTER<53; INPUT_COUNTER++){
		ALPHA = ALPHA * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	for(INPUT_COUNTER=53; INPUT_COUNTER<54; INPUT_COUNTER++){
		ALPHA_SHIFT = ALPHA_SHIFT * 10 + ( INPUT_STRING[INPUT_COUNTER] - '0' );
	}
	POT_I -= 1000;
	FEEDBACK = POT_I;
	SET_FEEDBACK(FEEDBACK);
	START_I -= 4096;
	STOP_I -= 4096;
	CYCLES_I -= 100;	
	WAIT -= 1000;
	PULSE -= 1000;
	VOLTAGE_MEASUREMENT_NUMBER -= 1000;
	CURRENT_MEASUREMENT_NUMBER -= 1000;
	/*
	SPARE_CURRENT_MEASUREMENT_NUMBER = CURRENT_MEASUREMENT_NUMBER - 256;
	SPARE_VOLTAGE_MEASUREMENT_NUMBER = VOLTAGE_MEASUREMENT_NUMBER - 64;
	*/
	STEP -= 1000;
	DEPOSITION_V -= 4096;
	DEPOSITION_T -= 1000;
	EQUILIBRIUM_T -= 1000;
	DEPOSITION_T *= 1000;
	EQUILIBRIUM_T *= 1000;
	ALPHA -= 100;
	//ALPHA_CALC_FLOAT = log((ALPHA + 1)) / log (2);	This code doesn't work brings a zero for ALPHA_SHIFT
	//ALPHA_SHIFT = (int) ALPHA_CALC;					so using switch/case below instead
// 	switch (ALPHA)
// 	{
// 	case 3:
// 		ALPHA_SHIFT = 2;
// 		break;
// 	case 7:
// 		ALPHA_SHIFT = 3;
// 		break;
// 	case 15:
// 		ALPHA_SHIFT = 4;
// 		break;
// 	case 31:
// 		ALPHA_SHIFT = 5;
// 		break;
// 	case 63:
// 		ALPHA_SHIFT = 6;
// 		break;
// 	case 127:
// 		ALPHA_SHIFT = 7;
// 		break;
// 	default:
// 		ALPHA_SHIFT = 3;
// 		break;
// 	}
	switch (VOLTAGE_MEASUREMENT_NUMBER)
	{
	case 16:
		VOLTAGE_SHIFTER = 3;
		break;
	case 32:
		VOLTAGE_SHIFTER = 4;
		break;
	case 64:
		VOLTAGE_SHIFTER = 5;
		break;
	case 128:
		VOLTAGE_SHIFTER = 6;
		break;
	default:
		VOLTAGE_SHIFTER = 3;
		break; 
	}
	switch (CURRENT_MEASUREMENT_NUMBER)
	{
	case 16:
		CURRENT_SHIFTER = 3;
		break;
	case 32:
		CURRENT_SHIFTER = 4;
		break;
	case 64:
		CURRENT_SHIFTER = 5;
		break;
	case 128:
		CURRENT_SHIFTER = 6;
		break;
	case 256:
		CURRENT_SHIFTER = 7;
		break;
	case 512:
		CURRENT_SHIFTER = 8;
		break;
	case 1024:
		CURRENT_SHIFTER = 9;
		break;
	default:
		CURRENT_SHIFTER = 3;
		break;
	}
	/*
 	printf("3216,%d,%d,\n", ALPHA, ALPHA_SHIFT);
 	printf("3216,%d,%d,\n", VOLTAGE_MEASUREMENT_NUMBER, CURRENT_MEASUREMENT_NUMBER);
 	printf("3216,%d,%d,\n", VOLTAGE_SHIFTER, CURRENT_SHIFTER);
	 */
	if (START_I > STOP_I)
	{
		START_I += 50;
	} 
	else
	{
		START_I -= 50;
	}
	while ( UCSR0A & (1<<RXC0) )
	{
		dummy = UDR0;
	}
	//return the received an unsigned char*
	unsigned char *returner = NULL;
	return (returner);
}
void TRANSMIT (void)
{
	printf ("%d,%d,\n", VOLTAGE, CURRENT);
	/*
	itoa (VOLTAGE, VOLTAGE_BUFFER, 10);
	UART_TX_STRING (VOLTAGE_BUFFER);
	UART_TX_STRING(",");
	itoa (CURRENT, CURRENT_BUFFER, 10);
	UART_TX_STRING (CURRENT_BUFFER);
	UART_TX_STRING(",\n");
	*/
}

void TRANSMIT_UNFILTERED (void)
{
	itoa (VOLTAGE, VOLTAGE_BUFFER, 10);
	UART_TX_STRING (VOLTAGE_BUFFER);
	UART_TX_STRING(",");
	itoa (CURRENT, CURRENT_BUFFER, 10);
	UART_TX_STRING (CURRENT_BUFFER);
	UART_TX_STRING(",\n");
}

//this function is called by printf as a stream handler
int usart_putchar_printf(char var, FILE *stream) 
{
	// translate \n to \r for br@y++ terminal
	if (var == '\n') UART_TX_CHAR('\r');
	UART_TX_CHAR(var);
	return 0;
}
