/*
 * banheiro.cpp
 *
 *  Created on: 10 de jun de 2020
 *      Author: acer
 */
#include <Arduino.h>
#include "definicoes.h"

void banheiro_lamp(int8_t lum_percent){
	float pwm_value = lum_percent*2.55;

	analogWrite(banheiro_out_lamp, pwm_value);
}
int banheiro_sethist(int8_t value){

	return value;
}

void banheiro_heat(int state){
	digitalWrite(banheiro_out_aq, state);
}

int banheiro_read(){
	const float convert = 10* 5.0/1023;

	return analogRead(banheiro_temp)*convert;
}

