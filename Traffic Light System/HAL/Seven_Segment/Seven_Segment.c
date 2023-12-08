/*
 * Seven_Segment.c
 *
 * Created: 11/24/2023 5:44:14 PM
 *  Author: Ahmed Mamdouh
 */ 


#include "Seven_Segment.h"

void Seven_Segment_Init(Seven_Segment_t *Seven_Segment_ptr){
	gpio_pin_set_direction(Seven_Segment_ptr->SS_PINA_PORT, Seven_Segment_ptr->SS_PINA_PIN, OUTPUT);
	gpio_pin_set_direction(Seven_Segment_ptr->SS_PINB_PORT, Seven_Segment_ptr->SS_PINB_PIN, OUTPUT);
	gpio_pin_set_direction(Seven_Segment_ptr->SS_PINC_PORT, Seven_Segment_ptr->SS_PINC_PIN, OUTPUT);
	gpio_pin_set_direction(Seven_Segment_ptr->SS_PIND_PORT, Seven_Segment_ptr->SS_PIND_PIN, OUTPUT);
	};

void Seven_Segment_Write(Seven_Segment_t *Seven_Segment_ptr,uint8_t number){
	gpio_pin_set_value(Seven_Segment_ptr->SS_PINA_PORT, Seven_Segment_ptr->SS_PINA_PIN, (number&0x01));
	gpio_pin_set_value(Seven_Segment_ptr->SS_PINB_PORT, Seven_Segment_ptr->SS_PINB_PIN, ((number>>1)&0x01));
	gpio_pin_set_value(Seven_Segment_ptr->SS_PINC_PORT, Seven_Segment_ptr->SS_PINC_PIN, ((number>>2)&0x01));
	gpio_pin_set_value(Seven_Segment_ptr->SS_PIND_PORT, Seven_Segment_ptr->SS_PIND_PIN, ((number>>3)&0x01));	
	};

