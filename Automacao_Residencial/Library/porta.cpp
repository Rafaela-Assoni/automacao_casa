/*
 * porta.cpp
 *
 *  Created on: 10 de jun de 2020
 *      Author: acer
 */
#include<Arduino.h>


int porta_read(int8_t pin){
	return digitalRead(pin);
}
void porta_write(int8_t pin, int state){
	digitalWrite(pin, state);
}


void porta_start_timer(){

}
void porta_alarm(int8_t pin, int state){
	//alarm_handler(state);
	digitalWrite(pin,state);
}

void porta_msg(char *msg){
	Serial.print(msg);
}
