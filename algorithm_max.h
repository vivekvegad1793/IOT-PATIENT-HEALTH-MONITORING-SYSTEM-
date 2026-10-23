#ifndef __ALGORITHM_MAX_H__
#define __ALGORITHM_MAX_H__

#include <lpc21xx.h>

typedef struct{
	unsigned int bpm;
	float spo2;
	unsigned char valid;
}pulse_result;

void algorithm_init(void);
unsigned char algorithm_process(unsigned long ir, unsigned long red, pulse_result *result);

static unsigned long moving_average(unsigned long value);
#endif
