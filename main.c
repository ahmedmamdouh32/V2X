/*
* FinalAdnan.c
*
* Created: 11/21/2023 12:07:07 AM
* Author : Ahmed Mamdouh
*/

#include "MCAL/GPIO/mcal_gpio.h"
#include "MCAL/INTERRUPT/mcal_ext_interrupt.h"
#include "HAL/LED/hal_led.h"
#include "HAL/BUTTON/hal_button.h"
#include "MCAL/TIMERS/TIMER0/mcal_timer0.h"
#include "HAL/Seven_Segment/Seven_Segment.h"


#define CAR_STATE_RED 0
#define CAR_STATE_YELLOW 1
#define CAR_STATE_GREEN 2

uint8_t go_green=1;
uint8_t go_red=1;
uint8_t go_yellow=1;


sint8_t car_leds_iterator=0;
uint8_t car_led_state = 0;
uint8_t rec_data;

void idle_state();
void car_state_green_routine();
void EXT_INT0_CallBack(void);

Seven_Segment_t traffic_light_seven_segment={
	.SS_PINA_PORT = PORTB_INDEX,
	.SS_PINA_PIN  = PIN3,
	.SS_PINB_PORT = PORTB_INDEX,
	.SS_PINB_PIN  = PIN4,
	.SS_PINC_PORT = PORTB_INDEX,
	.SS_PINC_PIN  = PIN5,
	.SS_PIND_PORT = PORTB_INDEX,
	.SS_PIND_PIN  = PIN6
};


Timer0_cfg_t my_timer={
	/* -------------- Configurations for 1sec delay */
	.Timer0_mode            = TIMER0_MODE_NORMAL,
	.TIMER0_CALLBACK        = NULL,
	.Timer0_PreScaler       = TIMER0_CLOCK_PRESCALER_256,
	.Timer0_Preloaded_Value = 10,
	.COV= 80
};

int main(void)
{
	led_init(ped_red_port,ped_red_pin);
	led_init(ped_yellow_port,ped_yellow_pin);
	led_init(ped_green_port,ped_green_pin);
	led_init(car_red_port,car_red_pin);
	led_init(car_yellow_port,car_yellow_pin);
	led_init(car_green_port,car_green_pin);

	Seven_Segment_Init(&traffic_light_seven_segment);

	Interrupr_INTx_Init(EXT_INT0, INTx_SENSE_RISING_EDGE, EXT_INT0_CallBack);


	Timer0_Init(&my_timer);

	while (1)
	{
		idle_state();
	}
}

void idle_state(){

	//turning off all Leds
	led_turn_off(ped_red_port,ped_red_pin);
	led_turn_off(ped_yellow_port,ped_yellow_pin);
	led_turn_off(ped_green_port,ped_green_pin);

	led_turn_off(car_red_port,car_red_pin);
	led_turn_off(car_yellow_port,car_yellow_pin);
	led_turn_off(car_green_port,car_green_pin);


if(go_green){
	//******open green led for 10 seconds******
	go_red=1;
	car_led_state = CAR_STATE_GREEN;
	led_turn_on(car_green_port,car_green_pin);
	car_leds_iterator = 9;
	while(car_leds_iterator >= 0){
		Seven_Segment_Write(&traffic_light_seven_segment,car_leds_iterator);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	led_turn_off(car_green_port,car_green_pin);
}

if(go_red){
	//******open red led for 10 seconds******
	go_yellow=1;
	car_led_state = CAR_STATE_RED;
	car_leds_iterator=9;
	led_turn_on(car_red_port,car_red_pin);
	while(car_leds_iterator >= 0){
		Seven_Segment_Write(&traffic_light_seven_segment,car_leds_iterator);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	led_turn_off(car_red_port,car_red_pin);
}

if(go_yellow){
	//******toggle yellow led for 4 seconds******
	go_green=1;
	car_led_state = CAR_STATE_YELLOW;
	car_leds_iterator=4;
	while(car_leds_iterator >= 0){
		Seven_Segment_Write(&traffic_light_seven_segment,car_leds_iterator);
		led_toggle(car_yellow_port,car_yellow_pin);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	led_turn_off(car_yellow_port,car_yellow_pin);	
}
}


void car_state_green_routine(){

	while(car_leds_iterator >= 0){
		Seven_Segment_Write(&traffic_light_seven_segment,car_leds_iterator);
		led_toggle(ped_yellow_port,ped_yellow_pin);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	
	led_turn_off(ped_yellow_port,ped_yellow_pin);
	led_turn_on(ped_green_port,ped_green_pin);
	led_turn_off(car_green_port,car_green_pin);
	led_turn_on(car_red_port,car_red_pin);
	car_leds_iterator = 9;
	
	while(car_leds_iterator >= 0){
		Seven_Segment_Write(&traffic_light_seven_segment,car_leds_iterator);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	
	car_leds_iterator = 4;
	
	while(car_leds_iterator >= 0){
		Seven_Segment_Write(&traffic_light_seven_segment,car_leds_iterator);
		led_toggle(ped_yellow_port,ped_yellow_pin);
		led_toggle(car_yellow_port,car_yellow_pin);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	
	led_turn_off(ped_yellow_port,ped_yellow_pin);
	led_turn_off(car_yellow_port,car_yellow_pin);
	led_turn_off(ped_green_port,ped_green_pin);
	led_turn_off(car_red_port,car_red_pin);
	go_red=0;
	go_yellow=0;
}



void car_state_red_routine(){
	led_turn_on(ped_green_port,ped_green_pin);
	sint8_t waiting_time= 9-car_leds_iterator;
	while(car_leds_iterator >= 0){
		Seven_Segment_Write(&traffic_light_seven_segment,car_leds_iterator);	
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	
	car_leds_iterator = 4+waiting_time;
	if(car_leds_iterator >9){
		car_leds_iterator = 9;
	}
	
	while(car_leds_iterator >= 0){
		Seven_Segment_Write(&traffic_light_seven_segment,car_leds_iterator);
		led_toggle(ped_yellow_port,ped_yellow_pin);
		led_toggle(car_yellow_port,car_yellow_pin);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	
	led_turn_off(ped_yellow_port,ped_yellow_pin);
	led_turn_off(car_yellow_port,car_yellow_pin);
	led_turn_off(ped_green_port,ped_green_pin);
	led_turn_off(car_red_port,car_red_pin);
	
	go_yellow=0;	
}


void car_state_yellow_routine(){
	while(car_leds_iterator >= 0){
		Seven_Segment_Write(&traffic_light_seven_segment,car_leds_iterator);
		led_toggle(car_yellow_port,car_yellow_pin);
		led_toggle(ped_yellow_port,ped_yellow_pin);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	
	led_turn_off(car_yellow_port,car_yellow_pin);
	led_turn_on(car_green_port,car_green_pin);
	
	car_leds_iterator = 9;
	while(car_leds_iterator >= 0){
		Seven_Segment_Write(&traffic_light_seven_segment,car_leds_iterator);
		led_toggle(ped_yellow_port,ped_yellow_pin);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}

	led_turn_off(ped_yellow_port,ped_yellow_pin);
	led_turn_off(car_green_port,car_green_pin);
	led_turn_on(ped_green_port,ped_green_pin);
	led_turn_on(car_red_port,car_red_pin);
	
	car_leds_iterator = 9;
	while(car_leds_iterator >= 0){
		Seven_Segment_Write(&traffic_light_seven_segment,car_leds_iterator);
		Timer0_WaitBlocking(&my_timer);
		car_leds_iterator--;
	}
	
	go_green=0;
	go_red=0;
}


/* --------------------------------------- EXT INT0 ISR --------------------------------------- */
void EXT_INT0_CallBack(void)
{
	//check for state of cars' LEDS
	switch(car_led_state){
		case CAR_STATE_RED:
		car_state_red_routine();
		break;

		case CAR_STATE_YELLOW:
		car_state_yellow_routine();
		break;
		
		case CAR_STATE_GREEN:
		car_state_green_routine();
		break;
	}

}