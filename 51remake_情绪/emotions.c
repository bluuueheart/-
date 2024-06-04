#include <car.h>

void wary(void)
{ 
		run();		

		while(Light==1)
		{
			stop();
		}
} 

void indecisive(void)
{ 
		if(Light==1)
		{
			back();
		}
		else
		{
			run();
		}
} 

void paranoid(void)
{ 
		run();		

		if(Light==1)
		{
			rotate();
			delay1s(); delay1s(); delay1s(); delay1s(); delay1s(); 
			stop();
			run();
			delay1s();  
		}
} 

void insecure(void)
{
		if(Light==1)
		{
			rotate();
		}
		else
		{
			run();
		}
} 

void obsessive(void)
{
		if(Light==1)
		{
			back();
			while(back_Light==0)
			{
				back();
			}
		}
		run();
} 