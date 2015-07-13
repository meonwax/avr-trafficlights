#ifndef TRAFFICLIGHTS_H
#define TRAFFICLIGHTS_H

#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

int button_is_pressed();
void clear();
void standard_lights();
void yellow_blink();
void party();
void chase_down();
void ping_pong_chase();
int main(void);

#endif /* TRAFFICLIGHTS_H */
