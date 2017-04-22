#include "ball.h"
#include "paddle.h"
#include "collision.h"


void check_ball_vs_ghost(object_t *ball) {
	int dx, dy, dx_col, dy_col;

	for (int i = 1; i <= GHOST_NB; i++) {
		if(object[i].active){
			dx_col = ball->radius + object[i].radius + STEP;
			dy_col = ball->radius + object[i].radius + STEP;
			dx = ball->x - object[i].x;
			dy = ball->y - object[i].y;

			if (ABS(dx) <= dx_col && ABS(dy) <= dy_col) {
				score++;
				lcd_print(190, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", score);
				if (ball->dir != NORTH && ball->dir != SOUTH && ball->dir != WEST
						&& ball->dir != EAST) {
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

void check_ball_vs_racket(object_t *ball){
	if(ball->y + ball->radius >= MAX_POS_Y - STEP){
		if((ball->x - ball->radius > raquet.x + raquet.lenght + STEP || ball->x + ball->radius < raquet.x - STEP) && (ball->dir & SOUTH) == SOUTH){
			if(lives > 1){
				lives--;
				lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", lives);
				//ball->x = raquet.x + raquet.lenght/2;
				//ball->y = MAX_POS_Y - ball->radius - STEP;
				ball->x = START_POS_X - ball->radius - STEP;
				ball->y = START_POS_Y - ball->radius - STEP;
				ball->dir = NORTH + EAST;
				vTaskDelay(1000/portTICK_RATE_MS);
			}else{
				lives--;
				lcd_circle(ball->x, ball->y, ball->radius, LCD_BLACK);
				lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", lives);
				ball->active = false;
				lcd_print(30,280,SMALLFONT,LCD_WHITE,LCD_BLACK, "Press joystick to start");
			}
		}
	}
}

void ball_routine(void *params){
	object_t *ball = &object[0];
	while (1) {
			if (joystick_get_state(JOYSTICK_CENTER)) {
				lcd_print(30,280,SMALLFONT,LCD_BLACK,LCD_BLACK, "Press joystick to start");
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
			}
			vTaskDelay(10 / portTICK_RATE_MS);

	if(ball->active){
		lcd_circle(ball->x, ball->y, ball->radius, LCD_BLACK);	//efface la balle
		check_ball_vs_racket(ball);
		check_ball_vs_ghost(ball);
		check_border(ball, false);
		if(ball->active){
			move(ball);
			lcd_circle(ball->x, ball->y, ball->radius, LCD_BLUE);	//affiche la balle
		}
	}
	}
}

//initialise la balle
void init_ball(object_t *ball) {
	ball->radius = RADIUS_BALL;
	ball->x = START_POS_X - ball->radius - STEP;
	ball->y = START_POS_Y - ball->radius - STEP;
	ball->dir = NORTH + EAST;
	ball->active = true;
}
