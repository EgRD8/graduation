/*
 * servo_motor.c
 *
 * Created: 10/23/2019 1:46:05 PM
 *  Author: Mohamed Zaghlol
 */ 


#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include "std_macros.h"
#include "timer.h"
int main(void)
{
	while(1)
	{
		timer1_wave_fastPWM(1);
		_delay_ms(1000);
		
		timer1_wave_fastPWM(1.5);
		_delay_ms(1000);
		
		timer1_wave_fastPWM(2);
		_delay_ms(1000);
	}
}

