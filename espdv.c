//esp
#include<lpc21xx.h>
#include"header.h"
//#include"../pulse_max.h"
//#include"../algorithm_max.h"
#include<stdio.h>
#include<string.h>
//MAX30102_DATA SAMPLE;
//pulse_result PULSE;
float spo2;
unsigned int temp ,bpm;
//unsigned int temp;
char buf[200];
void esp_init()
 {
  uart1_init(9600);
 // uart0_init(9600);
  delay_ms(1000);
 }
int esp_ck()
{
char buf[50];
uart1_tx_str("AT\r\n");
esp_res(buf);
if(strstr(buf,"OK")!=NULL)
return 1;
return 0;
}
int esp_reset()
{
uart1_tx_str("AT+RST\r\n");
delay_ms(2000);
return 1;
}
int esp_setmode(unsigned char mode)
{
char cmd[30];
sprintf(cmd,"AT+CWMODE=%d\r\n",mode);
uart1_tx_str(cmd);
delay_ms(1000);
return 1;
}
int esp_mux()
{
char buf[100];
uart1_tx_str("AT+CIPMUX=0\r\n");
esp_res(buf);
if(strstr(buf,"OK"))
return 1;

return 0;
}
//void esp_cmd(char *cmd)
//{
//uart0_tx_str(cmd);
//}	
 int esp_cnt(char *ssid, char *pswd)
{
    char cmd[80];
    char buf[200];
    sprintf(cmd,"AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,pswd);
    uart1_tx_str(cmd);
    esp_res(buf);        // Read ESP8266 response
    if(strstr(buf,"WIFI GOT IP")!=NULL)
        return 1;
    if(strstr(buf,"OK")!=NULL)
        return 1;
    if(strstr(buf,"FAIL")!=NULL)
        return 0;
    if(strstr(buf,"ERROR")!=NULL)
        return 0;
    return 0;
}
 int esp_getip()
 {
 uart1_tx_str("AT+CIFSR\r\n");
 delay_ms(1000);
 return 1;
 }
int esp_stcp(char *svr,unsigned int port)
{
char cmd[80];
sprintf(cmd,"AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",svr,port);
uart1_tx_str(cmd);
delay_ms(3000);
return 1;
}
int esp_senddata(char *data)
{
char cmd[20];
sprintf(cmd,"AT+CIPSEND=%d\r\n",strlen(data));
uart1_tx_str(cmd);
delay_ms(1000);
uart1_tx_str(data);
//delay_ms(3000);
return 1;
}
int esp_ctcp()
{
uart1_tx_str("AT+CIPCLOSE\r\n");
delay_ms(1000);
return 1;
}
int esp_stk(unsigned int temp, float spo2, unsigned int bpm)
{ 
char svr[] = "api.thingspeak.com";
int port = 80;
char http[150];
sprintf(http,"GET /update?api_key=GMPVQSP43TT8Z2ZO" 
"&field1=%u" 
"&field2=%.1f" 
"&field3=%.u HTTP/1.1\r\n"
"Host: api.thingspeak.com\r\n"
"Connection: close\r\n"
"\r\n",temp,spo2,bpm);
esp_senddata(http);

//sprintf(http,"GET /update?api_key=GMPVQSP43TT8Z2ZO" 
//"&field1=%d" 
//"&field2=%d" 
//"&field3=%.2f HTTP/1.1\r\n"
//"Host: api.thingspeak.com\r\n"
//"Connection: close\r\n"
//"\r\n",1,2,3);
//esp_senddata(http);

delay_ms(3000);
return 1;
}
void esp_res(char *buf)
{
 int i=0;
 char ch;
 memset(buf,0,200);
 while(1)
 {
  ch=uart1_rx();
  buf[i]=ch;
  i++;
  if(i>=199)
  {
  break;
  }
  if(ch=='\n')
  break;
 }
		buf[i]='\0';
}


