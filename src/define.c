#include "define.h"

object_t object[GHOST_NB + 1];
int score = 0;
int lives = 0;
__DATA(RAM2) uint16_t *ghost_im_left[2], *ghost_im_right[2],
		*ghost_im_center[2];
uint16_t ghost_width, ghost_height;
