#include <msp430.h> 


/**
 * main.c
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD; //stops watchdog timer
    // Pin setup
    P1SEL &= ~BIT0; // Set P1.0 as a digital input/output
    P4SEL &= ~BIT7; //Set P4.7 as a digital input/output
    P1DIR |= BIT0; // Set P1.0 as output
    P4DIR |= BIT7; // Set p4.7 as output

    // Timer setup
    TA0CTL = TASSEL_2 | ID_3 | MC_2;
    // CCR0 setup
    TA0CCR0 = 0x6000;
    TA0CCTL0 |= CCIE; //Enables interupt

    //Timer2 Setup
    TA1CTL = TASSEL_2 | ID_3 | MC_2;
    //CCR0 setup
    TA1CCR0 = 0X9000;
    TA1CCTL0 |= CCIE; //Interrupt enable

    // Enter LPM0 and enable global interrupts
    _BIS_SR(LPM0_bits + GIE);
}

// ISR
#pragma vector=TIMER0_A0_VECTOR;
__interrupt void Time0_A0_Vector(void) {
    //LED1.0 is toggled by timer0
    P1OUT ^= BIT0;
}

#pragma vector=TIMER1_A0_VECTOR;
__interrupt void Time1_A1_Vector(void){
    //LED4.7 is toggled by timer1
    P4OUT ^= BIT7;


}
