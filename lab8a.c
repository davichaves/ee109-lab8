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
void check_states(void);

int main(void) {
  //sei(); // Enable interrupts
  init_ports();
	init_lcd();
  writecommand(1); //clear LCD
  char myVar[20];
  int var = -10;
  moveto(5);
  int aState, bState;
  /* Main programs goes here */
  while (1) {
    if ((PINC & 0b00010000) == 0) { //A5 == 0
      aState = 0;
    } else {
      aState = 1;
    }
    if ((PINC & 0b00100000) == 0) { //A4 == 0
      bState = 0;
    } else {
      bState = 1;
    }

    if (/* condition */) {
      /* code */
    }
    snprintf(myVar, 20, "%d:%d", aState, bState);
    stringout(myVar);
    moveto(5);
  } // Loop forever

  return 0;   /* never reached */
}

void check_states() {

}

/*
  init_ports - Do various things to initialize the ports
*/

void init_ports() {
  PCMSK0 |= ((1 << PCINT5)| (1 << PCINT1));
  DDRD |= 0xF0; //setting D4-D7 as outputs
  DDRB |= 0x03; //seeting B1-B2 as outputs
  PORTC |= ((1 << PC4) | (1 << PC5));
}
