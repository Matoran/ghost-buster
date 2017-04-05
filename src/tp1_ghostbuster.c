/**
 * Name        : tp1_ghostbuster.c
 * Version     : 1.0
 * Description : Ghostbuster game template. FreeRTOS in cooperative mode.
 */

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
#define MAXPOSX 239 //240-1 start count at 0
#define MAXPOSY 299 //320-1 start count at 0
#define STARTPOSX 239
#define STARTPOSY 299

// Direction vector. Note that only 8 directions are possible,
// since NORTH|SOUTH is nonsense for example.
enum {
	NORTH=1,
	EAST=2,
	SOUTH=4,
	WEST=8
};

// structure containing object position, size and direction
typedef struct {
	int x;
	int y;
	int radius;
	int dir;
	bool active;
} object_t;

// object instances:  object[0] is the ball, the other objects are the ghosts
object_t object[GHOST_NB+1];
// pointers on the ghosts bitmaps. 2 images by ghost direction.
__DATA(RAM2) uint16_t *ghost_im_left[2], *ghost_im_right[2], *ghost_im_center[2];
uint16_t ghost_width, ghost_height;


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
int test_collision(int object_id, object_t *obj_array, int min_idx, int max_idx)
{
	int i, dx, dy, dx_col, dy_col, col;

	for (i=min_idx; i<=max_idx; i++)		// search only collisions with ghosts (never with ball)
		if (i!=object_id && object[i].active)
		{
			dx_col=obj_array[object_id].radius+obj_array[i].radius+STEP;
			dy_col=obj_array[object_id].radius+obj_array[i].radius+STEP;
			dx=obj_array[object_id].x-obj_array[i].x;
			dy=obj_array[object_id].y-obj_array[i].y;
			if (ABS(dx) <= dx_col && ABS(dy) <= dy_col)
			{
				col=NO_COLLISION;
				if (dx>0)
					col|=WEST;
				else if (dx<0)
					col|=EAST;
				if (dy>0)
					col|=NORTH;
				else if (dy<0)
					col|=SOUTH;
				if (col & obj_array[object_id].dir)	// collision tested only in the object direction
					return i;		// return (one of) the ID of the object creating the collision
			}
		}
	return NO_COLLISION;
}

//bouge n'importe quelle objet en fonction de son step
void move(object_t *obj){
	switch (obj->dir){
		case NORTH:
			obj->y -= STEP;
			break;
		case SOUTH:
			obj->y += STEP;
			break;
		case EAST:
			obj->x += STEP;
			break;
		case WEST:
			obj->x -= STEP;
			break;
		case NORTH+EAST:
			obj->x += STEP;
			obj->y -= STEP;
			break;
		case NORTH+WEST:
			obj->x -= STEP;
			obj->y -= STEP;
			break;
		case SOUTH+EAST:
			obj->x += STEP;
			obj->y += STEP;
			break;
		case SOUTH+WEST:
			obj->x -= STEP;
			obj->y += STEP;
			break;
		default:
			break;
	}
}

//change sa direction
void inverse_dir(object_t *obj){
	switch (obj->dir){
		case NORTH:
			obj->dir = SOUTH;
			break;
		case SOUTH:
			obj->dir = NORTH;
			break;
		case EAST:
			obj->dir = WEST;
			break;
		case WEST:
			obj->dir = EAST;
			break;
		case NORTH+EAST:
			obj->dir = NORTH+WEST;
			break;
		case NORTH+WEST:
			obj->dir = NORTH+EAST;
			break;
		case SOUTH+EAST:
			obj->dir = SOUTH+WEST;
			break;
		case SOUTH+WEST:
			obj->dir = SOUTH+EAST;
			break;
		case NORTH+EAST+20:
			obj->dir = SOUTH+EAST;
			break;
		case NORTH+WEST+20:
			obj->dir = SOUTH+WEST;
			break;
		case SOUTH+EAST+20:
			obj->dir = NORTH+EAST;
			break;
		case SOUTH+WEST+20:
			obj->dir = NORTH+WEST;
			break;
		default:
			break;
	}
}

//check si un objet touche un board,
//si c'est le cas le fait changer de direction
void check_border(object_t *obj){
	bool top = false;
	bool bottom = false;
	bool right = false;
	bool left = false;

	if(obj->x - obj->radius <= STEP){
		left = true;
	}

	if(obj->x + obj->radius > MAXPOSX-STEP){
		right = true;
	}

	if(obj->y - obj->radius <= STEP){
		top = true;
	}

	if(obj->y + obj->radius >= MAXPOSY-STEP){
		bottom = true;
	}

	if(top || bottom){
		if(obj->dir != NORTH && obj->dir != SOUTH && obj->dir != WEST && obj->dir != EAST){
			obj->dir += 20;
		}
		inverse_dir(obj);
	}

	if(left || right){
		inverse_dir(obj);
	}

}

void check_ball_vs_ghost(object_t *ball){
	int x = 110;
	int y = 150;
	int w = &ghost_width;
	int h = &ghost_height;

	int x2 = x + h;
	int y2 = y + h;

	int x3 = x + h + w;
	int y3 = y + h + w;

	int x4 = x + w;
	int y4 = y + w;

	if((ball->x - ball->radius) > x3 && (ball->y + ball->radius) > y3 && (ball->x - ball->radius) < x2 && (ball->y + ball->radius) < y2){
		ball->dir = WEST;
	}
}

//initialise la balle
void init_ball(object_t *ball){
	ball->radius = 50;
	ball->x = STARTPOSX - ball->radius;
	ball->y = STARTPOSY - ball->radius;
	ball->dir = NORTH + EAST;
	ball->active = true;
}

int lives = 3;
int score = 0;

int main(void)
{
	init_rnd32(1);
	init_lcd();
	clear_screen(LCD_BLACK);
	init_traces(115200, 1, true);		// to be removed if you implement your own traces

	if ((ghost_im_left[0]=read_bmp_file("ghost_l1.bmp", &ghost_width, &ghost_height))==NULL)
		return -1;
	//lcd_print(85, 100, SMALLFONT, LCD_WHITE, LCD_BLACK, "Have fun!");

	display_bitmap16(ghost_im_left[0], 110, 150, ghost_width, ghost_height);

	object_t ball;
	init_ball(&ball);
	//lcd_circle(1, 1, 1, LCD_WHITE);
	lcd_circle(ball.x, ball.y, ball.radius, LCD_GREEN);
	lcd_print(40, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "Lives: %d", lives);
	lcd_print(140, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "Score: %d", score);
	int i = 0;

	while(1){

		for(i; i < 250000; i++){};//attente active
		lcd_circle(ball.x,ball.y,ball.radius,LCD_BLACK);//efface la balle
		check_border(&ball);
		check_ball_vs_ghost(&ball);
		move(&ball);
		lcd_circle(ball.x,ball.y,ball.radius,LCD_GREEN);//affiche la balle
		i = 0;
	}
	return 1;
}
