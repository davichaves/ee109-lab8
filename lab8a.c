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

char state; // 1 = stopped | 2 = started | 3 = Lapped
char time[3];

void init_ports(void);
void init_adc(void);
void init_timer1(unsigned short m);

void setTimerToZero(void);
void printTime(void);

int main(void) {
  state = 1;
  sei(); // Enable interrupts
  init_ports();
  init_adc();
	init_lcd();
  init_timer1(5000);
  setTimerToZero();
  writecommand(1); //clear LCD
  printTime();
  int n;
  int myNumber = 0;

  /* Main programs goes here */

   while (1) {
      int prevVal = myNumber;
      ADCSRA |= (1 << ADSC); //start conversion
      while (ADCSRA & (1 << ADSC)); //wait for conversion
      int prevN = n;
      n = ADC;
      if (!((prevN < (n + 10)) && (prevN > (n - 10)))) {
         if(n < 390) {
            if (state == 2) {
               state = 1;
            } else {
               state = 2;
            }
            //up -------- START_STOP Button -----------------
         } else if(n < 600) {
            if (state == 1) {
               setTimerToZero();
               printTime();
            } else if (state == 2) {
               state = 3;
            } else {
               state = 2;
            }
            //down -------- LAP_RESET Button -----------------
         }
      }
      _delay_ms(10);
   } // Loop forever

  return 0;   /* never reached */
}

/*
  print time
*/

void printTime() {
   writedata(time[2]);
   writedata(time[1]);
   writedata('.');
   writedata(time[0]);
   moveto(0);
}

/*
  set timer to zero
*/

void setTimerToZero() {
   int i;
   for (i = 0; i < 3; i++) {
      time[i] = '0';
   }
}

/*
  interrupt
*/

ISR(TIMER1_COMPA_vect){
   // increments every 0.1s
  if (state != 1) { //if not stopped it will increment
    time[0] += 1;
    if (time[0] > '9') {
       time[0] = '0';
       time[1] += 1;
       if (time[1] > '9') {
          time[0] = '0';
          time[1] = '0';
          time[2] += 1;
          if (time[2] == '6') {
             setTimerToZero();
          }
       }
    }
  }
  if (state == 2) {
    printTime();
  }
}

/*
  init_timer - Do various things to initialize the ports
*/

void init_timer1(unsigned short m) {
   TCCR1B |= (1 << WGM12); // Set to CTC mode
   TIMSK1 |= (1 << OCIE1A); // Enable Timer Interrupt
   OCR1A = m; //prescalar=64 counting to 25000 = 0.1s w/ 16 MHz clock
   // and start counter
   TCCR1B |= (1 << CS12);
}

/*
  init_ports - Do various things to initialize the ports
*/

void init_ports() {
   DDRD |= 0xF0; //setting D4-D7 as outputs
   DDRB |= 0x03; //seeting B1-B2 as outputs
}

/*
  init_adc - Do various things to initialize the adc
*/
void init_adc() {
   ADMUX &= 0b00000000; //set all bits to zero
   ADMUX |= 0b01000000; // set 01 to reference, set 10-bit conv, set A0 
   ADCSRA &= 0b00000000; //set all bits to zero
   ADCSRA |= 0b10000100; //enable ADC, set divider to 4
}