/*
 * collision.h
 *
 *  Created on: 5 avr. 2017
 *      Author: selement
 */

#ifndef COLLISION_H_
#define COLLISION_H_

void check_border(object_t *obj);
void move(object_t *obj);
void inverse_dir(object_t *obj);
void inverse_dir_bottom_top(object_t *obj);

#endif /* COLLISION_H_ */
