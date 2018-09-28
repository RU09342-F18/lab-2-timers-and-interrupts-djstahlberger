# TIMER A Blink
Using a timer to replicate the multiple blink code from lab 1.

## How does it work

Using two timers in continuous mode(sweeping from 0x00000 to 0xFFFF) and two capture compare registers, two different LEDs can be toggled at different rates. This is achieved by setting up interrupts that trigger when the value in the timer register hits the same value in the capture control register. Then the capture control register gets set to a new value so it can blink

## Where does it work

This code was written for the MSP430G2553 and the MSP430F5529. The only differences in the code were the ports associated with the LEDS (1.0 and 4.7 for the F5529 and 1.0 and 1.6 for the G2553)
