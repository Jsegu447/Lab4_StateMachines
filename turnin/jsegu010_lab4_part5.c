/*	Author: jsegu010
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum STATES{START,WAITP,WAITR,WAITY,WAITRY,UNLOCK,RELOCK} State;


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	State = START;
    while (1){
	switch(State){
		case START:
		State = WAITP;
		PORTB = 0x00;
		break;
		
		case WAITP:
		if((PINA & 0x07) == 0x04){
			State = WAITR;		
	  	}
		else{
		State = START;
		}
		break;

		case WAITR:
		if((PINA & 0x07) == 0x04){
			State = WAITR;
		}
		else if((PINA & 0x07) == 0x00){
			State = WAITY;
		}
		
		else{
		State = START;	
		}
		break;

		case WAITY:
		if((PINA & 0x07) == 0x02){
		State = WAITRY;
		}
		else if((PINA & 0x07) == 0x00){
		State = WAITY;
		}
		else{
		State = START;
		}
		break;
		
		case WAITRY:
		State = UNLOCK;
		break;
		
		case UNLOCK:
		PORTB = 0x01;
		if((PINA & 0x80) == 0x80){
		 State = START;
		} 
		else if((PINA & 0x07) == 0x04){
		State = RELOCK;
		}  
		else{
		State = UNLOCK;
		}
		break;	
		
		case RELOCK:
		if((PINA & 0x80) == 0x80){
		State = START;
		}
                else if((PINA & 0x07) == 0x04){
                        State = RELOCK;
                }
                else if((PINA & 0x07) == 0x00){
                        State = RELOCK;
                }
		else if((PINA & 0x07) == 0x02){
		State = START;
		}
                else{
                State = UNLOCK;
                }
                break;
		
	}	
    }
    return 1;
}
