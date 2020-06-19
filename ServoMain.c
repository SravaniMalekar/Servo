/*
 * servo.c
 *
 * Created: 18-06-2020 23:35:12
 * Author : Sravani Malekar
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h" // serial communication header file

#define PULSE_MIN 1000 //min angle for servo
#define PULSE_MAX 5000 //max angle for servo
#define PULSE_MID 3000 //90 degree angle for servo

static inline void initTimer(void){//sends a pulse every 20ms
	TCCR1A |=(1 << WGM11);//bit for enabling FastPWM
	TCCR1B |=(1 << WGM12)|(1 << WGM13);//bits for enabling Fast PWM
	TCCR1B |=(1 << CS11);//Prescaler as 8
	ICR1 = 40000;//top value
	TCCR1A |= (1 << COM1A1);//non-inverting mode
	DDRB = 0Xff;//setting PORTB as output
}


int main(void)
{
	USART_Init();//initializing uart
	serialString("hello");
	initTimer();//initializing timer1
	

    while (1) 
    {
		serialString("MIN");
		OCR1A =PULSE_MIN;
		_delay_ms(1500);
		serialString("MAX");
		OCR1A =PULSE_MAX;
		_delay_ms(1500);
		serialString("MID");
		OCR1A = PULSE_MID;
		_delay_ms(1500);
		
    }
}

