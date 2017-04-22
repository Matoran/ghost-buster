/*
 * raquet.h
 *
 *  Created on: 5 avr. 2017
 *      Author: gaetan
 */

#ifndef RAQUET_H_
#define RAQUET_H_

// structure containing object position, size and direction
#include "define.h"


bool in_border_left(raquet_t *object);
bool in_border_right(raquet_t *object);
bool joystick_get_state(uint8_t pos);
void direction_joystick();
void paddle_move(raquet_t *obj);
void paddle_routine(void *params);
void init_paddle();

#endif /* RAQUET_H_ */
