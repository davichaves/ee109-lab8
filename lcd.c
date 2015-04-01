/********************************************
*
*  Name: Davi Rodrigues Chaves
*  Section: W 3:30-5:00 PM
*  Assignment: Lab 8 - Rotary Encoders
*
********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void writenibble(unsigned char);

/*
  init_lcd - Do various things to initialize the LCD display
*/
void init_lcd() {
  _delay_ms(15);              // Delay at least 15ms

  PORTB &= ~(1 << PB0); // Clear R to 0
  writenibble(0b00110000);
  // Use writenibble to send 0011

  _delay_ms(5);               // Delay at least 4msec

  writenibble(0b00110000);
  // Use writenibble to send 0011

  _delay_us(120);             // Delay at least 100usec

  writenibble(0b00110000);
  // Use writenibble to send 0011

  writenibble(0b00100000);
  // Use writenibble to send 0010    // Function Set: 4-bit interface

  _delay_ms(2);

  writecommand(0x28);         // Function Set: 4-bit interface, 2 lines

  writecommand(0x0F);         // Display and cursor on
}

/*
  stringout - Print the contents of the character string "str"
  at the current cursor position.
*/
void stringout(char *str) {
	int i = 0;
	while(str[i] != '\0') {
		writedata(str[i]);
		i+=1;
	}
}

/*
  moveto - Move the cursor to the postion "pos"
*/

void moveto(unsigned char pos) {
	if (pos < 16) {
		writecommand(0x80 + pos);
	} else {
		writecommand(0xC0 + pos-16);
	}
}

/*
  writecommand - Output a byte to the LCD display instruction register.
*/
void writecommand(unsigned char x) {
	PORTB &= ~(1 << PB0); // Clear R to 0
	writenibble(x);
	writenibble(x << 4);
  _delay_ms(2);
}

/*
  writedata - Output a byte to the LCD display data register
*/
void writedata(unsigned char x) {
	PORTB |= (1 << PB0); // Clear R to 1
	writenibble(x);
	writenibble(x << 4);
  _delay_ms(2);
}

/*
  writenibble - Output four bits from "x" to the display
*/
void writenibble(unsigned char x) {
   PORTD &= 0x0F;
   PORTD |= (x & 0xF0);
   PORTB &= ~(1 << PB1); // Clear E to 0
   PORTB |= (1 << PB1); // Set E to 1
   PORTB |= (1 << PB1); // Set E to 1
   PORTB &= ~(1 << PB1); // Clear E to 0
}