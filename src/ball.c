#include "ball.h"
#include "raquet.h"


void check_ball_vs_ghost(object_t *ball) {
	/*int w = ghost_width;
	 int h = ghost_height;
	 int r = ghost_width / 2;
	 int x = 110 + r;
	 int y = 150 + ghost_height / 2;

	 dx_col = ball->radius + r + STEP;
	 dy_col = ball->radius + r + STEP;
	 dx = ball->x - x;
	 dy = ball->y - y;*/

	int dx, dy, dx_col, dy_col;

	for (int i = 0; i < GHOST_NB; i++) {
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
					inverse_dir_bottom_top(ball);
				} else {
					inverse_dir(ball);
				}
				lcd_filled_rectangle(object[i].x - object[i].radius,
						object[i].y - object[i].radius,
						object[i].x + object[i].radius,
						object[i].y + object[i].radius, LCD_BLACK);
				object[i].active = 0;
			}
		}
	}
}

void check_ball_vs_racket(object_t *ball){
	if(ball->y + ball->radius >= MAXPOSY - STEP){
		if(ball->x - ball->radius > raquet.x + raquet.lenght + STEP || ball->x + ball->radius < raquet.x - STEP){
			lives--;
			lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", lives);
			ball->x = raquet.x + raquet.lenght/2;
			ball->y = MAXPOSY - ball->radius - STEP;
		}
	}
}

//initialise la balle
void init_ball(object_t *ball) {
	ball->radius = 3;
	ball->x = STARTPOSX - ball->radius - STEP;
	ball->y = STARTPOSY - ball->radius - STEP;
	ball->dir = NORTH + EAST;
	ball->active = true;
}
