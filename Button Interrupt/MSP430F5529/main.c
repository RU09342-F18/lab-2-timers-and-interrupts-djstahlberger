#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1SEL &= 0; //sets pin function to I/O

    P1DIR |= BIT0; //Sets P1.0 to output

    P1DIR &= ~BIT1; //Sets P1.1 to input
    P1REN |= BIT1; //Enables the pull up-down resistor
    P1OUT |= BIT1; //Eets the pull down resistor

    P1IE |= BIT1; //Enables the interupt for P1.1
    P1IES |= BIT1; //Enables rising edge for P1.3
    P1IFG &= ~BIT1; //Clears the flag

    // Enter LPM0 and enable global interrupts
    _BIS_SR(LPM0_bits + GIE);
    return 0;
}
    #pragma vector = PORT1_VECTOR;
    __interrupt void Port_1(void)
    {
        P1OUT ^= BIT0; //Toggles LED
        P1IFG &= ~BIT1; //Clears interrupt flag
    }

