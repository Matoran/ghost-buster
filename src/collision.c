//check si un objet touche un board,
//si c'est le cas le fait changer de direction
void check_border(object_t *obj) {
	bool top = false;
	bool bottom = false;
	bool right = false;
	bool left = false;

	if (obj->x - obj->radius <= STEP) {
		left = true;
	}

	if (obj->x + obj->radius > MAXPOSX - STEP) {
		right = true;
	}

	if (obj->y - obj->radius <= STEP) {
		top = true;
	}

	if (obj->y + obj->radius >= MAXPOSY - STEP) {
		bottom = true;
	}

	if (top || bottom) {
		if (obj->dir != NORTH && obj->dir != SOUTH && obj->dir != WEST
				&& obj->dir != EAST) {
			inverse_dir_bottom_top(obj);
		} else {
			inverse_dir(obj);
		}
	}

	if (left || right) {
		inverse_dir(obj);
	}

}


//bouge n'importe quelle objet en fonction de son step
void move(object_t *obj) {
	switch (obj->dir) {
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
	case NORTH + EAST:
		obj->x += STEP;
		obj->y -= STEP;
		break;
	case NORTH + WEST:
		obj->x -= STEP;
		obj->y -= STEP;
		break;
	case SOUTH + EAST:
		obj->x += STEP;
		obj->y += STEP;
		break;
	case SOUTH + WEST:
		obj->x -= STEP;
		obj->y += STEP;
		break;
	default:
		break;
	}
}

//change sa direction
void inverse_dir(object_t *obj) {
	switch (obj->dir) {
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
	case NORTH + EAST:
		obj->dir = NORTH + WEST;
		break;
	case NORTH + WEST:
		obj->dir = NORTH + EAST;
		break;
	case SOUTH + EAST:
		obj->dir = SOUTH + WEST;
		break;
	case SOUTH + WEST:
		obj->dir = SOUTH + EAST;
		break;
	}
}

//change sa direction
void inverse_dir_bottom_top(object_t *obj) {
	switch (obj->dir) {
	case NORTH + EAST:
		obj->dir = SOUTH + EAST;
		break;
	case NORTH + WEST:
		obj->dir = SOUTH + WEST;
		break;
	case SOUTH + EAST:
		obj->dir = NORTH + EAST;
		break;
	case SOUTH + WEST:
		obj->dir = NORTH + WEST;
		break;
	default:
		break;
	}
}
