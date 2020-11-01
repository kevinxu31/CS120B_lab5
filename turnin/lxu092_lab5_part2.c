/*	Author: lab
 *  Partner(s) Name: Luofeng Xu
 *	Lab Section:022
 *	Assignment: Lab 5  Exercise 2
 *	Exercise Description: https://youtu.be/MmZvrgk6O9Q
 *			https://drive.google.com/file/d/1RKT0o-CtLRRuzzcO0Urn-TANCOFwhjFK/view?usp=sharing
 *			I've been testing this video by myself and it works well, if it's not working for you, please ask me to upload again.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States{Start,RA,PA_0,PA_1,Reset}state;
unsigned char A0;
unsigned char A1;
unsigned char C;
void Tick(){
	switch(state){
		case Start:
			C=7;
			state=RA;
			break;
		case RA:
			if(A0&(!A1)){
				state=PA_0;
				if(C<9){C=C+1;}
			}
			else if(A0&A1){
				state=Reset;C=0;
			}
			else if((!A0)&A1){
				state=PA_1;
				if(C>0){C=C-1;}
			}
			else{state=RA;}
			break;
		case PA_0:
			if(A0&(!A1)){state=PA_0;}
			else if((!A0)&(!A1)){state=RA;}
			else if(A0&A1){state=Reset;C=0;}
			break;
                case PA_1:
                        if(A1&(!A0)){state=PA_1;}
                        else if((!A0)&(!A1)){state=RA;}
                        else if(A0&A1){state=Reset;C=0;}
                        break;
		case Reset:
			if(!A1&!A0){state=RA;}
			else{state=Reset;}
			break;
		default:
			break;
	}
}

int main(void) {
	DDRA=0x00;PORTA=0xFF;
	DDRC=0xFF;PORTC=0x00;
	state=Start;
	while (1) {

		A0=~PINA&0x01;
		A1=(~PINA>>1)&0x01;
		Tick();
		PORTC=C;
		
	}
	return 1;
}
