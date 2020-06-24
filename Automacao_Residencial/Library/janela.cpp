/*
 * janela.cpp
 *
 *  Created on: 10 de jun de 2020
 *      Author: acer
 */
#include <Arduino.h>
#include "definicoes.h"

int janela_read(int8_t pin){
	return analogRead(pin);
}

void janela_motor(int8_t pin_p,int8_t pin_n,int8_t sensor_pin,int16_t stop_value){

	if(stop_value < 0.2*1023)stop_value= 0.2*1023;
	else if(stop_value > 0.8*1023)stop_value =0.8*1023;


	if(janela_read(sensor_pin)> stop_value){
		digitalWrite(pin_n, HIGH);
		while(1){
			if(janela_read(sensor_pin)<= stop_value){
				digitalWrite(pin_n, LOW);
				break;
			}
		}
	}
	else {
		digitalWrite(pin_p, HIGH);
		while(1){
			if(janela_read(sensor_pin)>= stop_value){
				digitalWrite(pin_p, LOW);
				break;
			}
		}
	}
}
int janela_windread(int8_t pin){
	int convert= 33.3*(5.0/1023);
	return analogRead(pin)*convert;
	//Serial.println(analogRead(pin));
}
void janela_alert(){
	//fecha cortinas
	janela_motor(janela_out_cortina1p, janela_out_cortina1n,
			janela_in_cortina1, 4);

	janela_motor(janela_out_cortina2p, janela_out_cortina2n,
			janela_in_cortina2, 4);
}

