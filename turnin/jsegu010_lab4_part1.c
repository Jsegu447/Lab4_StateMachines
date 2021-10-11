/*	Author: jsegu010
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum SM1_STATES{SM1_START, SM1_RELEASEONB0, SM1_RELEASEONB1, SM1_PRESSONB0,SM1_PRESSONB1} State;


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	State = SM1_START;
    while (1) {
	switch(State){
        
	case SM1_START:
        State = SM1_RELEASEONB0;
        break;
        
	case SM1_RELEASEONB0:
        if((PINA&0x01) == 0x01){ State = SM1_PRESSONB1;} 
	else if((PINA&0x01) == 0x00){ State = SM1_RELEASEONB0;}
	break;
	
	case SM1_PRESSONB1:
	if((PINA&0x01) == 0x01){ State = SM1_PRESSONB1;}
        else if((PINA&0x01) == 0x00){ State = SM1_RELEASEONB1;}
	break;

	case SM1_RELEASEONB1:
	if((PINA&0x01) == 0x01){ State = SM1_PRESSONB0;}
        else if((PINA&0x01) == 0x00){ State = SM1_RELEASEONB1;}
        break;
	
	case SM1_PRESSONB0:
        if((PINA&0x01) == 0x01){ State = SM1_PRESSONB0;}
        else if((PINA&0x01) == 0x00){ State = SM1_RELEASEONB0;}
        break;

	default:
	State = SM1_START;
	break;
	}
	
	switch(State){
	
	case SM1_START:
        PORTB =0x01;
        break;

        case SM1_RELEASEONB0:
        PORTB = 0x01;
        break;

        case SM1_PRESSONB1:
        PORTB = 0x02;
        break;

        case SM1_RELEASEONB1:
        PORTB = 0x02;
        break;

        case SM1_PRESSONB0:
        PORTB = 0x01;
        break;
	}

        
    }
    return 1;
}
