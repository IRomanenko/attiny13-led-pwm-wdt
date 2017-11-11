// Attiny13A
#define F_CPU 9690000

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "wdt-api.h"
#include "pwm-api.h"

int State = 0;

ISR (WDT_vect) {

    if (State != 6) {
        deInitializeTimer0PWM();
        stopTimer0PWM();
        PORTB &= ~(1<<PB0);
    }

    switch (State) {

        case 1: {
            initializeTimer0PWM();
            setTimer0PWMOutput(50);
            startTimer0PWM();
            break;
        }

        case 3: {
            initializeTimer0PWM();
            setTimer0PWMOutput(125);
            startTimer0PWM();
            break;
        }

        case 5: {
            initializeTimer0PWM();
            setTimer0PWMOutput(255);
            startTimer0PWM();
            break;
        }

        case 6: {
            softLightOff();
            break;
        }

        case 7: {
            PORTB &= ~(1<<PB0);
            State = 0;
            break;
        }

    }

    State += 1;

    if (State >= 7) {
        PORTB &= ~(1<<PB0);
        State = 0;
    }

    WDTCR |= _BV(WDTIE);
}


void softLightOff(void) {

    int CurrentWidth = 255;
    int Step         = 10;
    int DelayA       = 20;

    for (int i = 0; i < 25; i++) {
        CurrentWidth = CurrentWidth - Step;
        setTimer0PWMOutput(CurrentWidth);
        _delay_ms(DelayA);
    }

}

int main(void) {

    DDRB  = 0xFF;

    // Power management
    ADCSRA &= ~(1<<ADEN); // turn off ADC
    ACSR |= _BV(ACD);     // disable analog comparator

    // WDT initialization
    initWDT();

    sei();

    PORTB &= ~(1<<PB0);

    while(1) {

        sleep_enable();
        sleep_cpu();

    }

}
