#ifndef IMPULSE_H
#define IMPULSE_H


#define RF 0
#define RB 1
#define LF 2
#define LB 3


typedef struct 
{
	float TIME_X; // %1000
	int TIME_X_N;
	float TIME_X_value;
	int TIME_X_MAX;
	float TIME_Y; // %1000
	int TIME_Y_N;
	float TIME_Y_value;
	int TIME_Y_MAX;
	int PULSE_SPD;
}PULSE;


void PULSE_INIT(int X_N,int Y_N,int X_MAX, int Y_MAX,float sx_RF, float sy_RF,float sx_RB, 
	float sy_RB,float sx_LF, float sy_LF,float sx_LB, float sy_LB);



void PULSE_UPDATE(float spd);


float map(float x1, float y1,float x2, float y2, float n) ;





#endif