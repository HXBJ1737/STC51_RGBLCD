
#ifndef __GUI_H__
#define __GUI_H__

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
void GUI_DrawPoint(u16 x, u16 y, u16 color);
void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void Draw_Triangel(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void Fill_Triangel(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_ShowChar(u16 x, u16 y, u16 fc, u16 bc, u8 num, u8 size, u8 mode);
void LCD_ShowNum(u16 x, u16 y, u32 num, u16 color, u8 len, u8 size);
void LCD_ShowString(u16 x, u16 y, u8 size, u16 color, u8 *p, u8 mode);
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s, u8 mode);
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode);
void gui_circle(int xc, int yc, u16 c, int r, int fill);
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode);
void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
#endif
