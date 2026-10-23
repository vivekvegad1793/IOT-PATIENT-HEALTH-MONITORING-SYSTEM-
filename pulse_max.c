#include "header.h"

void Pulse_WriteReg(unsigned char reg,unsigned char value){
i2c_send(MAX30102_ADDR,reg,value);
}

unsigned char Pulse_ReadReg(unsigned char reg){
return i2c_read(MAX30102_ADDR, reg);
}


void pulse_init(void){
/*reset*/
Pulse_WriteReg(MAX_MODE_CONFIG,0x40);

delay_ms(100);

/*FIFO*/
Pulse_WriteReg(MAX_FIFO_WR_PTR,0x00);
Pulse_WriteReg(MAX_OVF_COUNTER,0x00);
Pulse_WriteReg(MAX_FIFO_RD_PTR,0x00);

/*FIFO CONFIG*/
Pulse_WriteReg(MAX_FIFO_CONFIG,0X0F);

/*SPO2 CONFIG*/
Pulse_WriteReg(MAX_SPO2_CONFIG,0X27);

/*SPO2 MODE*/
Pulse_WriteReg(MAX_MODE_CONFIG,0X03);

/*LED_CURRENT*/
Pulse_WriteReg(MAX_LED1_PA,0X24);
Pulse_WriteReg(MAX_LED2_PA,0X24);

/*INTERRUPT*/
Pulse_WriteReg(MAX_INTR_ENABLE_1,0X40);
Pulse_WriteReg(MAX_INTR_ENABLE_2,0X00);

}

void Pulse_ReadFIFO(MAX30102_DATA *sample){
unsigned char data[6];

i2c_read_multi(MAX30102_ADDR,MAX_FIFO_DATA,data,6);
//data = i2c_read(MAX30102_ADDR,MAX_FIFO_DATA);
sample->red = ((unsigned long )data[0] << 16) | ((unsigned long)data[1] << 8) | ((unsigned long)data[2]);

sample->ir = ((unsigned long )data[3] << 16) | ((unsigned long )data[4] << 8) | ((unsigned long )data[5]);

/*18 bit adc value*/
sample->red &= 0x03ffff;
sample->ir &= 0x03ffff;
}

