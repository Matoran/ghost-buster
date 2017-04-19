/*
 * ball.h
 *
 *  Created on: 5 avr. 2017
 *      Author: selement
 */

#ifndef BALL_H_
#define BALL_H_

#include "define.h"

void check_ball_vs_ghost(object_t *ball);
void init_ball(object_t *ball);
void check_ball_vs_racket(object_t *ball);
void ball_routine();

#endif /* BALL_H_ */
