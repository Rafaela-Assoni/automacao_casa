/*
 * sala.h
 *
 *  Created on: 10 de jun de 2020
 *      Author: acer
 */

#ifndef LIBRARY_SALA_H_
#define LIBRARY_SALA_H_
#include <Arduino.h>
//#include "sala.cpp"

void sala_beginsensor(int8_t);
float sala_readtemp();
void sala_setarc(int8_t pin, int state);
int sala_mode(int mode_manual);
int sala_arc_mode(int8_t mode, int8_t manual_temp);
void sala_lamp(int8_t lum_percent);
void sala_set_arc(int8_t manual_temp);



#endif /* LIBRARY_SALA_H_ */
