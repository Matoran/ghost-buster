#ifndef COLLISION_H_
#define COLLISION_H_

#include "define.h"
#include <stdbool.h>

void move(object_t *obj);
void inverse_dir(object_t *obj);
void inverse_dir_bottom_top(object_t *obj, bool ghost);
void check_border(object_t *obj, bool ghost);
int test_collision(int object_id, object_t *obj_array, int min_idx, int max_idx);

#endif
