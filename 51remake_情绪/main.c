#include <car.h>

extern unsigned char Left_Speed_Ratio;
extern unsigned char Right_Speed_Ratio;
unsigned int time=0; 
extern unsigned char pwm_val_left;
extern unsigned char pwm_val_right;

void delay1s(void)   
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  
}

void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。

	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器			
}



void timer0()interrupt 1 using 2 
{ 
TH0=0XFC;	//给定时器赋初值，定时1ms
TL0=0X18;
time++; 
pwm_val_left++; 
pwm_val_right++; 
pwm_out_left_moto(); 
pwm_out_right_moto(); 
} 

void main()
	{
	Timer0Init();  
	Left_Speed_Ratio=0.5;   //设置左电机车速为最大车速的50%
	Right_Speed_Ratio=0.5;	 //设置右电机车速为最大车速的50%
	while(1)
		{
		obsessive();
		}
	}