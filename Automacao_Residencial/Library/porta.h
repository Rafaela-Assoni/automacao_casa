/*
 * porta.h
 *
 *  Created on: 10 de jun de 2020
 *      Author: acer
 */

#ifndef LIBRARY_PORTA_H_
#define LIBRARY_PORTA_H_
#include <Arduino.h>
//#include "./porta.cpp"

int porta_read(int8_t pin);

void porta_write(int8_t pin, int state);

void alarm_handler(int8_t state);

void porta_alarm(int8_t pin, int state);

void porta_msg(char *msg);

void porta_start_timer();


#endif /* LIBRARY_PORTA_H_ */
