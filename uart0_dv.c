#include<lpc21xx.h>
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)
void uart0_init(unsigned int baud)
{
int result=0,pclk;
if(VPBDIV==0)
pclk=15000000;
else if (VPBDIV==1)
pclk=60000000;
else if (VPBDIV==2)
pclk=30000000;

result=pclk/(16*baud);
PINSEL0 |=0x00000005;
U0LCR=0x83;
U0DLL=result&0xff;
U0DLM=(result>>8)&0xff;
U0LCR=0x03;
}
void uart0_tx(unsigned int data)
{
while(THRE==0);
U0THR=data;
}
unsigned int uart0_rx()
{
while(RDR==0);
return U0RBR;
}
void uart0_tx_str(char *p)
{
unsigned int i;
	while(1)
	{
   	p[i]=uart0_rx();
		if(p[i]=='\r')
			break;
		++p;
	}
	p[i]=0;
}
void uart0_rx_str(unsigned char *p,int l)
{
int i;
	for(i=0;i<l;i++)
	{
	while(1)
	{
	p[i]=uart0_rx();
		if(p[i]=='\r')
			break;
		p++;
	}
	p[i]='\0';
	}
}
void uart0_int(int num)
{
int a[10], i = 0;
if(num == 0) // If number is zero, print '0'
{
uart0_tx('0');
}
if(num < 0) // If negative, print minus sign
{
num = -num;
uart0_tx('-');
}
while(num > 0) // Extract individual digits
{
a[i] = num % 10 + 48; // Convert numeric to ASCII
num = num / 10; // Reduce number
i++;
}
for(i = i-1; i >= 0; i--) // Print digits in correct order
{
uart0_tx(a[i]);
}
}
void uart0_float(float f)
{

}