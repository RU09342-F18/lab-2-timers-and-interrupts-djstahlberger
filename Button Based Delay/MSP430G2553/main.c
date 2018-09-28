#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	BCSCTL3 = LFXT1S_2; //Allows G2 to use internal crystal
	
	P1DIR |= BIT0; //Sets direction of P1.0 to output

	P1OUT |= BIT3; //Sets pull-down resistor
	P1DIR &= ~BIT3; //Sets direction of P1.3 to input
	P1REN |= BIT3; //Enables the pull up/down resistor
	P1OUT |= BIT3; //Sets it to pull down

	TACTL = TASSEL_1 | MC_1 | ID_2; //Enables ACLCK, sets up mode, sets internal divider to 4
	CCTL0 = CCIE; //Interrupt Enable
	TACCR0 = 200; //sets register 200
	P1IE |= BIT3; //enables button interrupt
	P1IES |= BIT3; //sets interrupt to trigger on rising edge
	P1IFG &= ~BIT3; //clears interrupt flag

    // Enter LPM0 and enable global interrupts
	_BIS_SR(LPM0_bits + GIE);
	return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){
    if(P1IES & BIT3){ //if FALLING edge is detected
        TACTL = TASSEL_1 | MC_2 | ID_2 | TACLR; //Enables ACLCK, sets continuous mode, sets internal divider to 4, CLEARS TIMER
        P1IES &= ~BIT3; //sets interrupt to rising edge
    }
    else{
        TACTL = TASSEL_1 | MC_1 | ID_2; //Enables ACLCK, sets up mode, sets internal divider to 4
        P1IES |= BIT3; //sets interrupt to detect falling edge
        CCR0 = TAR;//sets ccr equal to clck register
    }
    P1IFG &= ~BIT3; //Clears interrupt
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0(void){
    //toggle LED 1.0
    P1OUT ^= BIT0;
}






