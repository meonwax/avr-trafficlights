/***********************************************
 *
 * Traffic lights controller for ATtiny13
 * Copyright 2015 meonwax
 *
 * Fuses should be programmed as
 *   low: 0x6a    high: 0xFF
 *
 * Some macros inspired by http://www.avrfreaks.net/forum/macros-ddr-and-port-pin-name
 */

#include "trafficlights.h"
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

#define WAIT_AND_CHECK(tenth_seconds)   for(int i=tenth_seconds; i > 0; i--) { if(button_is_pressed()) return; _delay_ms(100); }

#define configure_as_input(bit)         {DDRB &= ~(1 << bit);}
#define configure_as_output(bit)        {DDRB |= (1 << bit);}

#define pullup_on(bit)                  {PORTB |= (1 << bit);}
#define pullup_off(bit)                 {PORTB &= ~(1 << bit);}

#define set_high(bit)                   {PORTB |= (1 << bit);}
#define set_low(bit)                    {PORTB &= ~(1 << bit);}
#define toggle(bit)                     {PINB |= (1 << bit);}

#define RED                             PB4
#define YELLOW                          PB3
#define GREEN                           PB2
#define BUTTON                          PB0

int main(void) {
    DDRB  = 0xff; // whole PORTB as output
    configure_as_input(BUTTON);
    pullup_on(BUTTON);

    while(1) {
        standard_lights();
        clear();
        _delay_ms(1000);

        yellow_blink();
        clear();
        _delay_ms(1000);

        chase_down();
        clear();
        _delay_ms(1000);

        ping_pong_chase();
        clear();
        _delay_ms(1000);

        party();
        clear();
        _delay_ms(1000);
    }
    return 0;
}

/*
 * Lights out
 */
 void clear() {
    set_low(RED);
    set_low(YELLOW);
    set_low(GREEN);  
}

/*
 * Standard behaviour of traffic lights
 */
 void standard_lights() {
    while(1) {
        set_high(RED);
        WAIT_AND_CHECK(100);
        set_high(YELLOW);
        WAIT_AND_CHECK(15);
        set_low(RED);
        set_low(YELLOW);
        set_high(GREEN);
        WAIT_AND_CHECK(100);
        set_low(GREEN);
        set_high(YELLOW);
        WAIT_AND_CHECK(15);
        set_low(YELLOW);
    }
}

/*
 * Traffic lights in night mode
 */
 void yellow_blink() {
    while(1) {
        toggle(YELLOW);
        WAIT_AND_CHECK(8);
    }
}

/*
 * Party mode
 */
 void party() {
    set_high(RED);
    set_high(GREEN);
    while(1) {
        toggle(RED);
        WAIT_AND_CHECK(3);
        toggle(YELLOW);
        WAIT_AND_CHECK(3);
        toggle(GREEN);
        WAIT_AND_CHECK(3);
    }
}

void chase_down() {
    while(1) {
        set_high(RED);
        WAIT_AND_CHECK(3);
        set_low(RED);
        set_high(YELLOW);
        WAIT_AND_CHECK(3);
        set_low(YELLOW);
        set_high(GREEN);
        WAIT_AND_CHECK(3);
        set_low(GREEN);
    }
}

void ping_pong_chase() {
    while(1) {
        set_high(RED);
        WAIT_AND_CHECK(3);
        set_low(RED);
        set_high(YELLOW);
        WAIT_AND_CHECK(3);
        set_low(YELLOW);
        set_high(GREEN);
        WAIT_AND_CHECK(3);
        set_low(GREEN);
        set_high(YELLOW);
        WAIT_AND_CHECK(3);
        set_low(YELLOW);
    }
}

int button_is_pressed() {
    return !(PINB & (1 << BUTTON));
}
