
#include "lcd.h"
#include "string.h"
#include "font.h"
#include "gui.h"

void GUI_DrawPoint(u16 x, u16 y, u16 color)
{
    LCD_SetCursor(x, y); // 设置光标位置
    Lcd_WriteData_16Bit(color);
}

void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color)
{
    u16 i, j;
    u16 width  = ex - sx + 1;       // 得到填充的宽度
    u16 height = ey - sy + 1;       // 高度
    LCD_SetWindows(sx, sy, ex, ey); // 设置显示窗口
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++)
            Lcd_WriteData_16Bit(color); // 写入数据
    }

    // LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1); // 恢复窗口设置为全屏
}

void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;

    delta_x = x2 - x1; // 计算坐标增量
    delta_y = y2 - y1;
    uRow    = x1;
    uCol    = y1;
    if (delta_x > 0)
        incx = 1; // 设置单步方向
    else if (delta_x == 0)
        incx = 0; // 垂直线
    else {
        incx    = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; // 水平线
    else {
        incy    = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x; // 选取基本增量坐标轴
    else
        distance = delta_y;
    for (t = 0; t <= distance + 1; t++) // 画线输出
    {
        GUI_DrawPoint(uRow, uCol, color); // 画点
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance) {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance) {
            yerr -= distance;
            uCol += incy;
        }
    }
}

void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    LCD_DrawLine(x1, y1, x2, y1, color);
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x1, y2, x2, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
}

void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    LCD_Fill(x1, y1, x2, y2, color);
}

void _draw_circle_8(int xc, int yc, int x, int y, u16 c)
{
    GUI_DrawPoint(xc + x, yc + y, c);

    GUI_DrawPoint(xc - x, yc + y, c);

    GUI_DrawPoint(xc + x, yc - y, c);

    GUI_DrawPoint(xc - x, yc - y, c);

    GUI_DrawPoint(xc + y, yc + x, c);

    GUI_DrawPoint(xc - y, yc + x, c);

    GUI_DrawPoint(xc + y, yc - x, c);

    GUI_DrawPoint(xc - y, yc - x, c);
}

void gui_circle(int xc, int yc, u16 c, int r, int fill)
{
    int x = 0, y = r, yi, d;

    d = 3 - 2 * r;

    if (fill) {
        // 如果填充（画实心圆）
        while (x <= y) {
            for (yi = x; yi <= y; yi++)
                _draw_circle_8(xc, yc, x, yi, c);

            if (d < 0) {
                d = d + 4 * x + 6;
            } else {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    } else {
        // 如果不填充（画空心圆）
        while (x <= y) {
            _draw_circle_8(xc, yc, x, y, c);
            if (d < 0) {
                d = d + 4 * x + 6;
            } else {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
}

void Draw_Triangel(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    LCD_DrawLine(x0, y0, x1, y1, color);
    LCD_DrawLine(x1, y1, x2, y2, color);
    LCD_DrawLine(x2, y2, x0, y0, color);
}

static void _swap(u16 *a, u16 *b)
{
    u16 tmp;
    tmp = *a;
    *a  = *b;
    *b  = tmp;
}

void Fill_Triangel(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2)
{
    u16 a, b, y, last;
    int dx01, dy01, dx02, dy02, dx12, dy12;
    long sa = 0;
    long sb = 0;
    if (y0 > y1) {
        _swap(&y0, &y1);
        _swap(&x0, &x1);
    }
    if (y1 > y2) {
        _swap(&y2, &y1);
        _swap(&x2, &x1);
    }
    if (y0 > y1) {
        _swap(&y0, &y1);
        _swap(&x0, &x1);
    }
    if (y0 == y2) {
        a = b = x0;
        if (x1 < a) {
            a = x1;
        } else if (x1 > b) {
            b = x1;
        }
        if (x2 < a) {
            a = x2;
        } else if (x2 > b) {
            b = x2;
        }
        LCD_Fill(a, y0, b, y0, POINT_COLOR);
        return;
    }
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;

    if (y1 == y2) {
        last = y1;
    } else {
        last = y1 - 1;
    }
    for (y = y0; y <= last; y++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        if (a > b) {
            _swap(&a, &b);
        }
        LCD_Fill(a, y, b, y, POINT_COLOR);
    }
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        if (a > b) {
            _swap(&a, &b);
        }
        LCD_Fill(a, y, b, y, POINT_COLOR);
    }
}

/*****************************************************************************
 * @name       :void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode)
 * @date       :2018-08-09
 * @function   :Display a single English character
 * @parameters :x:the bebinning x coordinate of the Character display position
                y:the bebinning y coordinate of the Character display position
                                fc:the color value of display character
                                bc:the background color of display character
                                num:the ascii code of display character(0~94)
                                size:the size of display character
                                mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
void LCD_ShowChar(u16 x, u16 y, u16 fc, u16 bc, u8 num, u8 size, u8 mode)
{
    u8 temp;
    u8 pos, t;
    u16 colortemp = POINT_COLOR;

    num = num - ' ';                                      // 得到偏移后的值
    LCD_SetWindows(x, y, x + size / 2 - 1, y + size - 1); // 设置单个文字显示窗口
    if (!mode)                                            // 非叠加方式
    {
        for (pos = 0; pos < size; pos++) {

            temp = asc2_1608[num][pos]; // 调用1608字体
            for (t = 0; t < size / 2; t++) {
                if (temp & 0x01)
                    Lcd_WriteData_16Bit(fc);
                else
                    Lcd_WriteData_16Bit(bc);
                temp >>= 1;
            }
        }
    } else // 叠加方式
    {
        for (pos = 0; pos < size; pos++) {
            temp = asc2_1608[num][pos]; // 调用1608字体
            for (t = 0; t < size / 2; t++) {
                POINT_COLOR = fc;
                if (temp & 0x01) LCD_DrawPoint(x + t, y + pos); // 画一个点
                temp >>= 1;
            }
        }
    }
    POINT_COLOR = colortemp;
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1); // 恢复窗口为全屏
}

/*****************************************************************************
 * @name       :void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode)
 * @date       :2018-08-09
 * @function   :Display English string
 * @parameters :x:the bebinning x coordinate of the English string
                y:the bebinning y coordinate of the English string
                                p:the start address of the English string
                                size:the size of display character
                                mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
void LCD_ShowString(u16 x, u16 y, u8 size, u16 color, u8 *p, u8 mode)
{
    while ((*p <= '~') && (*p >= ' ')) // 判断是不是非法字符!
    {
        if (x > (lcddev.width - 1) || y > (lcddev.height - 1))
            return;
        LCD_ShowChar(x, y, color, BACK_COLOR, *p, size, mode);
        x += size / 2;
        p++;
    }
}

/*****************************************************************************
 * @name       :u32 mypow(u8 m,u8 n)
 * @date       :2018-08-09
 * @function   :get the nth power of m (internal call)
 * @parameters :m:the multiplier
                n:the power
 * @retvalue   :the nth power of m
******************************************************************************/
u32 mypow(u8 m, u8 n)
{
    u32 result = 1;
    while (n--) result *= m;
    return result;
}

/*****************************************************************************
 * @name       :void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
 * @date       :2018-08-09
 * @function   :Display number
 * @parameters :x:the bebinning x coordinate of the number
                y:the bebinning y coordinate of the number
                                num:the number(0~4294967295)
                                len:the length of the display number
                                size:the size of display number
 * @retvalue   :None
******************************************************************************/
void LCD_ShowNum(u16 x, u16 y, u32 num, u16 color, u8 len, u8 size)
{
    u8 t, temp;
    u8 enshow = 0;
    for (t = 0; t < len; t++) {
        temp = (num / mypow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1)) {
            if (temp == 0) {
                LCD_ShowChar(x + (size / 2) * t, y, color, BACK_COLOR, '0', size, 0);
                continue;
            } else
                enshow = 1;
        }
        LCD_ShowChar(x + (size / 2) * t, y, color, BACK_COLOR, temp + '0', size, 0);
    }
}

/*****************************************************************************
 * @name       :void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
 * @date       :2018-08-09
 * @function   :Display a single 16x16 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
                y:the bebinning y coordinate of the Chinese character
                                fc:the color value of Chinese character
                                bc:the background color of Chinese character
                                s:the start address of the Chinese character
                                mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s, u8 mode)
{
    u8 i, j;
    u16 k;
    u16 HZnum;
    u16 x0 = x;
    HZnum  = sizeof(tfont16) / sizeof(typFNT_GB16); // 自动统计汉字数目

    for (k = 0; k < HZnum; k++) {
        if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)) && (tfont16[k].Index[2] == *(s + 2))) {
            LCD_SetWindows(x, y, x + 16 - 1, y + 16 - 1);
            for (i = 0; i < 16 * 2; i++) {
                for (j = 0; j < 8; j++) {
                    if (!mode) // 非叠加方式
                    {
                        if (tfont16[k].Msk[i] & (0x80 >> j))
                            Lcd_WriteData_16Bit(fc);
                        else
                            Lcd_WriteData_16Bit(bc);
                    } else {
                        POINT_COLOR = fc;
                        if (tfont16[k].Msk[i] & (0x80 >> j)) LCD_DrawPoint(x, y); // 画一个点
                        x++;
                        if ((x - x0) == 16) {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue; // 查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
    }

    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1); // 恢复窗口为全屏
}

void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode)
{
    u16 x0 = x;
    u8 bHz = 0;       // 字符或者中文
    while (*str != 0) // 数据未结束
    {

        GUI_DrawFont16(x, y, fc, bc, str, mode);
        str += 3;
        x += size; // 下一个汉字偏移
    }
}

/*****************************************************************************
 * @name       :void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
 * @date       :2018-08-09
 * @function   :Centered display of English and Chinese strings
 * @parameters :x:the bebinning x coordinate of the Chinese and English strings
                y:the bebinning y coordinate of the Chinese and English strings
                                fc:the color value of Chinese and English strings
                                bc:the background color of Chinese and English strings
                                str:the start address of the Chinese and English strings
                                size:the size of Chinese and English strings
                                mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode)
{
    int len = strlen((const char *)str) / 3;
    // u16 x1  = (lcddev.width - len* 6) /2;
    u16 x1 = x - len * size / 2;
    Show_Str(x1, y, fc, bc, str, size, mode);
}
