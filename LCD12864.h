#ifndef __C12864_H_
#define	__C12864_H_
#define uchar unsigned char
#define uint  unsigned int
/*TS12864A-3 端口定义*/
void Delay(unsigned int xms);
void lcd12864_init();
void lcd_wcmd(uchar cmd);
void lcd_wdat(uchar dat);
bit lcd_busy();
#endif

