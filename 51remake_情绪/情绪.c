#include <reg52.h>//51头文件
unsigned char pwm_val_left,pwm_val_right; //中间变量，用户请勿修改。
unsigned char pwm_left,pwm_right; //定义PWM输出高电平的时间的变量。用户操作PWM的变量。
#define PWM_DUTY 100 //定义PWM的周期，数值为定时器0溢出周期，假如定时器溢出时间为100us，则PWM周期为10ms。
#define PWM_HIGH_MIN 35 //限制PWM输出的最小占空比。用户请勿修改。
#define PWM_HIGH_MAX PWM_DUTY //限制PWM输出的最大占空比。用户请勿修改。

/*电机驱动IO定义*/
sbit leftMotorPwm = P1^5; //为1 左电机使能
sbit IN1 = P1^4; //为1 左电机正转
sbit IN2 = P1^3; //为1 左电机反转
sbit IN3 = P1^2; //为1 右电机反转
sbit IN4 = P1^1; //为1 右电机正转
sbit rightMotorPwm = P1^0; //为1 右电机使能

void Timer0_Init(void); //定时器0初始化
void LoadPWM(void);//装入PWM输出值
void forward(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11智能小车前进
void left_run(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11智能小车左转
void right_run(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11智能小车右转
void stop(void);//QX_A11智能小车停车

/*主函数*/
void main(void)
{
Timer0_Init();//定时0初始化
while(1)
{
forward(70,70);//前进
}
}

void forward(unsigned char LeftSpeed,unsigned char RightSpeed)
{
    pwm_left = LeftSpeed,pwm_right = RightSpeed;//设置速度
    IN1 = 1;
    IN2 = 0;
    IN3 = 0;
    IN4 = 1;
}
void left_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right = RightSpeed;//设置速度
	IN1 = 1;
	IN2 = 0;
	IN3 = 1;
	IN4 = 0;
}
void right_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right = RightSpeed;//设置速度
	IN1 = 0;
	IN2 = 1;
	IN3 = 0;
	IN4 = 1;
}
void stop(void)
{
	IN1 = 0;
	IN2 = 1;
	IN3 = 1;
	IN4 = 0;
}
/********************* Timer0初始化************************/
void Timer0_Init(void)
{
TMOD |= 0x02;//定时器0，8位自动重装模块
TH0 = 164;
TL0 = 164;//11.0592M晶振，12T溢出时间约等于100微秒
TR0 = 1;//启动定时器0
ET0 = 1;//允许定时器0中断
EA = 1;//总中断允许
}
/********************* Timer0中断函数************************/
void timer0_int (void) interrupt 1
{
    pwm_val_left++;
    pwm_val_right++;
    if(pwm_left > PWM_HIGH_MAX) pwm_left = PWM_HIGH_MAX; //如果左输出写入大于最大占空比数据，则强制为最大占空比。
    if(pwm_left < PWM_HIGH_MIN) pwm_left = PWM_HIGH_MIN; //如果左输出写入小于最小占空比数据，则强制为最小占空比。
    if(pwm_right > PWM_HIGH_MAX) pwm_right = PWM_HIGH_MAX; //如果右输出写入大于最大占空比数据，则强制为最大占空比。
    if(pwm_right < PWM_HIGH_MIN) pwm_right = PWM_HIGH_MIN; //如果右输出写入小于最小占空比数据，则强制为最小占空比。
    if(pwm_val_left<=pwm_left) leftMotorPwm = 1; //装载左PWM输出高电平时间
    else leftMotorPwm = 0; //装载左PWM输出低电平时间
    if(pwm_val_left>=PWM_DUTY) pwm_val_left = 0; //如果左对比值大于等于最大占空比数据，则为零
    if(pwm_val_right<=pwm_right) rightMotorPwm = 1; //装载右PWM输出高电平时间
    else rightMotorPwm = 0; //装载右PWM输出低电平时间
    if(pwm_val_right>=PWM_DUTY) pwm_val_right = 0; //如果右对比值大于等于最大占空比数据，则为零
}