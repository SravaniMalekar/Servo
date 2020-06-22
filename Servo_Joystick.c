/*
 * Servo_Joystick.c
 *
 * Created: 22-06-2020 18:28:40
 * Author : Sravani Malekar
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PULSE_MIN 1000 //min angle for servo
#define PULSE_MAX 5000 //max angle for servo
#define PULSE_MID 3000 //90 degree angle for servo

#define XPIN (1 << MUX0)//ADC1 channel
#define YPIN (1 << MUX1)//ADC2 channel

void ADC_Init0(void);//func for initialization of ADC0
uint16_t readADC(uint8_t channel);//func to enable use of multiple ADC

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
    initTimer();//initializing timer1 for Servo
	ADC_Init0();//initializing ADC0
	uint16_t Xval;
	uint16_t Yval;
	uint16_t WVx;

    while (1) 
    {
		Xval = readADC(XPIN);//reading X value from Joystick
		Yval = readADC(YPIN);
		WVx = ((4000./1023.)*Xval) +1000;//converting input to value corresponding to angle
		OCR1A = WVx;
		_delay_ms(500);

		
    }
}

void ADC_Init0(void){
	ADMUX |= (1 << REFS0);// ref.voltage selection
	ADCSRA |= (1 << ADEN);// ADC enable bit
	ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);// setting prescaler as 128

}
uint16_t readADC(uint8_t channel){
	
	ADMUX = (11110000 & ADMUX)|(channel);
	ADCSRA |= (1 << ADSC);// starting conversation
	while(ADCSRA & (1 << ADSC));
	return(ADC);
}
