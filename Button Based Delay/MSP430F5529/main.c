#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5; //Unlocks GPIO pins

    P1DIR |= BIT0; //Sets direction of P1.0 to output

    P1OUT |= BIT1; //Sets pull-down resistor
    P1DIR &= ~BIT1; //Sets direction of P1.1 to input
    P1REN |= BIT1; //Enables the pull up/down resistor
    P1OUT |= BIT1; //Sets it to pull down

    //Timer B setup
    TB0CTL = TBSSEL_1 | MC_1 | ID_2; //Enables ACLCK, sets up mode, sets internal divider to 4
    TB0CCTL0 = CCIE; //Interrupt Enable
    TB0CCR0 = 200; //sets register 200
    P1IE |= BIT1; //enables button interrupt
    P1IES |= BIT1; //sets interrupt to trigger on rising edge
    P1IFG &= ~BIT1; //clears interrupt flag

    // Enter LPM0 and enable global interrupts
    _BIS_SR(LPM0_bits + GIE);
    return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){
    if(P1IES & BIT1){ //if FALLING edge is detected
        TB0CTL = TBSSEL_1 | MC_2 | ID_2 | TBCLR; //Enables ACLCK, sets continuous mode, sets internal divider to 4, CLEARS TIMER
        P1IES &= ~BIT1; //sets interrupt to falling edge
    }
    else{
        TB0CTL = TBSSEL_1 |  MC_1 | ID_2; //Enables ACLCK, sets up mode, sets internal divider to 4
        P1IES |= BIT1; //sets interrupt to detect falling edge
        TB0CCR0 = TBR;//sets ccr equal to clck register
    }
    P1IFG &= ~BIT1; //Clears interrupt
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void TIMER0_B0(void){
    //toggle LED 1.0
    P1OUT ^= BIT0;
}
