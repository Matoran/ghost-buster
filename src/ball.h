#ifndef BALL_H_
#define BALL_H_

#include "define.h"

void check_ball_vs_ghost(object_t *ball);
void init_ball(object_t *ball);
void check_ball_vs_paddle(object_t *ball);
void ball_routine(void *params);

#endif /* BALL_H_ */
