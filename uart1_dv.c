#include<lpc21xx.h>
#define THRE ((U1LSR>>5)&1)
#define RDR (U1LSR&1)
void uart1_init(unsigned int baud)
{
int result=0,pclk;
if(VPBDIV==0)
pclk=15000000;
else if (VPBDIV==1)
pclk=60000000;
else if (VPBDIV==2)
pclk=30000000;

result=pclk/(16*baud);
PINSEL0 |=0x00050000;
U1LCR=0x83;
U1DLL=result&0xff;
U1DLM=(result>>8)&0xff;
U1LCR=0x03;
}
void uart1_tx(unsigned int data)
{
while(THRE==0);
U0THR=data;
}
unsigned int uart1_rx()
{
while(RDR==0);
return U1RBR;
}
void uart1_tx_str(char *p)
{
unsigned int i;
	while(1)
	{
   	p[i]=uart1_rx();
		if(p[i]=='\r')
			break;
		++p;
	}
	p[i]=0;
}
void uart1_rx_str(unsigned char *p,int l)
{
int i;
	for(i=0;i<l;i++)
	{
	while(1)
	{
	p[i]=uart1_rx();
		if(p[i]=='\r')
			break;
		p++;
	}
	p[i]='\0';
	}
}
void uart1_int(int num)
{
int a[10], i = 0;
if(num == 0) // If number is zero, print '0'
{
uart1_tx('0');
}
if(num < 0) // If negative, print minus sign
{
num = -num;
uart1_tx('-');
}
while(num > 0) // Extract individual digits
{
a[i] = num % 10 + 48; // Convert numeric to ASCII
num = num / 10; // Reduce number
i++;
}
for(i = i-1; i >= 0; i--) // Print digits in correct order
{
uart1_tx(a[i]);
}
}

