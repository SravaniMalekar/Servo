/*
 * servotry.c
 *
 * Created: 19-06-2020 11:41:03
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

uint16_t Receiveangle(void);
static inline void initTimer(void){//sends a pulse every 20ms
	TCCR1A |=(1 << WGM11);//bit for enabling FastPWM
	TCCR1B |=(1 << WGM12)|(1 << WGM13);//bits for enabling Fast PWM
	TCCR1B |=(1 << CS11);//Prescaler as 8
	ICR1 = 40000;//top value
	TCCR1A |= (1 << COM1A1);//non-inverting mode
	DDRB = 0Xff;//setting PORTB as output
}

static inline void demo(void){
	serialString("MIN\r\n");
	OCR1A =PULSE_MIN;
	_delay_ms(1500);
	serialString("MAX\r\n");
	OCR1A =PULSE_MAX;
	_delay_ms(1500);
	serialString("MID\r\n");
	OCR1A = PULSE_MID;
	_delay_ms(1500);
}

int main(void)
{
	uint16_t Pulselength;
	USART_Init();//initializing uart
	serialString("hello\r\n");
	initTimer();//initializing timer1
	demo();

    while (1) 
    {
		serialString("enter number betweeen 1000 to 5000:\r\n");//taking user input
		Pulselength = Receiveangle();
		
		serialString("wait...");
		OCR1A = Pulselength;
		
		_delay_ms(1000);
		
	
		
    }
}
uint16_t Receiveangle(void){
	char thousands ='0';
	char hundreds ='0';
	char tens ='0';
	char ones ='0';
	char charac ='0';
	
	do{
		thousands=hundreds;
		hundreds=tens;
		tens=ones;
		ones=charac;
		charac =ReceiveByte();
		
	}while(charac != '\r');
	
	return(1000*(thousands -'0')+100*(hundreds -'0')+10*(tens- '0')+ ones - '0');
}
