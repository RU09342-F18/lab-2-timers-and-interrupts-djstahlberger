# Button Based Delay
This code blinks an LED in correspondence with how long a button is held down. So if the button is pressed and released immediately the LED will blink faster than if the button was held down for, say, 5 seconds.

## How it works
Using a timer, capture compare registers, a button, and global interrupts this can be easily done. The timer is initially set to run in up mode and the interrupt is set up to detect the falling edge (or button press) of the input pin. Once this event occurs, the interrupt is set to detect the rising edge for when the button is released and the timer is reset and set to continuous mode to see how long the button is pressed for. Once the button is released the capture compare register is set to the value of the timer and the timer is once again reset and put into continuous mode. The interrupt flag is then reset.

## Where does this work
This code was made for the MSP430G2553 and the MSP430FR2311. The difference between the codes was the ports and the name of the timer. The G2 uses Timer A and the FR2311 uses the Timer B. For ports, the G2 uses 1.0 for the LED and 1.3 for the button. The FR2311 uses 1.0 for the output and 1.1 for the input.
