#include "C12864.h"
#include <reg52.h>
#include <intrins.h>
#include "Delay.h"
#define uchar unsigned char
#define uint  unsigned int
//unsigned char str[] = "数\xfd三\xfd";//显示乱码，加\xfd
#define LCD_data  P0             //数据口
sbit LCD_RS  =  P3^5;            //寄存器选择输入 
sbit LCD_RW  =  P3^6;            //液晶读/写控制
sbit LCD_EN  =  P3^4;            //液晶使能控制
sbit LCD_PSB =  P3^7;            //串/并方式控制

void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}
bit lcd_busy()
{ 
    bit result;
    P0=0X00;              //关掉数码管的信号。阻止数码管受到P0口信号的影响
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    Delay(1);
    result = (bit)(P0&0x80);
    LCD_EN = 0;
    return(result); 
 }
void lcd_wcmd(uchar cmd)
{   
                         
    while(lcd_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    _nop_();
    _nop_(); 
    P0 = cmd;
	Delay(1);
    LCD_EN = 1;
	Delay(1);
    LCD_EN = 0;  
}
/*******************************************************************/
/*                                                                 */
/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
/*                                                                 */
/*******************************************************************/
void lcd_wdat(uchar dat)
{                          
    while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    Delay(1);
    LCD_EN = 1;
    Delay(1);
    LCD_EN = 0; 
}
/*******************************************************************/
/*                                                                 */
/*  LCD初始化设定                                                  */
/*                                                                 */
/*******************************************************************/
void lcd12864_init()
{ 

    LCD_PSB = 1;         //并口方式   
    lcd_wcmd(0x34);      //扩充指令操作
    Delay(5);
    lcd_wcmd(0x30);      //基本指令操作
    Delay(5);
    lcd_wcmd(0x0C);      //显示开，关光标
    Delay(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    Delay(5);
}
