/*
 * Practicumm_Two.c
 *
 * Created: 5/8/2026 3:10:20 PM
 * Author : Rivombo
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD = 0xFF; //set as output
	DDRB |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3); // set as output
	DDRC |= (1 << 0) | (1 << 1) | (1 << 2); // set as output
	
	int unitsPortD[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x18};
	int portBTens[10] = {0x00,0x09,0x04,0x00,0x09,0x02,0x02,0x08,0x00,0x08};
	int portCTens[10] = {0x04,0x07,0x02,0x03,0x01,0x01,0x00,0x07,0x00,0x01};
		
	unsigned int hold, tens, units;
	unsigned long holdVal;
		
	ADMUX |= (1 << REFS1) | (1 << MUX2);
	ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // enable prescalers 
    while (1) 
    {
		ADCSRA |= (1 << ADSC); //start conversion
		while(ADCSRA & (1 << ADSC));
		
		hold = ADC;
		holdVal = (unsigned long)hold * 150;
		holdVal = holdVal/306;
		
		tens = holdVal/10;
		units = holdVal % 10;
		
		if(holdVal >= 0 && holdVal <= 99)
		{
			PORTD =unitsPortD[units];
			PORTB = portBTens[tens];
			PORTC = portCTens[tens];
			
		}
		
		
    }
}