
#ifndef FOURLEG_H
#define FOURLEG_H


#include "HT03.h"
#include "IMPULSE.h"


// create leg struct bind things to it



typedef struct 
{
	int w_leg; // which leg refer to in impulse.h
	uint8_t motor_in ; // the motorid inside
	uint8_t motort_out ; // the motorid outside

}LEG;

void LEG_init();




#endif