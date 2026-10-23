#include "pulse_max.h"
#include <lpc21xx.h>
#include "algorithm_max.h"

void adc_init(void);
unsigned int adc_read(int ch);

void lcd_data(unsigned char data);
void lcd_cmd(unsigned int cmd);
void lcd_init(void);
void lcd_str(char *p);

void uart0_rx_str(unsigned char *p,int l);
void uart0_tx_str(char *p);
unsigned char uart0_rx(void);
void uart0_tx(unsigned char data);
void uart0_init(unsigned int baud);
void uart0_float(float f);

void delay_s(unsigned int s);
void delay_ms(unsigned int ms);


void i2c_init(void);
void i2c_send(unsigned char sa,unsigned char mr,unsigned char data);
unsigned char i2c_read(unsigned char sa, unsigned char mr);
void i2c_read_multi(unsigned char sa,unsigned char mr,unsigned char *bf,unsigned char len);

void DHT11_init(void);
unsigned char DHT11_Start(void);
unsigned char DHT11_ReadByte(void);
unsigned char DHT11_ReadTemperature(void);

void esp_init();
int esp_ck();
int esp_reset();
int esp_setmode(unsigned char mode);
int esp_mux();
int esp_cnt(char *ssid,char *pswd);
int esp_getip();
int esp_stcp(char *svr,unsigned int port);
int esp_senddata(char *data);
int esp_ctcp();
int esp_stk(unsigned int temp, float spo2, unsigned int bpm);
void esp_res(char *buf);
