#include "REGX52.H"
#include "Timer0.h"
#include "Delay.h"
#include "key.h"
#include "Buzzer.h"
#include "lcd.h"
#include "gui.h"
#include <STRING.H>
#define DEBUG        1
#define KEY_BUZ_TIME 50
#define LED          P2_0
#define LED1         P2_1
#define Buzzer       P2_5
static unsigned char key_value = 0;
static unsigned char Sec = 42, Min = 29, Hour = 7;
static unsigned char show_flag = 0;
static unsigned char alarm_sec = 0, alarm_min = 30, alarm_hour = 7;
static unsigned char led0_flag  = 0;
static unsigned char led1_flag  = 0;
static unsigned char set_y      = 0;
static unsigned char set_x      = 0;
static unsigned char set_state  = 0;
static unsigned char key_v      = 0;
static unsigned alarm_flag      = 0;
static unsigned char alarm_show = 0;
/*----------------------------------*/
static void Nixie(u8 x)
{
    switch (x) {
        case 7:
            P2_2 = 0;
            P2_3 = 0;
            P2_4 = 0;
            break;
        case 6:
            P2_2 = 1;
            P2_3 = 0;
            P2_4 = 0;
            break;
        case 5:
            P2_2 = 0;
            P2_3 = 1;
            P2_4 = 0;
            break;
        case 4:
            P2_2 = 1;
            P2_3 = 1;
            P2_4 = 0;
            break;
        case 3:
            P2_2 = 0;
            P2_3 = 0;
            P2_4 = 1;
            break;
        case 2:
            P2_2 = 1;
            P2_3 = 0;
            P2_4 = 1;
            break;
        case 1:
            P2_2 = 0;
            P2_3 = 1;
            P2_4 = 1;
            break;
        case 0:
            P2_2 = 1;
            P2_3 = 1;
            P2_4 = 1;

            break;

        default:
            break;
    }
}
static void buzzer_alert()
{
#if DEBUG

    LED1 = 0;
    Buzzer_Time(KEY_BUZ_TIME);
    LED1 = 1;
#else
    LED1 = 0;
    Delay(50);
    LED1 = 1;
#endif
}
static void alarm_alert()
{
    LED1 = 0;
    Buzzer_Time(100);
    LED1 = 1;
}

static void show_student_info()
{
    int i = 0;
    LCD_DrawRectangle(1, 1, 159, 79, WHITE);
    Show_Str(10, 3, BLUE, BLACK, "学号：", 16, 0);
    LCD_ShowString(60, 3, 16, BLUE, "2022117000", 0);
    Show_Str(10, 20, BLUE, BLACK, "专业：电子信息工程", 16, 0);
    Show_Str(10, 40, BLUE, BLACK, "姓名：电子", 16, 0);
    Show_Str(10, 60, GREEN, BLACK, "按任意键开始", 16, 0);

    while (1) {
        key_value = keyget();
        if (key_value != 0) {
            buzzer_alert();
            break;
        }
    }
    for (i = 10; i < 150; i += 4) {
        LCD_DrawFillRectangle(i, 60, i + 5, 78, GREEN);
        Delay(2);
    }
    // BLK = 0;
    LCD_Clear(BLACK);
    // BLK = 1;
}

static void index_page()
{
    static unsigned char nixie_x         = 0;
    static unsigned char alarm_show_flag = 0;
    LCD_DrawRectangle(0, 0, 159, 79, BLUE);
    LCD_ShowString(10, 30, 16, WHITE, "Time :", 0);
    LCD_ShowString(10, 50, 16, WHITE, "Alarm:", 0);
    LCD_ShowChar(76, 30, WHITE, BLACK, ':', 16, 0);
    LCD_ShowChar(100, 30, WHITE, BLACK, ':', 16, 0);
    LCD_ShowChar(76, 50, WHITE, BLACK, ':', 16, 0);
    LCD_ShowChar(100, 50, WHITE, BLACK, ':', 16, 0);
    LCD_ShowNum(60, 30, Hour, WHITE, 2, 16);
    LCD_ShowNum(84, 30, Min, WHITE, 2, 16);
    LCD_ShowNum(108, 30, Sec, WHITE, 2, 16);
    LCD_ShowNum(60, 50, alarm_hour, WHITE, 2, 16);
    LCD_ShowNum(84, 50, alarm_min, WHITE, 2, 16);
    LCD_ShowNum(108, 50, 0, WHITE, 2, 16);
    while (1) {
        key_value = keyget();
        if (key_value != 0) {
            LCD_ShowChar(10, 10, YELLOW, BLACK, key_value, 16, 0);
            buzzer_alert();
            if (key_value == 'C') {
                set_state = 1 - set_state;
            }
            if (set_state == 0) {
                LCD_ShowChar(140, 50, GREEN, BLACK, ' ', 16, 0);
                LCD_ShowChar(140, 30, GREEN, BLACK, ' ', 16, 0);
                LCD_ShowChar(88, 10, GREEN, BLACK, ' ', 16, 0);
                LCD_ShowChar(65, 10, GREEN, BLACK, ' ', 16, 0);
            } else {
                if (key_value == 'A') {
                    set_y++;
                    set_y = set_y % 2;
                } else if (key_value == 'B') {
                    set_x++;
                    set_x = set_x % 2;
                }
                if (set_y == 0) {
                    LCD_ShowChar(140, 50, GREEN, BLACK, ' ', 16, 0);
                    LCD_ShowChar(140, 30, GREEN, BLACK, '<', 16, 0);
                }

                else if (set_y == 1) {
                    LCD_ShowChar(140, 30, GREEN, BLACK, ' ', 16, 0);
                    LCD_ShowChar(140, 50, GREEN, BLACK, '<', 16, 0);
                }

                if (set_x == 0) {
                    LCD_ShowChar(88, 10, GREEN, BLACK, ' ', 16, 0);
                    LCD_ShowChar(65, 10, GREEN, BLACK, 'V', 16, 0);
                } else if (set_x == 1) {
                    LCD_ShowChar(65, 10, GREEN, BLACK, ' ', 16, 0);
                    LCD_ShowChar(88, 10, GREEN, BLACK, 'V', 16, 0);
                }
                if (key_value == 'Q') {
                    if (set_y == 0) {
                        if (set_x == 0) {
                            Hour++;
                            if (Hour >= 24) Hour = 0;
                        } else if (set_x == 1) {
                            Min++;
                            if (Min >= 60) Min = 0;
                        }
                    } else if (set_y == 1) {
                        alarm_show = 1;
                        if (set_x == 0) {
                            alarm_hour++;
                            if (alarm_hour >= 24) alarm_hour = 0;
                        } else if (set_x == 1) {
                            alarm_min++;
                            if (alarm_min >= 60) alarm_min = 0;
                        }
                    }
                } else if (key_value == 'W') {
                    if (set_y == 0) {
                        if (set_x == 0) {
                            if (Hour == 0)
                                Hour = 23;
                            else
                                Hour--;
                        } else if (set_x == 1) {
                            if (Min == 0)
                                Min = 59;
                            else
                                Min--;
                        }
                    } else if (set_y == 1) {
                        alarm_show = 1;
                        if (set_x == 0) {
                            if (alarm_hour == 0)
                                alarm_hour = 23;
                            else
                                alarm_hour--;
                        } else if (set_x == 1) {
                            if (alarm_min == 0)
                                alarm_min = 59;
                            else
                                alarm_min--;
                        }
                    }
                }
            }
        }
        if (show_flag) {
            show_flag = 0;
            if (alarm_hour == Hour && alarm_min == Min && Sec == 0) {
                alarm_flag = 1;
            }
            nixie_x++;
            nixie_x = nixie_x % 8;
            Nixie(nixie_x);
            LCD_ShowNum(60, 30, Hour, WHITE, 2, 16);
            LCD_ShowNum(84, 30, Min, WHITE, 2, 16);
            LCD_ShowNum(108, 30, Sec, WHITE, 2, 16);
        }
        if (alarm_show) {
            alarm_show = 0;
            LCD_ShowNum(60, 50, alarm_hour, WHITE, 2, 16);
            LCD_ShowNum(84, 50, alarm_min, WHITE, 2, 16);
            LCD_ShowNum(108, 50, 0, WHITE, 2, 16);
        }
        if (alarm_flag) {
            if (Sec > 30)
                alarm_flag = 0;
            alarm_alert();
            
            if(!alarm_show_flag)
            {
                LCD_ShowString(94, 10, 16, RED, "ALARM!!!", 0);
                alarm_show_flag = 1;
            }
            
            if (key_value != 0) {
                alarm_flag = 0;
                alarm_show_flag = 0;
                LCD_ShowString(94, 10, 16, RED, "        ", 0);
            }
        }
    }
}

void main()
{
    LCD_Init();
    Timer0_Init();
    show_student_info();
    index_page();
    while (1) {
        key_value = keyget(); // 获取按键值
    }
}

void Timer0_Routine() interrupt 1
{
    static unsigned int T0Count;
    TL0 = 0x66;
    TH0 = 0xFC;
    T0Count++;
    if (T0Count >= 1000) {
        T0Count   = 0;
        led0_flag = 1 - led0_flag;
        LED       = led0_flag;
        Sec++;
        show_flag = 1;
        if (Sec >= 60) {
            Sec = 0;
            Min++;
            if (Min >= 60) {
                Min = 0;
                Hour++;
                if (Hour >= 24) {
                    Hour = 0;
                }
            }
        }
    }
}
