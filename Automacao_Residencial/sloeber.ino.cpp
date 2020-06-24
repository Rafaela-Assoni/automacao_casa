#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2020-06-24 14:55:30

#include "Arduino.h"
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

void setup() ;
void Time_count();
void blink_buzz();
void loop() ;
void process();
void monitor();
void sala_handler(String msg) ;
void janela_handler(String msg) ;
void quarto_bath_handler(String msg) ;
void porta_handler(String msg) ;
void msgHandler() ;

#include "Automacao_Residencial.ino"


#endif
