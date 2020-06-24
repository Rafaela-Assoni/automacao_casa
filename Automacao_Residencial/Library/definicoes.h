/*
 * definicoes.h
 *
 *  Created on: 10 de jun de 2020
 *      Author: Fabiano
 * Entrada Principal
 *
 *  Entradas: Sensor digital (ler estado da porta)
 *  Saidas: Saida digital (trancar, destrancar a porta c/senha
 *  		,c/timeout), saida digital alarme (c/senha)
 *  Total: 1 dg input, 2 dg output
 *
 * Sala de estar
 *
 *  Entrada: digital temp -> saida arC
 *  Saida: dg output ArC ->(modoAuto ou manual),
 * 		  saida an (manual temp, 1.7V=17C)
 * 		  saida an luz (0V off, 5V on)
 *  Total: 1 dg input, 1 dg output, 2 an output
 *
 * Janelas da sala de estar e jantar
 *  Entrada: 2 sensor an (cortinas 1v=closed, 4v=fullopen),
 *  		1 sensor an vento(0.5V = 5km/h, 4.5V=150km/h)
 *  Saida: 2 dg output
 *	Total: 3 an in, 2 dg out
 * Quarto e banheiro
 *   Entrada: an input Temp
 *   Saida: 1 dg out, 1 an out
 *   Total: 1 an in, 1 dg out, 1 an out
 *
 *
 *Sum: Entradas digitais: 2
 *Sum: Entradas analogicas: 4
 *Sum: Saidas digitais: 6 (-2 talvez) +1 pin pra cada motor
 *Sum: Saidas analogicas:3= pwm (+2 talvez)
 *Sum:
 *Sum: Talvez cada motor tenha uma saida a mais para rotacao invertida
 * */


#ifndef LIBRARY_DEFINICOES_H_
#define LIBRARY_DEFINICOES_H_

//Entrada principal
#define porta_input 22
#define porta_output 23
#define porta_alarme 24
//sala de estar
#define sala_in_temp 25
#define sala_out_arc 26
#define sala_out_lamp 7 //pwm
#define sala_out_man 8 //pwm
//janelas
#define janela_out_cortina1p 27
#define janela_out_cortina1n 28
#define janela_out_cortina2p 29
#define janela_out_cortina2n 30
#define janela_in_cortina1 A2
#define janela_in_cortina2 A3
#define janela_anem A0 //an in
//quarto e banheiro
#define banheiro_temp A1
#define banheiro_out_aq 31
#define banheiro_out_lamp 9 //pwm

#define TimeOffset 1000


#endif /* LIBRARY_DEFINICOES_H_ */
