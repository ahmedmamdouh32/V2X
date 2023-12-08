/*
 * hal_led.h
 *
 *  Created on: Nov 18, 2023
 *      Author: Adnan
 */

#ifndef HAL_LED_HAL_LED_H_
#define HAL_LED_HAL_LED_H_

/* ------------------------------- Includes ------------------------------- */
#include "../../MCAL/GPIO/mcal_gpio.h"

/* ------------------------------- Macros Declarations ------------------------------- */
			
//**************Pedsterians LEDs**************

#define ped_red_port				PORTA_INDEX
#define ped_red_pin					PIN0

#define ped_yellow_port				PORTA_INDEX
#define ped_yellow_pin				PIN1

#define ped_green_port				PORTA_INDEX
#define ped_green_pin				PIN2


//**************Cars LEDs**************
#define car_red_port				PORTB_INDEX
#define car_red_pin					PIN0

#define car_yellow_port				PORTB_INDEX
#define car_yellow_pin				PIN1

#define car_green_port				PORTB_INDEX
#define car_green_pin				PIN2

/* ------------------------------- data types declarations ------------------------------- */


/* ----------------------- Software Interfaces Declarations ----------------------- */
/**
 * @brief Initialize Led Pin as Input
 * @param _led_port Port index for led
 * @param _led_pin  pin number for led
 * @return none
 */
void led_init(gpio_port_index_t _led_port, gpio_pin_index_t _led_pin);

/**
 * @brief Turn on Led(output High on led pin)
 * @param _led_port Port index for led
 * @param _led_pin  pin number for led
 * @return none
 */
void led_turn_on(gpio_port_index_t _led_port, gpio_pin_index_t _led_pin);

/**
 * @brief Turn off Led(output Low on led pin)
 * @param _led_port Port index for led
 * @param _led_pin  pin number for led
 * @return none
 */
void led_turn_off(gpio_port_index_t _led_port, gpio_pin_index_t _led_pin);

/**
 * @brief toggle led state
 * @param _led_port Port index for led
 * @param _led_pin  pin number for led
 * @return none
 */
void led_toggle(gpio_port_index_t _led_port, gpio_pin_index_t _led_pin);


#endif /* HAL_LED_HAL_LED_H_ */
