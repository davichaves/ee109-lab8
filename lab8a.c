/********************************************
*
*  Name: Davi Rodrigues Chaves
*  Section: W 3:30-5:00 PM
*  Assignment: Lab 8 - Rotary Encoders
*
********************************************/

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

void init_ports(void);
void init_adc(void);

int main(void) {
  //sei(); // Enable interrupts
  init_ports();
	init_lcd();
  writecommand(1); //clear LCD
  char myVar = '0';
  moveto(5);
  writedata(myVar);
  /* Main programs goes here */

  while (1) {
    
  } // Loop forever

  return 0;   /* never reached */
}

/*
  init_ports - Do various things to initialize the ports
*/

void init_ports() {
  PCMSK0 |= ((1 << PCINT5)| (1 << PCINT1));
  DDRD |= 0xF0; //setting D4-D7 as outputs
  DDRB |= 0x03; //seeting B1-B2 as outputs
}
