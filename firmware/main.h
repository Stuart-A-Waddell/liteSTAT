
/* Project: POTENTIOSTAT FIRMWARE
 * File: main.h
 * Created: 04/01/2018
 * Author: Stuart Waddell
 * Robert Gordon University
 * School of Pharmacy and Life Sciences
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define PWR_LED_ON			PORTD |= (1<<PORTD2)
#define PWR_LED_OFF			PORTD &= ~(1<<PORTD2)
#define SCAN_LED_ON			PORTD |= (1<<PORTD3)
#define SCAN_LED_OFF		PORTD &= ~(1<<PORTD3)
#define CE_ON				PORTD |= (1<<PORTD4)
#define CE_OFF				PORTD &= ~(1<<PORTD4)
#define SET_COMPLIANCE_HI	PORTD |= (1<<PORTD5)
#define SET_COMPLIANCE_LO	PORTD &= ~(1<<PORTD5)
#define CELL_ON				PORTD |= (1<<PORTD6)
#define CELL_OFF			PORTD &= ~(1<<PORTD6)


#define POT_SELECT			PORTB &= ~(1<<PORTB0)
#define POT_DESELECT		PORTB |= (1<<PORTB0)
#define ADC_SELECT			PORTB &= ~(1<<PORTB1)
#define ADC_DESELECT		PORTB |= (1<<PORTB1)
#define DAC_SELECT			PORTB &= ~(1<<PORTB2)
#define DAC_DESELECT		PORTB |= (1<<PORTB2)

#define SPI_WAIT			while(!(SPSR & (1<<SPIF)))

#define POT_SS				PORTB0 // Slave selects
#define ADC_SS				PORTB1
#define DAC_SS				PORTB2
#define MOSI				PORTB3
#define MISO				PORTB4
#define SPI_CLK				PORTB5
#define PWR_LED				PORTD2
#define SCAN_LED			PORTD3
#define CE_RELAY			PORTD4
#define COMPLIANCE_RELAY	PORTD5
#define CELL_RELAY			PORTD6

#define FOSC 16000000UL // Clock Speed
#define BAUD 1000000UL
#define MYUBRR FOSC/16/BAUD-1
#define CTC_MATCH_OVERFLOW ((F_CPU / 1000) / 8) 

#define DAC_MIN				61440
#define DAC_MID				63500
#define DAC_MAX				65500
#define DAC_START			63500
#define POT_START			10
#define SHORT_WAIT			10
#define LONG_WAIT			100
#define PRE_WAIT			10

/* 
	ADC CHANNELS:	CH0 WE_RAW
					CH1	REF_SIG
					CH2	WE_SIG
					CH3 +2V5
					CH4	NC
					CH5 NC
					CH6 NC
					CH7 NC

*/
#define ADC_VOLTAGE_CONFIG1		0b00001000
#define ADC_VOLTAGE_CONFIG2		0b00000000
#define ADC_VOLTAGE_CONFIG3		0b00000000
#define ADC_CURRENT_CONFIG1		0b00001001
#define ADC_CURRENT_CONFIG2		0b00000000
#define ADC_CURRENT_CONFIG3		0b00000000
#define ADC_CURRENT_CONFIG4		0b00001010
#define ADC_CURRENT_CONFIG5		0b00000000
#define ADC_CURRENT_CONFIG6		0b00000000
#define POT_CONFIG				0b00000000

int INPUT_RECEIVED, ADC_READING, VOLTAGE, CURRENT, START_I, STOP_I, CYCLES_I, RATE_I, POT_I, COMPLIANCE;
int VOLTAGE_MEASUREMENT_NUMBER, CURRENT_MEASUREMENT_NUMBER, METHOD, CYCLES, WAIT, STEP, FIRST_PASS;
int CURRENT_CATHODIC, CURRENT_ANODIC, OLD_VOLTAGE, OLD_CURRENT;
int DEPOSITION_V, DEPOSITION_T, EQUILIBRIUM_T, PULSE, INITIAL_V;
int SCAN_NUMBER;
int FEEDBACK, HOLD_GAIN;
unsigned int DAC_LEVEL, MEASUREMENTS;
long int VOLTAGE_ADDER, CURRENT_ADDER;
volatile unsigned long ACTUAL_MILLIS;
unsigned long MILLIS_START, RUN_START, MEASURE_START;
char VOLTAGE_BUFFER[20], CURRENT_BUFFER[20], INPUT_COUNTER, INPUT_STRING[128], INPUT_CHAR;
unsigned char DAC_LO, DAC_HI, ADC_HI, ADC_LO, POT_LEVEL, junk1, junk2;
int az, ARRAY_COUNTER;
/*
int OLD_VOLTAGE_ARRAY[16];
int OLD_CURRENT_ARRAY[512];
*/
int SPARE_VOLTAGE_MEASUREMENT_NUMBER, SPARE_CURRENT_MEASUREMENT_NUMBER, VOLTAGE_SHIFTER, CURRENT_SHIFTER;
int ALPHA, ALPHA_SHIFT, POINT_NUMBER;
int NEW_VOLTAGE, NEW_CURRENT;
float ALPHA_CALC_FLOAT;


int main (void);
void SPI_INITIALISE (void);
void BOARD_INITIALISE (void);
void SET_DAC (void);
int READ_VOLTAGE (void);
unsigned char SPI_CHAR (unsigned char CONFIG_SETTING);
void UART_INITIALISE (unsigned int ubrr);
void UART_TX_STRING (char* StringPtr);
void UART_TX_CHAR (unsigned char data);
unsigned char UART_RX_CHAR (void);
unsigned char * UART_RX_STRING (void);
void SET_POT (void);
int READ_CURRENT (void);
void CV ();
unsigned int GET_INITIAL (int INITIAL_V);
int MEASURE_VOLTAGE ();
int MEASURE_CURRENT ();
void TEST_DAC_RANGE (void);
void TEST_REF_RANGE (void);
void CV_DOWN_FIRST ();
void CV_UP_FIRST ();
void TRANSMIT ();
void LSV ();
void LSV_DOWN ();
void LSV_UP ();
void PRINT_TESTS ();
int usart_putchar_printf(char var, FILE *stream);
void LSV_TEST ();
void LSV_DOWN_TEST ();
void LSV_UP_TEST ();
void speedTest (void);
void TRANSMIT_UNFILTERED (void);
void TEST_WE_RANGE (void);
void SWV (void);
int READ_PULSE_CURRENT (void);
void SWV_DOWN (void);
void SWV_UP (void);
void SET_FEEDBACK (int FEEDBACK);
void VOLTAGE_ALPHA_TEST (void);
void VOLTAGE_ALPHA_UP (void);
void VOLTAGE_ALPHA_DOWN (void);
void CURRENT_ALPHA_TEST (void);
void CURRENT_ALPHA_UP (void);
void CURRENT_ALPHA_DOWN (void);




// Necessary for printf
static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);

#endif /* MAIN_H_ */