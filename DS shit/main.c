#include <stdlib.h>
#include <util/delay.h>
#include "ds18b20.h"
#include "std_macros.h"
const int servoPin = 5; // D5

unsigned char difftemp(double old,double new)
{
	int x;

	x = (new > old) ? (new - old) : (old - new);
		
	if(x>=0 && x<=4)
		return '0';
	else if (x>=5 && x<=9)
		return '1';
	else if (x>=10)
		return '2';
		
	
}
int main(void)
{
	double newtemp = 0, oldtemp = 0;
	CLR_BIT(DDRB,0);//input for ir
	SET_BIT(DDRD,0);//LED 1
	SET_BIT(DDRD,1);//LED 2
	SET_BIT(DDRD,2);//LED 3	
	SET_BIT(DDRD,3);//LED 4

	oldtemp=ds18b20_gettemp();
	_delay_ms(1000);//wait for the new reading to come in
	while(1) 
	{		
		//DS18B20------------------------------------------------------------------------------------------
		newtemp = ds18b20_gettemp();
		int diffrant=difftemp(oldtemp,newtemp);
		switch(diffrant)
		{
			case '0':
			SET_BIT(PORTD,0);
			CLR_BIT(PORTD,1);
			break;
			case '1':
			SET_BIT(PORTD,1);
			CLR_BIT(PORTD,0);
			break;
			case '2':
			SET_BIT(PORTD,2);
			CLR_BIT(PORTD,1);
			CLR_BIT(PORTD,0);
			timer1_wave_fastPWM(1);
			break;
		}	
		oldtemp=newtemp;
		_delay_ms(200);
		//IR----------------------------------------------------------------------------------------------
		unsigned char IR_READs = READ_BIT(PINB,0);
		if (IR_READs==1)
		{
			_delay_ms(200);
			IR_READs=READ_BIT(PINB,0);
			
			if (IR_READs==1)
			{
				_delay_ms(200);
				IR_READs=READ_BIT(PINB,0);
				SET_BIT(PORTD,3);
				
				if (IR_READs==1)
				{
					timer1_wave_fastPWM(1);
					SET_BIT(PORTD,2);					
				}
			}
		}
		else 
		{
			CLR_BIT(PORTD,3);
		}
		
		//MQ5------------------------------------------------------------------------------------------------
		
		//MQ135----------------------------------------------------------------------------------------------
		
	}//while-end
		
	return 0;
}