/*	Author: lab
 *  Partner(s) Name: Luofeng Xu
 *	Lab Section:022
 *	Assignment: Lab 5  Exercise 3
 *	Exercise Description: https://youtu.be/tZuoUupL_Sk
 *			https://drive.google.com/file/d/1C6jI-6XVLz2RI8NBBrVWyaDQSIwbk3DT/view?usp=sharing
 *			
 *			I've been testing this video by myself and it works well, if it's not working for you, please ask me to upload again.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States{Start,RA,PA}state;
unsigned char A0;
unsigned char B;
unsigned char flag;
void Tick(){
	switch(state){
		case Start:
			B=0x00;
			state=RA;
			break;
		case RA:
			if(!A0){state=RA;}
			else if(A0){
				if(flag<6){
					B=(~(0x3E<<flag)&0x3F);
				}
				else if((flag>=6&&flag<11)||(flag>=18&&flag<22)){
					B=~B;
				}
				else if(flag>=11){
					B=(0x3F>>(flag-11))&0x3F;
				}
				state=PA;
				flag++;

			}
			break;
		case PA:
			if(A0){
				state=PA;
			}
			else if(!A0){
				state=RA;
			}
			if (flag==22){flag=0;}

			break;
		default:
			break;
	}
}

int main(void) {
	DDRA=0x00;PORTA=0xFF;
	DDRB=0xFF;PORTB=0x00;
	state=Start;
	flag=0;
	while (1) {
		A0=~PINA&0x01;
		Tick();
		PORTB=B;
		
	}
	return 1;
}
