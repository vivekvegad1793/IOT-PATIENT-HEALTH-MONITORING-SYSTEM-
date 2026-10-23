#include "header.h"


#define SAMPLE_RATE 100
#define BUFFER_SIZE 100
#define FILTER_SIZE 8
#define MIN_PEAK_DISTANCE 40
#define MAX_BEATS 5

static unsigned long ir_filter[FILTER_SIZE];
static unsigned char filter_index;
static unsigned long ir_buffer[FILTER_SIZE];
static unsigned long red_buffer[BUFFER_SIZE];
static unsigned short sample_index;
//static unsigned char index = 0;
//static unsigned long avg=0;
static unsigned long prev_avg = 0;
//static unsigned int sample_count = 0;
static unsigned short last_peak =0;
static unsigned char rising =0;

static unsigned short beat_interval[MAX_BEATS];
static unsigned char beat_index;

static unsigned long moving_average(unsigned long value)
{
unsigned long sum=0;
unsigned char i;
ir_filter[filter_index]=value;
filter_index++;
if(filter_index>=FILTER_SIZE)
filter_index=0;
for(i=0;i<FILTER_SIZE;i++)
sum+=ir_filter[i];
return sum/FILTER_SIZE ;
}

void algorithm_init(){

   unsigned short i;

   for(i=0 ; i<	FILTER_SIZE ; i++)
   ir_filter[i] = 0;
 for(i=0 ; i<BUFFER_SIZE ; i++)
 {
   ir_buffer[i] = 0;
   red_buffer[i]=0;
   }

	filter_index =0;
	sample_index=0;
	prev_avg =0;
	beat_index =0;
	last_peak	 =0;
	rising =0;
}

unsigned char algorithm_process(unsigned long ir, unsigned long red,pulse_result *result){

	unsigned short i;
	//unsigned long sum =0;
	  unsigned long avg ;
	  unsigned short diff;

	  unsigned long ir_max,ir_min;
	  unsigned long red_max,red_min;
	  float ac_ir;
	  float dc_ir;

	  float ac_red;
	  float dc_red;
	float ratio;
	ir_buffer[sample_index] = ir;
	red_buffer[sample_index]=red;
	avg=moving_average(ir);

	sample_index++;
	if(sample_index >=  BUFFER_SIZE)
	sample_index =0;

	if(avg>prev_avg)
	rising=1;

	 if((avg<prev_avg)&&rising)
	 {
	 diff=(sample_index>=last_peak)?(sample_index-last_peak):(BUFFER_SIZE-last_peak+sample_index);
	 if(diff>MIN_PEAK_DISTANCE)
	 {
	 beat_interval[beat_index]=diff;
	 beat_index++;
	 if(beat_index>=MAX_BEATS)
	 beat_index=0;
	 last_peak=sample_index;
	 rising=0;
	 diff=0;
	 for(i=0;i<MAX_BEATS;i++)
	 diff+=beat_interval[i];
	 diff/=MAX_BEATS;
	 result->bpm=(60*SAMPLE_RATE)/diff;
	 ir_max=0;
	 ir_min=0xffffffff;
	 red_max=0;
	 red_min=0xfffffff;
	 for(i=0 ; i< BUFFER_SIZE ; i++)
	 {
	 if(ir_buffer[i]>ir_max)
	 ir_max=ir_buffer[i];

	 if(ir_buffer[i]<ir_min)
	 ir_min=ir_buffer[i];

	 if(red_buffer[i]>red_max)
	 red_max=red_buffer[i];

	  if(red_buffer[i]<red_min)
	 red_min=red_buffer[i];
	 }
	 dc_ir=(ir_max+ir_min)/2.0f;
	 ac_ir=(ir_max-ir_min);

	 dc_red=(red_max+red_min)/2.0f;
	 ac_red=(red_max-red_min);    //I CHANGE THE ac_ir to ac_red 

	 ratio=(ac_red/dc_red)/(ac_ir/dc_ir);

	 result->spo2=110.0f-(25.0f*ratio);

	 if(result->spo2>100)
	 result->spo2=100;

	 if(result->spo2<80)
	 result->spo2=80;

	 result->valid=1;
	 prev_avg=avg;
	 return 1;
	 }
   rising=0;
   }
   prev_avg=avg;
   result->valid=0;
   return 0;

}
	 /*
	 }
	for(i=0 ; i< FILTER_SIZE ; i++)
	sum += 	ir_buf[i];

	avg = sum/FILTER_SIZE ;
	sample_count++;

	if(	avg > prev_avg)
	rising =1;

	if((avg < prev_avg) && rising){
	 unsigned int diff;
	 diff = sample_count - last_peak;

	 if(diff > MIN_PEAK_DISTANCE){

	 result->bpm = (60*SAMPLE_RATE)/diff;
	 ratio = (float)red/(float)ir;

	 result->spo2 = 110.0-(25.0*ratio);

	 if(result->spo2 > 100)
	 result->spo2 = 100;

	 if(result->spo2 < 80)
	 result->spo2 = 80;

	 last_peak = sample_count;

	 rising = 0;
	 prev_avg = avg;

	 return 1;

	 }
	 rising =0;

	}

	prev_avg = avg;
	return 0;
}
*/
