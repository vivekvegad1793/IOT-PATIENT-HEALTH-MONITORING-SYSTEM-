#ifndef __pulse_max_H
#define __pulse_max_H

#include "header.h"
#include <lpc21xx.h>
#include <stdint.h>

//MAX i2c address
#define MAX30102_ADDR 0xAE

#define MAX_INTR_STATUS_1 0X00
#define MAX_INTR_STATUS_2 0X01
#define MAX_INTR_ENABLE_1 0X02
#define MAX_INTR_ENABLE_2 0X03

#define MAX_FIFO_WR_PTR 0X04
#define MAX_OVF_COUNTER 0X05
#define MAX_FIFO_RD_PTR 0X06
#define MAX_FIFO_DATA 0X07

#define MAX_FIFO_CONFIG 0X08
#define MAX_MODE_CONFIG 0X09
#define MAX_SPO2_CONFIG 0X0A

#define MAX_LED1_PA 0X0C
#define MAX_LED2_PA 0X0D

#define MAX_TEMP_INT 0X1F
#define MAX_TEMP_FRAC 0X20
#define MAX_TEMP_CONFIG 0X21

#define MAX_REV_ID 0XFE
#define MAX_PART_ID 0XFF

/*MODE CONFIG*/

#define MAX_MODE_HR 0X02
#define MAX_MODE_SPO2 0X03
#define MAX_MODE_MULTI_LED 0X07

/*FIFO BUFFER*/

typedef struct{
unsigned int red;
unsigned int ir;
}MAX30102_DATA;


/*function prototype*/

void pulse_init(void);
void Pulse_WriteReg(unsigned char reg,unsigned char value);
unsigned char Pulse_ReadReg(unsigned char reg);
void Pulse_ReadFIFO(MAX30102_DATA *sample);

#endif

