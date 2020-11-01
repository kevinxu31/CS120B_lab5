/*	Author: lab
 *  Partner(s) Name: Luofeng Xu
 *	Lab Section:022
 *	Assignment: Lab 5  Exercise 1
 *	Exercise Description: https://youtu.be/PHmHVftlMxk
 *			https://drive.google.com/file/d/1WvqQ7lbTlFIgzmqdjDsyn5qf73XiwDzb/view?usp=sharing
 *			I've been testing this video by myself and it works well, if it's not working for you, please ask me to upload again.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRA=0x00;PORTA=0xFF;
	DDRC=0xFF;PORTC=0x00;
	unsigned char fuel=0x00;
	unsigned char c=0x00;
	while (1) {
		fuel=~PINA&0x0F;
		if (fuel==0){
			c=0x40;
		}
		else if(fuel>0 && fuel<=2){
			c=0x60;
		}
		else if(fuel>2 && fuel<=4){
			c=0x70;
		}
		else if(fuel>4 && fuel<=6){
                	c=0x38;
                }
		else if(fuel>6 && fuel<=9){
                	c=0x3c;
                }
		else if(fuel>9 && fuel<=12){
                	c=0x3e;
                }
		else if(fuel>12 && fuel<=15){
                	c=0x3f;
                }
		PORTC=c;
	}
	return 1;
}
