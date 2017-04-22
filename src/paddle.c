/*
 * raquet.c

 *
 *  Created on: 5 avr. 2017
 *      Author: gaetan
 */
#include "define.h"

void init_paddle() {
	raquet.lenght = 30;
	raquet.width = 4;
	raquet.x = 110;
	raquet.y = 299;
	raquet.dir = 0;

	lcd_filled_rectangle(raquet.x, raquet.y, raquet.x + raquet.lenght,
			raquet.y + raquet.width, LCD_WHITE);
}

bool in_border_left(raquet_t *object) {
	if (object->x < (0 + STEP)) {
		return true;
	} else {
		return false;
	}
}

bool in_border_right(raquet_t *object) {
	if ((object->x + object->lenght) >= MAX_POS_X - STEP) {
		return true;
	} else {
		return false;
	}
}

/***********************************
 * function     : JoystickGetState
 * arguments    : pos (from enum)
 * return value : int
 *   est 	= p1.21	 -> 2
 *   ouest 	= p1.23	 -> 4
 ***********************************/
bool joystick_get_state(uint8_t pos) {
	if (((LPC_GPIO1->FIOPIN >> pos) & 1) == 1) {
		return false;
	} else {
		return true;
	}
}
void direction_joystick() {
	if (joystick_get_state(JOYSTICK_LEFT)) {
		if (in_border_left(&raquet)) {
			raquet.dir = 0;
		} else {
			raquet.dir = WEST;
		}
		raquet.active = true;
	} else {
		raquet.dir = 0;
		raquet.active = false;
	}

	if (joystick_get_state(JOYSTICK_RIGHT)) {
		if (in_border_right(&raquet)) {
			raquet.dir = 0;
		} else {
			raquet.dir = EAST;
		}
		raquet.active = true;
	} else if (raquet.active == false) {
		raquet.dir = 0;
	}
}

void paddle_move(raquet_t *obj) {
	switch (obj->dir) {
	case EAST:
		obj->x += STEP;
		break;
	case WEST:
		obj->x -= STEP;
		break;
	default:
		break;
	}
}

void paddle_routine(void *params) {
	while (1) {
		vTaskDelay(8 / portTICK_RATE_MS);
		direction_joystick();
		switch (raquet.dir) {
			case WEST:
				lcd_filled_rectangle(raquet.x + raquet.lenght - STEP, raquet.y,
						raquet.x + raquet.lenght, raquet.y + raquet.width,
						LCD_BLACK);
				break;
			case EAST:
				lcd_filled_rectangle(raquet.x, raquet.y, raquet.x + STEP,
						raquet.y + raquet.width, LCD_BLACK);
				break;
			default:
				break;
		}
		paddle_move(&raquet);
		lcd_filled_rectangle(raquet.x, raquet.y, raquet.x + raquet.lenght,
				raquet.y + raquet.width, LCD_WHITE);
	}
}

