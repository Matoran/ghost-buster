/*
 * define.h
 *
 *  Created on: 5 avr. 2017
 *      Author: gaetan
 */

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
#define STEP         2			// moving step for all objects

#define MaxPosX		 239  //240-1 start count at 0
#define MaxPosY		 319  //320-1 start count at 0
#define JLeft		 23
#define JRight		 21

#define MAXPOSX 239 //240-1 start count at 0
#define MAXPOSY 300 //320-1 start count at 0
#define STARTPOSX 239
#define STARTPOSY 299


// Direction vector. Note that only 8 directions are possible,
// since NORTH|SOUTH is nonsense for example.
enum {
	NORTH = 1, EAST = 2, SOUTH = 4, WEST = 8
};

typedef struct {
	int x;
	int y;
	int lenght;
	int width;
	int dir;
	bool active;
} raquet_t;

#endif /* DEFINE_H_ */
