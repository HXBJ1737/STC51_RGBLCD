#ifndef __LCD_H
#define __LCD_H
#include "REGX52.h"
#define u16 unsigned short
#define u8  unsigned char
#define u32 unsigned int
// LCD重要参数集
typedef struct
{
    u16 width;   // LCD 宽度
    u16 height;  // LCD 高度
    u16 id;      // LCD ID
    u8 dir;      // 横屏还是竖屏控制：0，竖屏；1，横屏。
    u16 wramcmd; // 开始写gram指令
    u16 setxcmd; // 设置x坐标指令
    u16 setycmd; // 设置y坐标指令
    u8 xoffset;
    u8 yoffset;
} _lcd_dev;

// LCD参数
extern _lcd_dev lcddev; // 管理LCD重要参数

#define USE_HORIZONTAL 1 // 定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转


// 定义LCD的尺寸
#define LCD_W 80
#define LCD_H 160

// TFTLCD部分外要调用的函数
extern u16 POINT_COLOR; // 默认红色
extern u16 BACK_COLOR;  // 背景颜色.默认为白色

//-----------------LCD端口定义----------------
#define BLK       P0_2     // 背光控制引脚        PB9
#define LCD_CS    P0_3    // 片选引脚            PB11
#define LCD_RS    P0_4    // 寄存器/数据选择引脚 PB10
#define LCD_RST   P0_5    // 复位引脚            PB12


#define LCD_CS_SET LCD_CS=1
#define LCD_RS_SET  LCD_RS=1
#define LCD_RST_SET LCD_RST=1

#define LCD_CS_CLR  LCD_CS=0
#define LCD_RS_CLR  LCD_RS=0
#define LCD_RST_CLR LCD_RST=0

// 画笔颜色
#define WHITE   0xFFFF
#define BLACK   0x0000
#define BLUE    0x001F
#define BRED    0XF81F
#define GRED    0XFFE0
#define GBLUE   0X07FF
#define RED     0xF800
#define MAGENTA 0xF81F
#define GREEN   0x07E0
#define CYAN    0x7FFF
#define YELLOW  0xFFE0
#define BROWN   0XBC40 // 棕色
#define BRRED   0XFC07 // 棕红色
#define GRAY    0X8430 // 灰色
#define GRAY0   0xEF7D
#define GRAY1   0x8410 // 灰色1      00000 000000 00000
#define GRAY2   0x4208
// GUI颜色

#define DARKBLUE  0X01CF // 深蓝色
#define LIGHTBLUE 0X7D7C // 浅蓝色
#define GRAYBLUE  0X5458 // 灰蓝色
// 以上三色为PANEL的颜色

#define LIGHTGREEN 0X841F // 浅绿色
#define LIGHTGRAY  0XEF5B // 浅灰色(PANNEL)
#define LGRAY      0XC618 // 浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE  0XA651 // 浅灰蓝色(中间层颜色)
#define LBBLUE     0X2B12 // 浅棕蓝色(选择条目的反色)

void LCD_Init(void);
void LCD_Clear(u16 Color);
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x, u16 y); // 画点
void LCD_SetWindows(u16 xStar, u16 yStar, u16 xEnd, u16 yEnd);

void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
void LCD_WR_DATA(unsigned char dat);
void LCD_WriteRAM_Prepare(void);
void Lcd_WriteData_16Bit(u16 Data);
void LCD_direction(u8 direction);


#endif
