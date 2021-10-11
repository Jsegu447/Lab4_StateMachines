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
enum SM2_STATES{SM2_START,SM2_INCREASE,SM2_DECREASE, SM2_WAIT,SM2_RESET} State;


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;
	DDRC = 0xFF; PORTC = 0x07;
    /* Insert your solution below */
	State = SM2_START;
    while (1){  
	switch(State){
	case SM2_START:
	State = SM2_WAIT;
	break;
	
	case SM2_WAIT:
	if((PINA & 0x01) == 0x01 && (PINA & 0x02) == 0x02){
		State = SM2_RESET;
	}  
	else if((PINA & 0x01) == 0x01){
		State = SM2_INCREASE;
	}
	else if((PINA & 0x02) == 0x02){
		State = SM2_DECREASE;
	}
	else{
	State = SM2_WAIT;
	}
	break;
	
	case SM2_INCREASE:
	 if((PINA & 0x01) == 0x01 && (PINA & 0x02) == 0x02){
                State = SM2_RESET;
        }
        else if((PINA & 0x01) == 0x01){
                State = SM2_INCREASE;
        }
        else if((PINA & 0x02) == 0x02){
                State = SM2_DECREASE;
        }
        else{
        State = SM2_WAIT;
        }
	break;
	
	case SM2_DECREASE:
	 if((PINA & 0x01) == 0x01 && (PINA & 0x02) == 0x02){
                State = SM2_RESET;
        }
        else if((PINA & 0x01) == 0x01){
                State = SM2_INCREASE;
        }
        else if((PINA & 0x02) == 0x02){
                State = SM2_DECREASE;
        }
        else{
        State = SM2_WAIT;
        }
	break;
	
	case SM2_RESET:
	 if((PINA & 0x01) == 0x01 && (PINA & 0x02) == 0x02){
                State = SM2_RESET;
        }
        else if((PINA & 0x01) == 0x01){
                State = SM2_INCREASE;
        }
        else if((PINA & 0x02) == 0x02){
                State = SM2_DECREASE;
        }
        else{
        State = SM2_WAIT;
        }
	break;
	
	default:
	State = SM2_START;
	}

	switch(State){
	case SM2_START:
	PORTC = 0x07;
	break;
	
	case SM2_WAIT:
	break;
	
	case SM2_INCREASE:
	if(PINC < 9){
	PORTC = PINC+ 1;
	}		
	break;

	case SM2_DECREASE:
	PORTC = PINC - 1;
	break;
	
	case SM2_RESET:
	PORTC = 0x00;
	break;
	}		     
    }
    return 1;
}
