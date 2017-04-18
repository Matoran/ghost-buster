#include "ghost.h"
#include "collision.h"

int animation = 0;

int randomDirection() {
	int direction;
	//NORTH = 1, EAST = 2, SOUTH = 4, WEST = 8
	do {
		direction = randBetween(1, 12);
	} while ((direction & 5) == 5 || (direction & 10) == 10);
	return direction;
}

void loadGhosts() {
	if ((ghost_im_left[0] = read_bmp_file("ghost_l1.bmp", &ghost_width,
			&ghost_height)) == NULL)
		return -1;
	if ((ghost_im_left[1] = read_bmp_file("ghost_l2.bmp", &ghost_width,
			&ghost_height)) == NULL)
		return -1;
	if ((ghost_im_right[0] = read_bmp_file("ghost_r1.bmp", &ghost_width,
			&ghost_height)) == NULL)
		return -1;
	if ((ghost_im_right[1] = read_bmp_file("ghost_r2.bmp", &ghost_width,
			&ghost_height)) == NULL)
		return -1;
	if ((ghost_im_center[0] = read_bmp_file("ghost_c1.bmp", &ghost_width,
			&ghost_height)) == NULL)
		return -1;
	if ((ghost_im_center[1] = read_bmp_file("ghost_c2.bmp", &ghost_width,
			&ghost_height)) == NULL)
		return -1;
	for (int i = 0; i < GHOST_NB; i++) {
		object[i].active = true;
		object[i].x = randBetween(ghost_width / 2, MAXPOSX - ghost_width / 2);
		object[i].y = randBetween(ghost_height / 2, MAXPOSY - ghost_height / 2);
		object[i].radius = ghost_height / 2;

		object[i].dir = randomDirection();
	}
}

void ghost(int id) {
	if (object[id].active) {
		lcd_filled_rectangle(object[id].x - object[id].radius,
				object[id].y - object[id].radius,
				object[id].x + object[id].radius,
				object[id].y + object[id].radius, LCD_BLACK);
		if (test_collision(id, &object, 0, GHOST_NB)) {
			object[id].dir = randomDirection();
		}
		check_border(&object[id]);//
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

void ghosts() {
	animation++;
	animation %= 2;
	for (int i = 0; i < GHOST_NB; i++) {
		ghost(i);
	}
}

void drawGhosts() {
	while (1) {
		display_bitmap16(ghost_im_left[0], 110, 150, ghost_width, ghost_height);
		int start = LPC_TIM0->TC;
		while (LPC_TIM0->TC - start < 25e3 * 30) {
		}
		display_bitmap16(ghost_im_left[1], 110, 150, ghost_width, ghost_height);
		start = LPC_TIM0->TC;
		while (LPC_TIM0->TC - start < 25e3 * 30) {
		}
		display_bitmap16(ghost_im_right[0], 110, 150, ghost_width,
				ghost_height);
		start = LPC_TIM0->TC;
		while (LPC_TIM0->TC - start < 25e3 * 30) {
		}
		display_bitmap16(ghost_im_right[1], 110, 150, ghost_width,
				ghost_height);
		start = LPC_TIM0->TC;
		while (LPC_TIM0->TC - start < 25e3 * 30) {
		}
		display_bitmap16(ghost_im_center[0], 110, 150, ghost_width,
				ghost_height);
		start = LPC_TIM0->TC;
		while (LPC_TIM0->TC - start < 25e3 * 30) {
		}
		display_bitmap16(ghost_im_center[1], 110, 150, ghost_width,
				ghost_height);
	}
}
