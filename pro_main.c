#include <lpc21xx.h>
#include <stdio.h>
#include "header.h"

#define grn (1<<16)
#define rd  (1<<17)
#define buz (1<<18)

#define ir_threshold 75000

MAX30102_DATA SAMPLE;
pulse_result PULSE;
extern unsigned char Temp_Int;
extern unsigned int temp;
char s[50];
int main(void)

{
    /* GPIO Direction */
    IODIR0 |= (grn | rd | buz);

    /* Active LOW : Initially OFF */
    IOSET0 = grn | rd | buz;

    /* UART0 -> PC */
    uart0_init(9600);

    /* UART1 -> ESP8266 */
    esp_init();

    /* LCD */
    lcd_init();

    /* I2C */
    i2c_init();

    /* DHT11 */
    DHT11_Start();

    /* MAX30102 */
    pulse_init();
    algorithm_init();


    /************ ESP8266 ************/

//    if(!esp_ck())
//
//    {
//
//        uart0_tx_str("ESP8266 NOT FOUND\r\n");
//
//        while(1);
//
//    }
    esp_reset();
    esp_setmode(1);
    esp_cnt("Redmi","12345678");
    uart0_tx_str("WiFi Connected\r\n");
    esp_getip();
    /************ MAIN LOOP ************/
    while(1)
    {
        /* Read Temperature */
	//	uart0_tx_str("temp reading : ");
        Temp_Int = DHT11_ReadTemperature();
				//delay_ms(500);
        /* Read MAX30102 FIFO */
        Pulse_ReadFIFO(&SAMPLE);
        if(SAMPLE.ir > ir_threshold)
        {
            if(algorithm_process(SAMPLE.ir,
                                 SAMPLE.red,
                                 &PULSE))
            {

                /******** UART ********/
                sprintf(s,
                "Temperature : %hhu C\r\n"
                "Heart Rate  : %u BPM\r\n"
                "SpO2        : %.1f %%\r\n\r\n",
                Temp_Int,
                PULSE.bpm,
                PULSE.spo2);
                uart0_tx_str(s);
   	//	delay_ms(500);	  //atta dily
                /******** LCD ********/
                lcd_cmd(0x80);
                sprintf(s,"T:%u.C H:%u",Temp_Int,PULSE.bpm);
                lcd_str(s);
                lcd_cmd(0xC0);
                sprintf(s,"Sp:%2.1f%%",PULSE.spo2);
                lcd_str(s);
		     
                /******** INDICATION (ACTIVE LOW) ********/

                if((temp>38)||(PULSE.bpm<60)||(PULSE.bpm>100)||(PULSE.spo2<90))
                {
                    /* RED ON */
                    IOCLR0 = rd;
                    /* BUZZER ON */
                    IOCLR0 = buz;
                    /* GREEN OFF */
                    IOSET0 = grn;
                }
                else
                {
                    /* GREEN ON */
                    IOCLR0 = grn;
                    /* RED OFF */
                    IOSET0 = rd;
                    /* BUZZER OFF */
                    IOSET0 = buz;
                }
                /******** SEND TO THINGSPEAK ********/
                esp_stcp("api.thingspeak.com",80);
                esp_stk(Temp_Int,
                        PULSE.spo2,
                        PULSE.bpm);
                esp_ctcp();
                delay_ms(15000);
			 }
			//	delay_ms(500);

        }
		else
		{
		lcd_str("place the finger");
		}
		delay_ms(20);
	  
//	  		delay_ms(500);
    }	
//		delay_ms(500);

	
}