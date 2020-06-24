/*
 * banheiro.h
 *
 *  Created on: 10 de jun de 2020
 *      Author: acer
 */

#ifndef LIBRARY_BANHEIRO_H_
#define LIBRARY_BANHEIRO_H_
#include <Arduino.h>
//#include "banheiro.cpp"

void banheiro_lamp(int8_t lum_percent);
int banheiro_sethist(int8_t value);

void banheiro_heat(int state);

int banheiro_read();



#endif /* LIBRARY_BANHEIRO_H_ */
