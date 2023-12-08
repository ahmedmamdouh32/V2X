/*
 * Seven_Segment.h
 *
 * Created: 11/24/2023 5:44:27 PM
 *  Author: compu magic
 */ 


#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_


#include "../../MCAL/GPIO/mcal_gpio.h"

typedef struct{
	uint8_t SS_PINA_PORT;
	uint8_t SS_PINA_PIN;
	uint8_t SS_PINB_PORT;
	uint8_t SS_PINB_PIN;
	uint8_t SS_PINC_PORT;
	uint8_t SS_PINC_PIN;
	uint8_t SS_PIND_PORT;
	uint8_t SS_PIND_PIN;
}Seven_Segment_t;



void Seven_Segment_Init(Seven_Segment_t *Seven_Segment_ptr);
void Seven_Segment_Write(Seven_Segment_t *Seven_Segment_ptr,uint8_t number);




#endif /* SEVEN_SEGMENT_H_ */