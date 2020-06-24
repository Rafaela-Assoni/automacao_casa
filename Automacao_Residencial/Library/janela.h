/*
 * janela.h
 *
 *  Created on: 10 de jun de 2020
 *      Author: acer
 */

#ifndef LIBRARY_JANELA_H_
#define LIBRARY_JANELA_H_
#include <Arduino.h>
//#include "janela.cpp"

int janela_read(int8_t pin);

void janela_motor(int8_t pin_p,int8_t pin_n,int8_t sensor_pin,int16_t stop_value);
int janela_windread(int8_t pin);
void janela_alert();



#endif /* LIBRARY_JANELA_H_ */
