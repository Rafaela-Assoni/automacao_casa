/*
 * Conversores.cpp
 *
 *  Created on: 11 de jun de 2020
 *      Author: acer
 */
#include <Arduino.h>
#include <math.h>

int16_t toInt4(char a,char b,char c, char d){
	int16_t number =0;

	number+= (a-'0')*1000;
	number+= (b-'0')*100;
	number+= (c-'0')*10;
	number+= (d-'0');

return number;
}
int16_t toInt3(char a,char b,char c){
	int16_t number =0;

	number+= (a-'0')*100;
	number+= (b-'0')*10;
	number+= (c-'0');

return number;
}
uint8_t toInt2(char a,char b){
	int number =0;

	number+= (a-'0')*10;
	number+= (b-'0');

return number;
}
uint8_t toInt1(char a){
	int number =0;

	number+= (a-'0');

return number;
}
int16_t perc_to_analog(int16_t perc,int bits_resolution){
	int max_value= pow(2,bits_resolution) -1;
	int16_t ret =  perc *max_value/100;
	if (perc==0)ret=0;
	return ret;
}
int16_t analog_to_perc(int16_t analog,int bits_resolution, int cort){
	float max_value= pow(2,bits_resolution) -1;
	float aux1= max_value*0.8 - max_value*0.2;
	int16_t ret=0;
	if(cort==1){

		 ret =  ((analog*0.8 -analog*0.2)/aux1)*100;
	}

	else ret =  (analog/max_value)*100;
	Serial.print("PRA PROCENTAGEM: ");
	Serial.println(ret);

	return ret;
}
void int_to4char(char *w,int value){
	//int aux=0;
	 if (value ==0){
		 w[0]='0';
		 w[1]='0';
		 w[2]='0';
		 w[3]='0';
	 }
	 else{
		 if(value ==100){
			 w[0]='0';
			 w[1]='1';
			 w[2]='0';
			 w[3]='0';
		 }
		 else if(value<100&&value>9){
			 	 	 	w[0]='0';
			 	 	 	w[1]='0';
			 	 	 	w[2]= (value/10)+0x30;
			 		 	w[3]= value%10+0x30;
			 		 	//w[3]= (aux%10)+0x30;
		 }
		 else if(value<10) {
		    w[0]='0';
		    w[1]='0';
		    w[2]='0';
		    w[3]= value +0x30;
		 }
	 }
	//Serial.print("Value na funcao: ");
	//Serial.print(value);
	//Serial.print("w na funcao: ");
	//Serial.print(w);
}


