/**
 * @authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: All about the collisions
 * Language:  C
 * Date : april 2017
 */

#include "collision.h"
#include "random.h"

/**
 * Check if an object touch the border
 * @param obj ball or ghost
 * @param ghost if obj is a ghost
 */
void check_border(object_t *obj, bool ghost) {
	bool top = false;
	bool bottom = false;
	bool right = false;
	bool left = false;

	if (obj->x - obj->radius <= STEP && (obj->dir & WEST) == WEST) {
		left = true;
	}

	if (obj->x + obj->radius > MAX_POS_X - STEP  && (obj->dir & EAST) == EAST) {
		right = true;
	}

	if (obj->y - obj->radius <= STEP && (obj->dir & NORTH) == NORTH) {
		top = true;
	}

	if (obj->y + obj->radius > (ghost ? GHOST_MAX_Y : MAX_POS_Y) - STEP && (obj->dir & SOUTH) == SOUTH) {
		bottom = true;
	}

	if(top || bottom || left || right){
		if(!ghost && (top || bottom)){
			inverse_dir_bottom_top(obj, false);
		}else{
			inverse_dir(obj);
		}

	}
}

/**
 * Move an object
 * @param obj ball, ghost
 */
void move(object_t *obj) {
	switch (obj->dir) {
	case NORTH:
		obj->y -= STEP;
		break;
	case SOUTH:
		obj->y += STEP;
		break;
	case EAST:
		obj->x += STEP;
		break;
	case WEST:
		obj->x -= STEP;
		break;
	case NORTH + EAST:
		obj->x += STEP;
		obj->y -= STEP;
		break;
	case NORTH + WEST:
		obj->x -= STEP;
		obj->y -= STEP;
		break;
	case SOUTH + EAST:
		obj->x += STEP;
		obj->y += STEP;
		break;
	case SOUTH + WEST:
		obj->x -= STEP;
		obj->y += STEP;
		break;
	default:
		break;
	}
}

/**
 * Inverse the classic direction of object
 * @param obj ball or ghost
 */
void inverse_dir(object_t *obj) {
	switch (obj->dir) {
	case NORTH:
		obj->dir = SOUTH;
		break;
	case SOUTH:
		obj->dir = NORTH;
		break;
	case EAST:
		obj->dir = WEST;
		break;
	case WEST:
		obj->dir = EAST;
		break;
	case NORTH + EAST:
		obj->dir = NORTH + WEST;
		break;
	case NORTH + WEST:
		obj->dir = NORTH + EAST;
		break;
	case SOUTH + EAST:
		obj->dir = SOUTH + WEST;
		break;
	case SOUTH + WEST:
		obj->dir = SOUTH + EAST;
		break;
	}
}

/**
 * Inverse direction if the border top or bottom is touch
 * @param obj ball or ghost
 * @param ghost if obj is a ghost
 */
void inverse_dir_bottom_top(object_t *obj, bool ghost) {
	int random = randBetween(0, 2);
	if(!ghost){
		random = 1;
	}

	if (random) {
		switch (obj->dir) {
		case NORTH + EAST:
			obj->dir = SOUTH + EAST;
			break;
		case NORTH + WEST:
			obj->dir = SOUTH + WEST;
			break;
		case SOUTH + EAST:
			obj->dir = NORTH + EAST;
			break;
		case SOUTH + WEST:
			obj->dir = NORTH + WEST;
			break;
		default:
			break;
		}
	} else {
		switch (obj->dir) {
		case NORTH + EAST:
			obj->dir = NORTH + WEST;
			break;
		case NORTH + WEST:
			obj->dir = NORTH + EAST;
			break;
		case SOUTH + EAST:
			obj->dir = SOUTH + WEST;
			break;
		case SOUTH + WEST:
			obj->dir = SOUTH + EAST;
			break;
		default:
			break;
		}
	}
}

/* The function looks at the collision only in the direction taken by the object referenced as "object_id".
 * It detects all collisions among all objects indexes between min_idx and max_idx (skipping object_id itself).
 * If the distance (D) with an object is lower than |x2-x1|<radius1+radius2+STEP and |y2-y1|<radius1+radius2+STEP,
 * the collision is detected.
 * Parameters:
 * 		object_id: index of the moving object trying to detect a collision
 * 		obj_array: array of all objects
 * 		min_idx:   lower index of the object to test for collision
 * 		max_idx:   higher index of the object to test for collision
 * Return: index of the object provoking the collision or NO_COLLISION
 */
int test_collision(int object_id, object_t *obj_array, int min_idx, int max_idx) {
	int i, dx, dy, dx_col, dy_col, col;

	for (i = min_idx; i <= max_idx; i++) // search only collisions with ghosts (never with ball)
		if (i != object_id && object[i].active) {
			dx_col = obj_array[object_id].radius + obj_array[i].radius + STEP;
			dy_col = obj_array[object_id].radius + obj_array[i].radius + STEP;
			dx = obj_array[object_id].x - obj_array[i].x;
			dy = obj_array[object_id].y - obj_array[i].y;
			if (ABS(dx) <= dx_col && ABS(dy) <= dy_col) {
				col = NO_COLLISION;
				if (dx > 0)
					col |= WEST;
				else if (dx < 0)
					col |= EAST;
				if (dy > 0)
					col |= NORTH;
				else if (dy < 0)
					col |= SOUTH;
				if (col & obj_array[object_id].dir)	// collision tested only in the object direction
					return i;// return (one of) the ID of the object creating the collision
			}
		}
	return NO_COLLISION;
}
