/*
 * conversores.h
 *
 *  Created on: 11 de jun de 2020
 *      Author: acer
 */

#ifndef LIBRARY_CONVERSORES_H_
#define LIBRARY_CONVERSORES_H_
#include <Arduino.h>
//#include "conversores.cpp"

int16_t toInt4(char a,char b,char c, char d);
int16_t toInt3(char a,char b,char c);
uint8_t toInt2(char a,char b);
uint8_t toInt1(char a);
int16_t perc_to_analog(int16_t perc,int bits_resolution);
int16_t analog_to_perc(int16_t analog,int bits_resolution,int cort);
void int_to4char(char *w,int value);



#endif /* LIBRARY_CONVERSORES_H_ */
