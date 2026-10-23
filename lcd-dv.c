#include<lpc21xx.h>
#include"header.h"
void lcd_data(unsigned char data)
{
unsigned int t;
IOCLR1=0xFE<<16;
t=(data&0xF0)<<16;
IOSET1=t;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

IOCLR1=0xFE<<16;
IOSET1=(data&0x0F)<<20;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}
void lcd_cmd(unsigned int cmd)
{
 unsigned int t;
 IOCLR1=0xFE<<16;
 t=(cmd&0xF0)<<16;
 IOSET1=t;
 IOCLR1=1<<17;
 IOCLR1=1<<18;
 IOSET1=1<<19;
 delay_ms(2);
 IOCLR1=1<<19;

 IOCLR1=0xFE<<16;
 IOSET1=(cmd&0x0F)<<20;
 IOCLR1=1<<17;
 IOCLR1=1<<18;
 IOSET1=1<<19;
 IOCLR1=1<<19;
}
void lcd_init()
{
IODIR1 = 0xFE << 16;
IOCLR1 = 1 << 19; 
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x0E); 
lcd_cmd(0x01); 
}
void lcd_str(char *p)
{
while(*p!=0)
{
lcd_data(*p);
p++;
}
}
