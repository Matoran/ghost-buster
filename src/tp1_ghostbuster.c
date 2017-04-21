/**
 * Name        : tp1_ghostbuster.c
 * Version     : 1.0
 * Description : Ghostbuster game template. FreeRTOS in cooperative mode.
 */

#include "define.h"
#include "raquet.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "ghost.h"
#include "ball.h"
#include "random.h"
#include "uart.h"

void init() {
	LPC_TIM0->PR = 1;
	LPC_TIM0->TCR = 2;
	LPC_TIM0->TCR = 1;
	init_rnd32(1);
	init_lcd();
	clear_screen(LCD_BLACK);
	init_traces(115200, 1, true); // to be removed if you implement your own traces
	loadGhosts();
	init_square_control();
	init_ball(&object[0]);
	object[0].active = false;
	LPC_GPIO1->FIODIR &= ~(0b11111 << 19);
	lcd_print(40, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "Lives:");
	lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", lives);
	lcd_print(140, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "Score:");
	lcd_print(190, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", score);
}

void taskA(void *params) {
	while (1) {
		if (JoystickGetState(JCenter)) {
			lcd_circle(object[0].x, object[0].y, object[0].radius, LCD_BLACK);
			score = 0;
			lives = 3;
			init_ball(&object[0]);
			lcd_filled_rectangle(190, 305, MAXPOSX, 319, LCD_BLACK);
			lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", lives);
			lcd_print(190, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", score);
			for (int i = 1; i <= GHOST_NB; i++) {
				object[i].active = true;
			}
		}
		vTaskDelay(10 / portTICK_RATE_MS);
		ball_routine(&object[0]);
	}
}

void taskB(void *params) {
	while (1) {
		vTaskDelay(8 / portTICK_RATE_MS);
		raquet_routine();
	}
}

void taskC(void *params) {
	int id = *(int*) params;
	int cpt = 0, cptAnimation = 1, animation = 0;
	while (1) {
		vTaskDelay(20 + id * 2 / portTICK_RATE_MS);
		ghost(id, animation);
		cpt++;
		cptAnimation++;
		if (cptAnimation >= (100 + id * 10) / (20 + id * 2)) {
			animation++;
			animation %= 2;
			cptAnimation = 0;
		}

		if (cpt >= (2000 + id * 200) / (20 + id * 2)) {
			object[id].dir = randomDirection();
			cpt = 0;
		}
	}
}

int main(void) {
	init();

	if (xTaskCreate(taskA, (signed portCHAR *)"A", configMINIMAL_STACK_SIZE,
			NULL, 1, NULL) != pdPASS) {
		while (1) {
		};
	}

	if (xTaskCreate(taskB, (signed portCHAR *)"B", configMINIMAL_STACK_SIZE,
			NULL, 1, NULL) != pdPASS) {
		while (1) {
		};
	}

	for (int i = 1; i <= GHOST_NB; i++) {
		int *id = malloc(sizeof(int));
		*id = i;
		if (xTaskCreate(taskC, (signed portCHAR *)"C", configMINIMAL_STACK_SIZE,
				id, 1, NULL) != pdPASS) {
			while (1) {
			};
		}
	}
	vTaskStartScheduler();

	/*int i = 0;
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
	 }*/
}
