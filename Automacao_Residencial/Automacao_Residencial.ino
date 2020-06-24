#include <Arduino.h>
#include <stdint.h>
#include "Library/definicoes.h"
#include "Library/porta.h"
#include "Library/banheiro.h"
#include "Library/janela.h"
#include "Library/sala.h"
#include "Library/conversores.h"
#include <TimerOne.h>
#include <string.h>


int8_t porta_lockstatus = 0,porta_status=0,sala_manual=0,wind_alert=0,bath_heat =0,arc_status=0;
int8_t flag_timer=0, first=0,sala_temp=0, call_stop=0, lamp1=0,lamp2=0;
uint16_t close_timeout =0;
int8_t sala_temperature=0, bath_temperature=17, histerese =0;
char time1[]="08:00",time2[]="12:00",time3[]="18:00";
volatile uint32_t tempo=0;
volatile int8_t blink=0;
uint32_t tick = 0;

void setup() {
	Serial.begin(9600);

	//definicao da entrada principal/INPUT
	pinMode(porta_input, INPUT);
	//definicao da entrada principal/OUTPUT
	pinMode(porta_output, OUTPUT);
	pinMode(porta_alarme,OUTPUT);

	//definicao da sala /INPUT
	pinMode(sala_in_temp,INPUT);
	//definicao da sala/ OUTPUT
	pinMode(sala_out_arc, OUTPUT);
	pinMode(sala_out_lamp,OUTPUT);//PWM
	pinMode(sala_out_man, OUTPUT);//PWM

	//definicao da janela/ INPUT
	pinMode(janela_in_cortina1, INPUT);
	pinMode(janela_in_cortina2, INPUT);
	pinMode(janela_anem, INPUT);
	//definicao da janela/ OUTPUT
	pinMode(janela_out_cortina1n, OUTPUT);
	pinMode(janela_out_cortina1p, OUTPUT);
	pinMode(janela_out_cortina1n, OUTPUT);
	pinMode(janela_out_cortina2p, OUTPUT);

	//definicao do quarto e banheiro / INPUT
	pinMode(banheiro_temp, INPUT);
	//definica odo quarto e banheiro / OUTPUT
	pinMode(banheiro_out_aq,OUTPUT);
	pinMode(banheiro_out_lamp, OUTPUT);//PWM

	Serial.println("Testando a porta serial");
	tick = millis();

}
void Time_count(){

	tempo++;
}
void blink_buzz(){
	if(!first){
		porta_alarm(porta_alarme, 1);//liga buzzer
		blink=1;
		first=1;
	}
	if(blink==1 && tempo >= 2*60){
		tempo=0;
		porta_alarm(porta_alarme, 0);//desliga buzzer
		blink =0;
	}
	else if(blink==0 && tempo >=5*60){
		tempo=0;
		porta_alarm(porta_alarme, 1);
		blink=1;
	}
}

void loop() {
 msgHandler();
 process();
}
void process(){


	if(!porta_read(porta_input)&&porta_status==0){
		porta_start_timer();
		porta_status = 1;
	}
	if(porta_read(porta_input)==1 && call_stop==0){
		//if(timer_cont == time_out)porta_alarm
		if(!flag_timer){
			Timer1.initialize(1000000);
			Timer1.attachInterrupt(Time_count);
			flag_timer=1;
		}
		if(tempo>= close_timeout){
			Timer1.stop();
			Timer1.detachInterrupt();
			Timer1.initialize(1000000);
			tempo = 0;
			Timer1.attachInterrupt(blink_buzz);//ativa alarme
		}
	}
	else {
		if(flag_timer){
			Timer1.detachInterrupt();
			Timer1.stop();
			flag_timer=0;
		}
		if(!porta_read(porta_input))call_stop=0;
	}
	if(!sala_manual){

		if(sala_readtemp()> sala_temperature){
			sala_setarc(sala_out_arc, 1);
			arc_status=1;
		}
		else {
			sala_setarc(sala_out_arc, 0);
			arc_status=0;
		}
	}
	else {
		//manual temp
	}
	//time das cortinas precisa ser programado no serv
	if(janela_windread(janela_anem)>=50&&wind_alert==0){

		janela_alert();
		//quando for resposta vai ir um 1 na frente do local
		//pra identificar que é uma resposta

		Serial.println(":1300FFFF");//Wind Alert //endereco provisorio
		wind_alert=1;
	}
	if(banheiro_read() < bath_temperature +histerese){
		banheiro_heat(1);
		bath_heat =1;
	}
	else if(banheiro_read() > bath_temperature - histerese){
		banheiro_heat(0);
		bath_heat =0;
	}
	if(millis() >= tick + TimeOffset){
		tick =millis();
		monitor();
	}

}
void monitor(){
	char word[10]=":1303FFFF";
	char w[5]="FFFF";
	int var=0;
	//status porta : 1 1 0 3 FFFF/0000
	//status ar condicionado :
	//status cortina 1
	//status cortina 2
	//status aquecedor banheiro
	//velocidade vento
	//status lampada sala
	//status lampada quarto
	Serial.println("Porta ------------");
	if(porta_status)Serial.println(":1103FFFF");
	else Serial.println(":11030000");
	Serial.println("Arc ------------");
	if(arc_status>1){
		int_to4char(w, arc_status);

		word[5]=w[0];
		word[6]=w[1];
		word[7]=w[2];
		word[8]=w[3];
		Serial.println(word);
	}
	else if(arc_status)Serial.println(":1203FFFF");
	else Serial.println(":12030000");
	//cortinas 1 e 2
	Serial.println("Cortinas ------------");
	var =analog_to_perc(janela_read(janela_in_cortina1), 10,1);
	int_to4char(w, var);
	Serial.print("var1 = ");
	Serial.println(var);
	strcpy(word,":13030000");
	word[5]=w[0];
	word[6]=w[1];
	word[7]=w[2];
	word[8]=w[3];
	Serial.println(word);
	//Serial.println(janela_read(janela_in_cortina2));
	var =analog_to_perc(janela_read(janela_in_cortina2), 10,1);
	//Serial.print("Var 2em percent: ");
	//Serial.println(var);
	int_to4char(w, var);
	strcpy(word,":13040000");
	word[5]=w[0];
	word[6]=w[1];
	word[7]=w[2];
	word[8]=w[3];
	Serial.println(word);
	////////////////////////////////
	//vento
	Serial.println("Aquecedor e vento ------------");
	if(bath_heat)Serial.println(":1404FFFF");
	else Serial.println(":14040000");
	var = (int) janela_windread(janela_anem);
	int_to4char(w, var);
	strcpy(word,":13050000");
	word[5]=w[0];
	word[6]=w[1];
	word[7]=w[2];
	word[8]=w[3];
	Serial.println(word);
	//lamp1
	Serial.println("Lamp1 e2  ------------");
	var = lamp1;
	int_to4char(w, var);

	strcpy(word,":12040000");
	word[5]=w[0];
	word[6]=w[1];
	word[7]=w[2];
	word[8]=w[3];
	Serial.println(word);
	//lamp2

	var = lamp2;
	int_to4char(w, var);
	strcpy(word,":14030000");
	word[5]=w[0];
	word[6]=w[1];
	word[7]=w[2];
	word[8]=w[3];
	Serial.println(word);



}
void sala_handler(String msg) {
	const char CMD = msg[4];
	int value =0;

	switch (CMD) {
		case '1':
			//modo manual do ar condicionado on/off
			// + valor de temp da web
			// ativar pwm com
			value = toInt2(msg[7], msg[8]);
			if(value ==99){
				sala_manual=0;
				sala_mode(0);
				sala_set_arc(0);
				break;
			}
			if(!sala_manual){
				sala_manual = sala_arc_mode(!sala_manual,value);
				arc_status= value;
			}
			else sala_set_arc(value);
			break;
		case '2':
			//controle de luminosidade
			//ativar pwm com valor recebido e convertido
			lamp1=toInt3(msg[6], msg[7], msg[8]);
			Serial.print("Lamp 1 do arduino =");
			Serial.println(lamp1);
			value = perc_to_analog(lamp1, 8);
			sala_lamp(value);
			break;
		//case '3': //status arc, somente envio : 1 2 0 3 FFFF TRUE 0000 FALSE
		//	break;
		//case '4: //status lampada somente envio : 1 2 0 4 DADO
	}

}
void janela_handler(String msg) {
	const char CMD = msg[4];
	int value =0;

	switch (CMD) {

	case '1':
		//ativa modo manual 1
		//seta a cortina 1
		value = perc_to_analog(toInt3(msg[6], msg[7], msg[8]), 10);

		janela_motor(janela_out_cortina1p, janela_out_cortina1n, janela_in_cortina1,value);
		break;
	case '2':
		//ativa modo manual 2
		//seta a cortina 2
		value = perc_to_analog(toInt3(msg[6], msg[7], msg[8]), 10);
		janela_motor(janela_out_cortina2p, janela_out_cortina2n, janela_in_cortina2,value);
		break;
	}
	//case '3': status cortina 1 somente envio, : 1 3 0 3 DADO
	//case '4': status cortina 2 somente envio, : 1 3 0 4 DADO
	//case '5': envia dados vento : 1 3 0 5 DADO
}
void quarto_bath_handler(String msg) {
	char CMD = msg[4];
	int value=0;

	switch (CMD) {

	case '1':
		//seta luminosidade com o valor recebido
		//ativa o pwm com o valor recebido
		lamp2=toInt3(msg[6], msg[7], msg[8]);
		//Serial.print("Lamp 2 do arduino =");
		//Serial.println(lamp2);
		value = perc_to_analog(lamp2, 8);
		banheiro_lamp(value);
		break;
	case '2':
		//configura histerese do termometro do banheiro
		value = toInt4(msg[5], msg[6], msg[7], msg[8]);
		histerese = banheiro_sethist(value);
		break;

	}
	//case '3': status lampada quarto, somente envio, : 1 4 0 3 DADO
	//case '4': status estufa banheiro, somente envio : 1 4 0 4 FFFF TRUE /0000FALSE

}
void porta_handler(String msg) {
	 char CMD = msg[4];

	switch (CMD) {
	case '1':
		porta_write(porta_output, !porta_lockstatus);
		porta_lockstatus=!porta_lockstatus;
		break;
	case '2':
		call_stop =1;
		porta_alarm(porta_alarme, 0);//parar alarme
		Timer1.stop();
		Timer1.detachInterrupt();
		flag_timer =0;
		break;
	case '3':// status porta, somente envio :1 1 0 3 FFFF TRUE
			// status  porta, somente envio :1 1 0 3 0000 FALSE
		break;
	}
}
void msgHandler() {
	if (Serial.available() > 0) {
		while (Serial.available() > 0) {
			// ler toda a mensagem até encontrar LF
			String msg = Serial.readStringUntil('\n');

			if (msg[0] == ':') {
				const char place = msg[2];
				// Calcular LRC da Mensagem antes de prossegir....
				switch (place) { //o que antes era endereço do escravo alterei para endereço do local
				case '1':
					porta_handler(msg);
					break;
				case '2':
					sala_handler(msg);
					break;
				case '3':
					janela_handler(msg);
					break;
				case '4':
					quarto_bath_handler(msg);
					break;
				}
			}
		}
	}
}

