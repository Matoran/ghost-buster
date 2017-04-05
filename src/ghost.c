#include "ghost.h"

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
		object[i].x = 150;
		object[i].y = 120;
		object[i].radius = ghost_height / 2;
		object[i].dir = i + 1;
	}
}

void ghost(int id) {
	if (object[id].active) {
		lcd_filled_rectangle(object[id].x - object[id].radius,
				object[id].y - object[id].radius,
				object[id].x + object[id].radius,
				object[id].y + object[id].radius, LCD_BLACK);
		move(&object[id]);
		display_bitmap16(ghost_im_left[0], object[id].x - object[id].radius,
				object[id].y - object[id].radius, ghost_width, ghost_height);
	}
}

void ghosts() {
	for (int i = 0; i < GHOST_NB; i++) {
		if (object[i].active) {
			lcd_filled_rectangle(object[i].x - object[i].radius,
					object[i].y - object[i].radius,
					object[i].x + object[i].radius,
					object[i].y + object[i].radius, LCD_BLACK);
			check_border(&object[i]);
			move(&object[i]);
			display_bitmap16(ghost_im_left[0], object[i].x - object[i].radius,
					object[i].y - object[i].radius, ghost_width, ghost_height);
		}
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
