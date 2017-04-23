/**
 * @authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: manage paddle in the game
 * Language:  C
 * Date : april 2017
 */

#include "define.h"

/**
 * Initialize the paddle
 */
void init_paddle() {
	paddle.lenght = 30;
	paddle.width = 4;
	paddle.x = 110;
	paddle.y = 299;
	paddle.dir = 0;

	lcd_filled_rectangle(paddle.x, paddle.y, paddle.x + paddle.lenght,
			paddle.y + paddle.width, LCD_WHITE);
}

/**
 * Test if the paddle touch the left border
 * @param object paddle
 * @return bool
 */
bool in_border_left(paddle_t *object) {
	if (object->x < (0 + STEP)) {
		return true;
	} else {
		return false;
	}
}

/**
 * Test if the paddle touch the right border
 * @param object paddle
 * @return bool
 */
bool in_border_right(paddle_t *object) {
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

/**
 * Manage the direction for the joystick
 */
void direction_joystick() {
	if (joystick_get_state(JOYSTICK_LEFT)) {
		if (in_border_left(&paddle)) {
			paddle.dir = 0;
		} else {
			paddle.dir = WEST;
		}
		paddle.active = true;
	} else {
		paddle.dir = 0;
		paddle.active = false;
	}

	if (joystick_get_state(JOYSTICK_RIGHT)) {
		if (in_border_right(&paddle)) {
			paddle.dir = 0;
		} else {
			paddle.dir = EAST;
		}
		paddle.active = true;
	} else if (paddle.active == false) {
		paddle.dir = 0;
	}
}

/**
 * Move the paddle
 * @param obj paddle
 */
void paddle_move(paddle_t *obj) {
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

/**
 * Routine of the paddle(task call from the main)
 * @param params
 */
void paddle_routine(void *params) {
	while (1) {
		vTaskDelay(8 / portTICK_RATE_MS);
		direction_joystick();
		switch (paddle.dir) {
			case WEST:
				lcd_filled_rectangle(paddle.x + paddle.lenght - STEP, paddle.y,
						paddle.x + paddle.lenght, paddle.y + paddle.width,
						LCD_BLACK);
				break;
			case EAST:
				lcd_filled_rectangle(paddle.x, paddle.y, paddle.x + STEP,
						paddle.y + paddle.width, LCD_BLACK);
				break;
			default:
				break;
		}
		paddle_move(&paddle);
		lcd_filled_rectangle(paddle.x, paddle.y, paddle.x + paddle.lenght,
				paddle.y + paddle.width, LCD_WHITE);
	}
}

