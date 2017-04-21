#include "ball.h"
#include "raquet.h"
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
				object[i].active = 0;
			}
		}
	}
}

void check_ball_vs_racket(object_t *ball){
	if(ball->y + ball->radius >= MAXPOSY - STEP){
		if(ball->x - ball->radius > raquet.x + raquet.lenght + STEP || ball->x + ball->radius < raquet.x - STEP){
			if(lives > 1){
				lives--;
				lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", lives);
				//ball->x = raquet.x + raquet.lenght/2;
				//ball->y = MAXPOSY - ball->radius - STEP;
				ball->x = STARTPOSX - ball->radius - STEP;
				ball->y = STARTPOSY - ball->radius - STEP;
				ball->dir = NORTH + EAST;
				vTaskDelay(1000/portTICK_RATE_MS);
			}else{
				lives--;
				lcd_circle(ball->x, ball->y, ball->radius, LCD_BLACK);
				lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", lives);
				ball->active = false;
			}
		}
	}
}

void ball_routine(object_t *ball){
	if(ball->active){
		lcd_circle(ball->x, ball->y, ball->radius, LCD_BLACK);	//efface la balle
		check_ball_vs_racket(ball);
		check_border(ball, false);
		check_ball_vs_ghost(ball);
		if(ball->active){
			move(ball);
			lcd_circle(ball->x, ball->y, ball->radius, LCD_BLUE);	//affiche la balle
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
