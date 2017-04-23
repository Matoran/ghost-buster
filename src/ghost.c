/**
 * @authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: manage ghosts in the game (load images, move, animation)
 * Language:  C
 * Date : april 2017
 */

#include "ghost.h"
#include "collision.h"
#include "random.h"

/**
 * init ghosts
 */
void ghosts_init() {
	for (int i = 1; i <= GHOST_NB; i++) {
		object[i].active = true;
		object[i].x = 10 + i * 30;
		object[i].y = 100;
		object[i].radius = ghost_height / 2;

		object[i].dir = ghost_random_direction();
	}
}

/**
 * generate a random direction north, south, east or west
 * @return the direction
 */
int ghost_random_direction() {
	return 1 << randBetween(0, 3);
}

/**
 * load all images of the ghost
 */
void ghost_load_images() {
	if ((ghost_im_left[0] = read_bmp_file("ghost_l1.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while (1) {
		};
	if ((ghost_im_left[1] = read_bmp_file("ghost_l2.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while (1) {
		};
	if ((ghost_im_right[0] = read_bmp_file("ghost_r1.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while (1) {
		};
	if ((ghost_im_right[1] = read_bmp_file("ghost_r2.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while (1) {
		};
	if ((ghost_im_center[0] = read_bmp_file("ghost_c1.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while (1) {
		};
	if ((ghost_im_center[1] = read_bmp_file("ghost_c2.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while (1) {
		};

}

/**
 * clear the ghost before move
 * @param ghost to clear
 */
void ghost_clear(object_t *ghost) {
	if ((ghost->dir & NORTH) == NORTH) {
		lcd_filled_rectangle(ghost->x - ghost->radius,
				ghost->y + ghost->radius - STEP, ghost->x + ghost->radius,
				ghost->y + ghost->radius, LCD_BLACK);
	} else if ((ghost->dir & SOUTH) == SOUTH) {
		lcd_filled_rectangle(ghost->x - ghost->radius, ghost->y - ghost->radius,
				ghost->x + ghost->radius, ghost->y - ghost->radius + STEP,
				LCD_BLACK);
	}
	if ((ghost->dir & EAST) == EAST) {
		lcd_filled_rectangle(ghost->x - ghost->radius, ghost->y - ghost->radius,
				ghost->x - ghost->radius + STEP, ghost->y + ghost->radius,
				LCD_BLACK);
	} else if ((ghost->dir & WEST) == WEST) {
		lcd_filled_rectangle(ghost->x + ghost->radius - STEP,
				ghost->y - ghost->radius, ghost->x + ghost->radius,
				ghost->y + ghost->radius, LCD_BLACK);
	}
}

/**
 * draw ghost with correct image depending on direction and frame animation
 * @param ghost to draw
 * @param animation 0 or 1
 */
void ghost_draw(object_t *ghost, int animation) {
	switch (ghost->dir) {
	case EAST:
		display_bitmap16(ghost_im_right[animation % 2],
				ghost->x - ghost->radius, ghost->y - ghost->radius, ghost_width,
				ghost_height);
		break;
	case WEST:
		display_bitmap16(ghost_im_left[animation % 2], ghost->x - ghost->radius,
				ghost->y - ghost->radius, ghost_width, ghost_height);

		break;
	default:
		display_bitmap16(ghost_im_center[animation % 2],
				ghost->x - ghost->radius, ghost->y - ghost->radius, ghost_width,
				ghost_height);

	}
}

/**
 * task for one ghost, manage animation, random direction, collision, move and draw
 * @param params id of the ghost
 */
void ghost_routine(void *params) {
	int id = *(int*) params;
	int cpt_random_direction = 0, cpt_animation = 1, animation = 0;
	object_t *ghost = &object[id];
	while (1) {
		vTaskDelay(20 + id * 2 / portTICK_RATE_MS);
		if (ghost->active) {
			if (test_collision(id, object, 1, GHOST_NB)) {
				if (ghost->dir != NORTH && ghost->dir != SOUTH
						&& object[id].dir != WEST && ghost->dir != EAST) {
					inverse_dir_bottom_top(ghost, false);
				} else {
					inverse_dir(ghost);
				}
			}
			check_border(ghost, true); //
			ghost_clear(ghost);
			move(ghost);
			ghost_draw(ghost, animation);
			cpt_random_direction++;
			cpt_animation++;
			if (cpt_animation >= (100 + id * 10) / (20 + id * 2)) {
				animation++;
				animation %= 2;
				cpt_animation = 0;
			}
			if (cpt_random_direction >= (2000 + id * 200) / (20 + id * 2)) {
				ghost->dir = ghost_random_direction();
				cpt_random_direction = 0;
			}
		}

	}
}
