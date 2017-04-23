#ifndef DEFINE_H_
#define DEFINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <cr_section_macros.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "lcd.h"
#include "fonts.h"
#include "traces_ref.h"
#include "custom_rand.h"

#define NO_COLLISION 0
#define GHOST_NB     5
#define STEP         2
#define NB_LIVES	 3
#define RADIUS_BALL	 3

#define JOYSTICK_LEFT	 23
#define JOYSTICK_RIGHT	 21
#define JOYSTICK_CENTER	 19

#define MAX_POS_X 239
#define MAX_POS_Y 299
#define GHOST_MAX_Y 270
#define START_POS_X 120
#define START_POS_Y 299


// Direction vector. Note that only 8 directions are possible,
// since NORTH|SOUTH is nonsense for example.
enum {
	NORTH = 1,
	EAST = 2,
	SOUTH = 4,
	WEST = 8
};

// structure for the paddle
typedef struct {
	int x;
	int y;
	int lenght;
	int width;
	int dir;
	bool active;
} paddle_t;

paddle_t paddle;

// structure containing object position, size and direction
typedef struct {
	int x;
	int y;
	int radius;
	int dir;
	bool active;
} object_t;

// object instances:  object[0] is the ball, the other objects are the ghosts
extern object_t object[GHOST_NB + 1];

extern int score;
extern int lives;


// pointers on the ghosts bitmaps. 2 images by ghost_routine direction.
extern __DATA(RAM2) uint16_t *ghost_im_left[2], *ghost_im_right[2],
		*ghost_im_center[2];
extern uint16_t ghost_width, ghost_height;

#endif /* DEFINE_H_ */
