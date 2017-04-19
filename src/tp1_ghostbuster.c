/**
 * Name        : tp1_ghostbuster.c
 * Version     : 1.0
 * Description : Ghostbuster game template. FreeRTOS in cooperative mode.
 */

#include "define.h"
#include "raquet.h"

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
	init_ball(&object[GHOST_NB]);
	LPC_GPIO1->FIODIR &= ~(0b11111 << 19);
	lcd_print(40, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "Lives:");
	lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", lives);
	lcd_print(140, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "Score:");
	lcd_print(190, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", score);
}

int main(void) {
	init();


	int i = 0;
	int cpt = 0;
	while (1) {
		for (i; i < 250000; i++) {};//attente active
		cpt++;
		ball_routine(&object[GHOST_NB]);
		raquet_routine();
		i = 0;
		if(cpt == 2){
			ghosts();
			cpt = 0;
		}
	}
}
