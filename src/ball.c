/**
 * @authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: manage ball in the game
 * Language:  C
 * Date : april 2017
 */

#include "ball.h"
#include "paddle.h"
#include "collision.h"
#include "random.h"

/**
 * Check if the ball touch a ghost
 * @param ball
 */
void check_ball_vs_ghost(object_t *ball) {
	int dx, dy, dx_col, dy_col;

	for (int i = 1; i <= GHOST_NB; i++) {
		if (object[i].active) {
			dx_col = ball->radius + object[i].radius + STEP;
			dy_col = ball->radius + object[i].radius + STEP;
			dx = ball->x - object[i].x;
			dy = ball->y - object[i].y;

			if (ABS(dx) <= dx_col && ABS(dy) <= dy_col) {
				score++;
				lcd_print(190, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d",
						score);
				if (ball->dir != NORTH && ball->dir != SOUTH
						&& ball->dir != WEST && ball->dir != EAST) {
					inverse_dir_bottom_top(ball, true);
				} else {
					inverse_dir(ball);
				}
				lcd_filled_rectangle(object[i].x - object[i].radius,
						object[i].y - object[i].radius,
						object[i].x + object[i].radius,
						object[i].y + object[i].radius, LCD_BLACK);
				object[i].active = false;
			}
		}
	}
}

/**
 * Test if the ball is outside the paddle
 * @param ball
 */
void check_ball_vs_paddle(object_t *ball) {
	if (ball->y + ball->radius >= MAX_POS_Y - STEP) {
		if ((ball->x - ball->radius > paddle.x + paddle.lenght + STEP
				|| ball->x + ball->radius < paddle.x - STEP)
				&& (ball->dir & SOUTH) == SOUTH) {
			if (lives > 1) {
				lives--;
				lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d",
						lives);
				//ball->x = paddle.x + paddle.lenght/2;
				//ball->y = MAX_POS_Y - ball->radius - STEP;
				ball->x = START_POS_X - ball->radius - STEP;
				ball->y = START_POS_Y - ball->radius - STEP;
				ball->dir = NORTH + EAST;

			} else {
				lives--;
				lcd_circle(ball->x, ball->y, ball->radius, LCD_BLACK);
				lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d",
						lives);
				lcd_print(30, 280, SMALLFONT, LCD_WHITE, LCD_BLACK,
						"Press joystick to start");
			}
			ball->active = false;
		}
	}
}

/**
 * Routine of the ball(task call from the main)
 * @param params
 */
void ball_routine(void *params) {
	object_t *ball = &object[0];
	int dead[GHOST_NB];
	for (int i = 0; i < GHOST_NB; i++) {
		dead[i] = 0;
	}
	portTickType xLastWakeTime = xTaskGetTickCount();
	int countWait = 0;
	bool clicked = false;
	while (1) {
		vTaskDelayUntil(&xLastWakeTime, 10 / portTICK_RATE_MS);
		if (joystick_get_state(JOYSTICK_CENTER)) {
			clicked = true;
		} else if (clicked) {
			lcd_print(30, 280, SMALLFONT, LCD_BLACK, LCD_BLACK,
					"Press joystick to start");
			lcd_circle(object[0].x, object[0].y, object[0].radius, LCD_BLACK);
			score = 0;
			lives = NB_LIVES;
			init_ball(&object[0]);
			lcd_filled_rectangle(190, 305, MAX_POS_X, 319, LCD_BLACK);
			lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", lives);
			lcd_print(190, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", score);
			for (int i = 1; i <= GHOST_NB; i++) {
				object[i].active = true;
			}
			clicked = false;
		}

		if (ball->active) {
			lcd_circle(ball->x, ball->y, ball->radius, LCD_BLACK);//efface la balle
			check_ball_vs_paddle(ball);

			check_ball_vs_ghost(ball);

			check_border(ball, false);
			if (ball->active) {
				move(ball);
				lcd_circle(ball->x, ball->y, ball->radius, LCD_BLUE);//affiche la balle
			}
		} else if (lives > 0) {
			countWait++;
			if (countWait >= 100) {
				countWait = 0;
				ball->active = true;
			}
		}
		for (int i = 1; i <= GHOST_NB; i++) {
			if (!object[i].active) {
				dead[i - 1]++;
				if (dead[i - 1] == 2) {
					if (randBetween(1, 100) == 1) {
						object[i].active = true;
					}
					dead[i - 1] = 0;
				}
			}

		}
	}
}

/**
 * Initialize the ball
 * @param ball
 */
void init_ball(object_t *ball) {
	ball->radius = RADIUS_BALL;
	ball->x = START_POS_X - ball->radius - STEP;
	ball->y = START_POS_Y - ball->radius - STEP;
	ball->dir = NORTH + EAST;
	ball->active = true;
}
