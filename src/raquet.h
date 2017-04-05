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


bool inBorderLeft(raquet_t *object);
bool inBorderRight(raquet_t *object);
bool JoystickGetState(uint8_t pos);
void direction_joystick();
void raquet_move(raquet_t *obj);
void raquet_routine();

#endif /* RAQUET_H_ */
