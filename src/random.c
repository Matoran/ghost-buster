#include "random.h"


uint32_t randBetween(uint32_t min, uint32_t max){
	return rnd_32() % (max + 1 - min) + min;
}
