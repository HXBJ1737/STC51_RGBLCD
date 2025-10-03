#include <REGX52.H>


// void Timer0Init(void)
// {
// 	TMOD &= 0xF0;			
// 	TMOD |= 0x01;			
// 	TL0 = 0xFF;				
// 	TH0 = 0xFF;				
// 	TF0 = 0;				
// 	TR0 = 1;			
// 	ET0=1;
// 	EA=1;
// 	PT0=0;
// }
void Timer0_Init()
{
    TMOD &= 0xF0;			
	TMOD |= 0x01;			
	TL0 = 0x66;				
	TH0 = 0xFC;			
	TF0 = 0;			
	TR0 = 1;				
	ET0=1;
	EA=1;
	PT0=0;
}

void Timer1_Init()
{
    TMOD |= 0x10;   // 定时器1工作方式1
    TH1 = 0xFC;     // 1ms定时
    TL1 = 0x66;
    ET1 = 1;        // 开启定时器1中断
    TR1 = 1;        // 启动定时器1
}
