#include "lcd.h"
#include "softSPI.h"
#include "Delay.h"
// 管理LCD重要参数
// 默认为竖屏
_lcd_dev lcddev;

// 画笔颜色,背景颜色
u16 POINT_COLOR = 0xFFFF, BACK_COLOR = 0x0000;
u16 DeviceCode;

void LCD_WR_REG(unsigned char dat)
{
    LCD_CS_CLR;
    LCD_RS_CLR;
    SPIv_WriteData(dat);
    LCD_CS_SET;
}

void LCD_WR_DATA(u8 dat)
{
    LCD_CS_CLR;
    LCD_RS_SET;
    SPIv_WriteData(dat);
    LCD_CS_SET;
}

void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
    LCD_WR_REG(LCD_Reg);
    LCD_WR_DATA(LCD_RegValue);
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
    LCD_WR_REG(lcddev.wramcmd);
}

/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(u16 Data)
 * @date       :2018-08-09
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
 ******************************************************************************/
void Lcd_WriteData_16Bit(u16 Data)
{
    LCD_CS_CLR;
    LCD_RS_SET;

    SPIv_WriteData(Data >> 8);
    SPIv_WriteData(Data);
    LCD_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/
void LCD_DrawPoint(u16 x, u16 y)
{
    LCD_SetCursor(x, y); // 设置光标位置
    Lcd_WriteData_16Bit(POINT_COLOR);
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
 ******************************************************************************/
void LCD_Clear(u16 Color)
{
    unsigned int i, m;
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
    LCD_CS_CLR;
    LCD_RS_SET;
    for (i = 0; i < lcddev.height; i++) {
        for (m = 0; m < lcddev.width; m++) {
            SPIv_WriteData(Color >> 8);
            SPIv_WriteData(Color);
        }
    }
    LCD_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void LCD_RESET(void)
{
    LCD_RST_CLR;
    Delay(20);
    LCD_RST_SET;
    Delay(20);
}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void LCD_Init(void)
{
    LCD_RESET(); // LCD 复位
    //************* ST7735初始化**********//
    Delay(120); // ms
    LCD_WR_REG(0x11);
    Delay(120); // ms
    LCD_WR_REG(0x21);
    LCD_WR_REG(0xB1);
    LCD_WR_DATA(0x05);
    LCD_WR_DATA(0x3A);
    LCD_WR_DATA(0x3A);

    LCD_WR_REG(0xB2);
    LCD_WR_DATA(0x05);
    LCD_WR_DATA(0x3A);
    LCD_WR_DATA(0x3A);

    LCD_WR_REG(0xB3);
    LCD_WR_DATA(0x05);
    LCD_WR_DATA(0x3A);
    LCD_WR_DATA(0x3A);
    LCD_WR_DATA(0x05);
    LCD_WR_DATA(0x3A);
    LCD_WR_DATA(0x3A);

    LCD_WR_REG(0xB4); // Dot inversion
    LCD_WR_DATA(0x03);

    LCD_WR_REG(0xC0);
    LCD_WR_DATA(0x62);
    LCD_WR_DATA(0x02);
    LCD_WR_DATA(0x04);

    LCD_WR_REG(0xC1);
    LCD_WR_DATA(0xC0);

    LCD_WR_REG(0xC2);
    LCD_WR_DATA(0x0D);
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0xC3);
    LCD_WR_DATA(0x8D);
    LCD_WR_DATA(0x6A);

    LCD_WR_REG(0xC4);
    LCD_WR_DATA(0x8D);
    LCD_WR_DATA(0xEE);

    LCD_WR_REG(0xC5); // VCOM
    LCD_WR_DATA(0x0E);

    LCD_WR_REG(0xE0);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x02);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x07);
    LCD_WR_DATA(0x02);
    LCD_WR_DATA(0x07);
    LCD_WR_DATA(0x0A);
    LCD_WR_DATA(0x12);
    LCD_WR_DATA(0x27);
    LCD_WR_DATA(0x37);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x0D);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x10);

    LCD_WR_REG(0xE1);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x06);
    LCD_WR_DATA(0x02);
    LCD_WR_DATA(0x08);
    LCD_WR_DATA(0x0A);
    LCD_WR_DATA(0x13);
    LCD_WR_DATA(0x26);
    LCD_WR_DATA(0x36);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x0D);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x10);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA(0x05);

    LCD_WR_REG(0x36);
    LCD_WR_DATA(0xC8);

    LCD_WR_REG(0x29);
    LCD_direction(USE_HORIZONTAL);
    BLK = 0;
    LCD_Clear(BLACK);
    BLK = 1;
}

/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
                                yStar:the bebinning y coordinate of the LCD display window
                                xEnd:the endning x coordinate of the LCD display window
                                yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/
void LCD_SetWindows(u16 xStar, u16 yStar, u16 xEnd, u16 yEnd)
{
    LCD_WR_REG(lcddev.setxcmd);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(xStar + lcddev.xoffset);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(xEnd + lcddev.xoffset);

    LCD_WR_REG(lcddev.setycmd);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(yStar + lcddev.yoffset);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(yEnd + lcddev.yoffset);

    LCD_WriteRAM_Prepare();
}

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
                                Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
    LCD_SetWindows(Xpos, Ypos, Xpos, Ypos);
}

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
                                                    2-180 degree
                                                    3-270 degree
 * @retvalue   :None
******************************************************************************/
void LCD_direction(u8 direction)
{
    lcddev.setxcmd = 0x2A;
    lcddev.setycmd = 0x2B;
    lcddev.wramcmd = 0x2C;
    lcddev.dir     = direction % 4;
    switch (lcddev.dir) {
        case 0:
            lcddev.width   = LCD_W;
            lcddev.height  = LCD_H;
            lcddev.xoffset = 26;
            lcddev.yoffset = 1;
            LCD_WriteReg(0x36, (1 << 3) | (1 << 6) | (1 << 7)); // BGR==1,MY==0,MX==0,MV==0
            break;
        case 1:
            lcddev.width   = LCD_H;
            lcddev.height  = LCD_W;
            lcddev.xoffset = 1;
            lcddev.yoffset = 26;
            LCD_WriteReg(0x36, (1 << 3) | (1 << 7) | (1 << 5)); // BGR==1,MY==1,MX==0,MV==1
            break;
        case 2:
            lcddev.width   = LCD_W;
            lcddev.height  = LCD_H;
            lcddev.xoffset = 26;
            lcddev.yoffset = 1;
            LCD_WriteReg(0x36, (1 << 3) | (0 << 6) | (0 << 7)); // BGR==1,MY==0,MX==0,MV==0
            break;
        case 3:
            lcddev.width   = LCD_H;
            lcddev.height  = LCD_W;
            lcddev.xoffset = 1;
            lcddev.yoffset = 26;
            LCD_WriteReg(0x36, (1 << 3) | (1 << 6) | (1 << 5)); // BGR==1,MY==1,MX==0,MV==1
            break;
        default:
            break;
    }
}