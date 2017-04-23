/**
 * @authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Ghostbuster game template. FreeRTOS in cooperative mode.
 * Language:  C
 * Date : april 2017
 */
#include "define.h"
#include "paddle.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "ghost.h"
#include "ball.h"
#include "uart.h"

/**
 * init peripherals, uart, screen, random, load images, reset timer
 */
void init() {
	init_rnd32(1);
	init_lcd();
	clear_screen(LCD_BLACK);
	uart0_init(115200);
	ghost_load_images();
	init_paddle();
	init_ball(&object[0]);
	object[0].active = false;
	LPC_GPIO1->FIODIR &= ~(0b11111 << 19);
	lcd_print(40, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "Lives:");
	lcd_print(90, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", lives);
	lcd_print(140, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "Score:");
	lcd_print(190, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", score);
	lcd_print(30,280,SMALLFONT,LCD_WHITE,LCD_BLACK, "Press joystick to start");
	LPC_TIM0->PR = 1;
	LPC_TIM0->TCR = 2;
	LPC_TIM0->TCR = 1;
}

/**
 * call init and create tasks (ball, paddle, ghosts)
 * @return
 */
int main(void) {
	init();
	if (xTaskCreate(ball_routine, (signed portCHAR *)"ball", configMINIMAL_STACK_SIZE,
			NULL, 1, NULL) != pdPASS) {
		while (1) {
		};
	}
	if (xTaskCreate(paddle_routine, (signed portCHAR *)"paddle", configMINIMAL_STACK_SIZE,
			NULL, 1, NULL) != pdPASS) {
		while (1) {
		};
	}
	for (int i = 1; i <= GHOST_NB; i++) {
		int *id = malloc(sizeof(int));
		*id = i;
		if (xTaskCreate(ghost_routine, (signed portCHAR *)"ghost_routine", configMINIMAL_STACK_SIZE,
				id, 1, NULL) != pdPASS) {
			while (1) {
			};
		}
	}
	vTaskStartScheduler();
}
