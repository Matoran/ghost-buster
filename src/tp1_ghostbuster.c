
int lives = 3;
int score = 0;

void check_ball_vs_ghost(object_t *ball){
	/*int w = ghost_width;
	int r = ghost_width/2;
	int x = 110+r;
	int y = 150+ghost_height/2;*/
	/*dx_col=ball->radius+r+STEP;
	dy_col=ball->radius+r+STEP;
	dx=ball->x-x;
	dy=ball->y-y;*/

	int dx, dy, dx_col, dy_col;

	for(int i = 0; i < GHOST_NB; i++){
		dx_col=ball->radius+object[i].radius+STEP;
		dy_col=ball->radius+object[i].radius+STEP;
		dx=ball->x-object[i].x;
		dy=ball->y-object[i].y;
		if(ABS(dx) <= dx_col && ABS(dy) <= dy_col){
			score++;
			lcd_print(190, 305, SMALLFONT, LCD_WHITE, LCD_BLACK, "%d", score);
			if(ball->dir != NORTH && ball->dir != SOUTH && ball->dir != WEST && ball->dir != EAST){
				inverse_dir_bottom_top(ball);
			}else{
				inverse_dir(ball);
			}
			lcd_filled_rectangle(object[i].x-object[i].radius, object[i].y-object[i].radius, object[i].x+object[i].radius, object[i].y+object[i].radius, LCD_BLACK);
int main(void){