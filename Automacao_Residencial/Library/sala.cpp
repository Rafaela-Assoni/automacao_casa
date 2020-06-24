/*
 * sala.cpp
 *
 *  Created on: 10 de jun de 2020
 *      Author: acer
 */
#include <Arduino.h>
#include "DHT.h"
#include "definicoes.h"

DHT dht(sala_in_temp,DHT22);

void sala_beginsensor(int8_t){
	dht.begin();
}

float sala_readtemp(){
	float temp=0;
	temp = dht.readTemperature();

	return temp;
}
void sala_setarc(int8_t pin, int state){
	digitalWrite(pin,state);
}

int sala_mode(int mode_manual){
	return mode_manual;
}
int sala_arc_mode(int8_t mode, int8_t manual_temp){
	float pwm_value = manual_temp * 5.1;

	analogWrite(sala_out_man,pwm_value);
	return mode;
}

void sala_set_arc(int8_t manual_temp){
	float pwm_value = manual_temp * 5.1;

	analogWrite(sala_out_man,pwm_value);
}
void sala_lamp(int8_t lum_percent){
	float pwm_value = lum_percent*2.55;

	analogWrite(sala_out_lamp, pwm_value);
}


