#ifndef __car_H
#define __car_H

#include <reg52.h>
#include <intrins.h>

sbit Left_moto_pwm=P1^0 ;
sbit Right_moto_pwm=P1^1;
sbit p34=P3^0;
sbit p35=P1^5; 
sbit p36=P1^3;
sbit p37=P3^3;

sbit Light=P1^2;
sbit back_Light=P3^1;

void Left_moto_go() ;
void Left_moto_back() ;
void Left_moto_stp() ;
void Right_moto_go();
void Right_moto_back(); 
void Right_moto_stp(); 
void delay(unsigned int k) ;
void delay1s(void) ;
void pwm_out_left_moto(void) ;
void pwm_out_right_moto(void);
void run(void);
void back(void);
void left(void);
void right(void);
void stop(void);
void rotate(void);

void wary(void);
void indecisive(void);
void paranoid(void);
void insecure(void);
void obsessive(void);