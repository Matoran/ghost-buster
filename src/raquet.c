/*
 * raquet.c

 *
 *  Created on: 5 avr. 2017
 *      Author: gaetan
 */
#include "define.h"

raquet_t raquet;


void init_square_control(){
	raquet.lenght = 30;
	raquet.width = 4;
	raquet.x = 110;
	raquet.y = 299;
	raquet.dir = 0;

	lcd_filled_rectangle(raquet.x,raquet.y,raquet.x+raquet.lenght,raquet.y+raquet.width,LCD_GREEN);
}

bool inBorderLeft(raquet_t *object){
	if (object->x < (0 + STEP)) {
		return true;
	}else{
		return false;
	}
}

bool inBorderRight(raquet_t *object){
	if ((object->x + object->lenght) >= MaxPosX - STEP) {
		return true;
	}else{
		return false;
	}
}

/***********************************
 * function     : JoystickGetState
 * arguments    : pos (from enum)
 * return value : int
 *   est 	= p1.21	 -> 2
 *   ouest 	= p1.23	 -> 4
 ***********************************/
bool JoystickGetState(uint8_t pos){
	if ((LPC_GPIO1->FIOPIN >> pos) & 1 == 1) {
		return false;
	}else {
		return true;
	}
}
void direction_joystick(){
	if (JoystickGetState(JLeft)) {
		if (inBorderLeft(&raquet)) {
			raquet.dir = 0;
		}else{
			raquet.dir = WEST;
		}
		raquet.active = true;
	}else{
		raquet.dir = 0;
		raquet.active = false;
	}

	if(JoystickGetState(JRight)){
		if (inBorderRight(&raquet)) {
			raquet.dir = 0;
		}else{
			raquet.dir = EAST;
		}
		raquet.active = true;
	}else if (raquet.active == false){
		raquet.dir = 0;
	}
}

void raquet_move(raquet_t *obj){
	switch (obj->dir){
		case EAST:
			obj->x += STEP;
			break;
		case WEST:
			obj->x -= STEP;
			break;
		default:
			break;
	}
}

void raquet_routine(){
	direction_joystick();
	switch (raquet.dir) {
		case WEST:
			lcd_filled_rectangle(raquet.x+raquet.lenght-STEP,raquet.y,raquet.x+raquet.lenght,raquet.y+raquet.width,LCD_BLACK);
			break;
		case EAST:
			lcd_filled_rectangle(raquet.x,raquet.y,raquet.x+STEP,raquet.y+raquet.width,LCD_BLACK);
			break;
		default:
			break;
	}
	raquet_move(&raquet);
	lcd_filled_rectangle(raquet.x,raquet.y,raquet.x+raquet.lenght,raquet.y+raquet.width,LCD_GREEN);
}

