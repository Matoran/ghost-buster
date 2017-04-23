#ifndef RAQUET_H_
#define RAQUET_H_

#include "define.h"


bool in_border_left(paddle_t *object);
bool in_border_right(paddle_t *object);
bool joystick_get_state(uint8_t pos);
void direction_joystick();
void paddle_move(paddle_t *obj);
void paddle_routine(void *params);
void init_paddle();

#endif /* RAQUET_H_ */
