/**
 * Name        : tp1_ghostbuster.c
 * Version     : 1.0
 * Description : Ghostbuster game template. FreeRTOS in cooperative mode.
 */

#include "define.h"
#include "raquet.h"

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

void init() {
	LPC_TIM0->PR = 1;
	LPC_TIM0->TCR = 2;
	LPC_TIM0->TCR = 1;
	init_rnd32(1);
	init_lcd();
	clear_screen(LCD_BLACK);
	init_traces(115200, 1, true);// to be removed if you implement your own traces
	loadGhosts();
	init_square_control();
	LPC_GPIO1->FIODIR &= ~(0b11111 << 19);
}

int main(void) {
	init();

	object_t ball;
	init_ball(&ball);
//lcd_circle(1, 1, 1, LCD_WHITE);
	lcd_circle(ball.x, ball.y, ball.radius, LCD_GREEN);
	lcd_print(40, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "Lives:");
	lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", lives);
	lcd_print(140, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "Score:");
	lcd_print(190, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", score);

	int i = 0;

	while (1) {
		for (i; i < 250000; i++) {
		};	//attente active
		lcd_circle(ball.x, ball.y, ball.radius, LCD_BLACK);	//efface la balle
		check_border(&ball);
		check_ball_vs_ghost(&ball);
		move(&ball);
		lcd_circle(ball.x, ball.y, ball.radius, LCD_GREEN);	//affiche la balle
		raquet_routine();
		ghosts();
		i = 0;
	}
}
