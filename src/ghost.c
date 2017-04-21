#include "ghost.h"
#include "collision.h"
#include "random.h"

int randomDirection() {
	return 1 << randBetween(0, 3);
}

void loadGhosts() {
	if ((ghost_im_left[0] = read_bmp_file("ghost_l1.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while(1){};
	if ((ghost_im_left[1] = read_bmp_file("ghost_l2.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while(1){};
	if ((ghost_im_right[0] = read_bmp_file("ghost_r1.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while(1){};
	if ((ghost_im_right[1] = read_bmp_file("ghost_r2.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while(1){};
	if ((ghost_im_center[0] = read_bmp_file("ghost_c1.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while(1){};
	if ((ghost_im_center[1] = read_bmp_file("ghost_c2.bmp", &ghost_width,
			&ghost_height)) == NULL)
		while(1){};
	for (int i = 1; i <= GHOST_NB; i++) {
		object[i].active = true;
		object[i].x = 10+i*30;
		object[i].y = 100;
		object[i].radius = ghost_height / 2;

		object[i].dir = randomDirection();
	}
}

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

void ghost(int id, int animation) {
	if (object[id].active) {
		if (test_collision(id, object, 1, GHOST_NB)) {
			if (object[id].dir != NORTH && object[id].dir != SOUTH
					&& object[id].dir != WEST && object[id].dir != EAST) {
				inverse_dir_bottom_top(&object[id], false);
			} else {
				inverse_dir(&object[id]);
			}
			//object[id].dir = randomDirection();
		}
		check_border(&object[id], true); //
		ghost_clear(&object[id]);
		move(&object[id]);

		switch (object[id].dir) {
		case EAST:
			display_bitmap16(ghost_im_right[animation % 2],
					object[id].x - object[id].radius,
					object[id].y - object[id].radius, ghost_width,
					ghost_height);
			break;
		case WEST:
			display_bitmap16(ghost_im_left[animation % 2],
					object[id].x - object[id].radius,
					object[id].y - object[id].radius, ghost_width,
					ghost_height);

			break;
		default:
			display_bitmap16(ghost_im_center[animation % 2],
					object[id].x - object[id].radius,
					object[id].y - object[id].radius, ghost_width,
					ghost_height);

		}

	} else {
		if (randBetween(1, 100) == 1) {
			object[id].active = true;
		}
	}
}
