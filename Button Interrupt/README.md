# Button Interrupt
Using a timer, interrupts, and buttons to blink an LED

## How it works
An interrupt is enabled to read when a button is pressed and that will toggle an LED. Otherwise the processor is in low power mode.

## Where does it work
This code was written for the MSP430G2553 and the MSP430F5529. The difference between the code for these two boards was the pin for the button. (1.1 for the F5529 and 1.3 for the G2553).
