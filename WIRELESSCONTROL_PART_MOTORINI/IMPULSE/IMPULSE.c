#include "IMPULSE.h"


PULSE PULSE_data[4];


// void PULSE_INIT(float X_N,float Y_N,float X_MAX, float Y_MAX);

void PULSE_INIT(int X_N,int Y_N,int X_MAX, int Y_MAX,float sx_RF, float sy_RF,float sx_RB, 
	float sy_RB,float sx_LF, float sy_LF,float sx_LB, float sy_LB)
{
    PULSE_data[RF].TIME_X_N = X_N;
    PULSE_data[RF].TIME_Y_N = Y_N;
    PULSE_data[RF].TIME_X_MAX = X_MAX;
    PULSE_data[RF].TIME_Y_MAX = Y_MAX;
    PULSE_data[RF].TIME_X = sx_RF;
    PULSE_data[RF].TIME_Y = sy_RF;
    PULSE_data[RF].TIME_X_value = 0;
    PULSE_data[RF].TIME_Y_value = 0;

    PULSE_data[RB].TIME_X_N = X_N;
    PULSE_data[RB].TIME_Y_N = Y_N;
    PULSE_data[RB].TIME_X_MAX = X_MAX;
    PULSE_data[RB].TIME_Y_MAX = Y_MAX;
    PULSE_data[RB].TIME_X = sx_RB;
    PULSE_data[RB].TIME_Y = sy_RB;
    PULSE_data[RB].TIME_X_value = 0;
    PULSE_data[RB].TIME_Y_value = 0;

    
    PULSE_data[LF].TIME_X_N = X_N;
    PULSE_data[LF].TIME_Y_N = Y_N;
    PULSE_data[LF].TIME_X_MAX = X_MAX;
    PULSE_data[LF].TIME_Y_MAX = Y_MAX;
    PULSE_data[LF].TIME_X =  sx_LF;
    PULSE_data[LF].TIME_Y =  sy_LF;
    PULSE_data[LF].TIME_X_value = 0;
    PULSE_data[LF].TIME_Y_value = 0;

    PULSE_data[LB].TIME_X_N = X_N;
    PULSE_data[LB].TIME_Y_N = Y_N;
    PULSE_data[LB].TIME_X_MAX = X_MAX;
    PULSE_data[LB].TIME_Y_MAX = Y_MAX;
    PULSE_data[LB].TIME_X =  sx_LB;
    PULSE_data[LB].TIME_Y =  sy_LB;
    PULSE_data[LB].TIME_X_value = 0;
    PULSE_data[LB].TIME_Y_value = 0;

    
}

float map(float x1, float y1, float x2, float y2, float n) {
    // map 的放缩
		float	result = (n - x2) / (y2 -x2) * (y1-x1);
	
	 // if(result < 0) result = 0;
    return result;
}

void PULSE_UPDATE(float spd){

//    PULSE_data[RF].PULSE_SPD = spd;
//    PULSE_data[RB].PULSE_SPD = spd;
//    PULSE_data[LF].PULSE_SPD = spd;
//    PULSE_data[LB].PULSE_SPD = spd;

    if(PULSE_data[RF].TIME_X >= PULSE_data[RF].TIME_X_N*4/4 * 1){
        PULSE_data[RF].TIME_X = 0;
        PULSE_data[RF].TIME_X_value = 0;
    }else if(PULSE_data[RF].TIME_X < 0){
				PULSE_data[RF].TIME_X = PULSE_data[RF].TIME_X_N;
        PULSE_data[RF].TIME_X_value = 0;
		}
    else if(PULSE_data[RF].TIME_X <= (PULSE_data[RF].TIME_X_N/4 *1) ){
        float k = PULSE_data[RF].TIME_X_MAX/(PULSE_data[RF].TIME_X_N/4);
        PULSE_data[RF].TIME_X_value = PULSE_data[RF].TIME_X * k;
    }
    else if(PULSE_data[RF].TIME_X > (PULSE_data[RF].TIME_X_N/4 * 1) && PULSE_data[RF].TIME_X < (PULSE_data[RF].TIME_X_N* 3/4 * 1))
    {
        float k =  (-PULSE_data[RF].TIME_X_MAX -PULSE_data[RF].TIME_X_MAX )/(PULSE_data[RF].TIME_X_N*3/4 - PULSE_data[RF].TIME_X_N *1/4);
        float b =  -(PULSE_data[RF].TIME_X_N *2 /4 * k * 1);
        PULSE_data[RF].TIME_X_value = PULSE_data[RF].TIME_X * k + b;
    }
    else if(PULSE_data[RF].TIME_X >= PULSE_data[RF].TIME_X_N*3/4 * 1){
        
        float k = PULSE_data[RF].TIME_X_MAX/(PULSE_data[RF].TIME_X_N/4);
        float b =  -(PULSE_data[RF].TIME_X_N *4 /4 * k * 1);
        PULSE_data[RF].TIME_X_value = PULSE_data[RF].TIME_X * k + b;
    }

    if(PULSE_data[RF].TIME_Y >= PULSE_data[RF].TIME_Y_N*4/4 * 1){
        PULSE_data[RF].TIME_Y = 0;
        PULSE_data[RF].TIME_Y_value = 0;
    }else if(PULSE_data[RF].TIME_Y < 0){
				PULSE_data[RF].TIME_Y = PULSE_data[RF].TIME_Y_N;
        PULSE_data[RF].TIME_Y_value = 0;
		}
    else if(PULSE_data[RF].TIME_Y <= (PULSE_data[RF].TIME_Y_N/4 *1) ){
        float k = PULSE_data[RF].TIME_Y_MAX/(PULSE_data[RF].TIME_Y_N/4);
        PULSE_data[RF].TIME_Y_value = PULSE_data[RF].TIME_Y * k;
    }
    else if(PULSE_data[RF].TIME_Y > (PULSE_data[RF].TIME_Y_N/4 * 1) && PULSE_data[RF].TIME_Y < (PULSE_data[RF].TIME_Y_N* 3/4 * 1))
    {
        float k =  (-PULSE_data[RF].TIME_Y_MAX -PULSE_data[RF].TIME_Y_MAX )/(PULSE_data[RF].TIME_Y_N*3/4 - PULSE_data[RF].TIME_Y_N *1/4);
        float b =  -(PULSE_data[RF].TIME_Y_N *2 /4 * k * 1);
        PULSE_data[RF].TIME_Y_value = PULSE_data[RF].TIME_Y * k + b;
    }
    else if(PULSE_data[RF].TIME_Y >= PULSE_data[RF].TIME_Y_N*3/4 * 1){
        
        float k = PULSE_data[RF].TIME_Y_MAX/(PULSE_data[RF].TIME_Y_N/4);
        float b =  -(PULSE_data[RF].TIME_Y_N *4 /4 * k * 1);
        PULSE_data[RF].TIME_Y_value = PULSE_data[RF].TIME_Y * k + b;
    }
    


    if(PULSE_data[RB].TIME_X >= PULSE_data[RB].TIME_X_N*4/4 * 1){
        PULSE_data[RB].TIME_X = 0;
        PULSE_data[RB].TIME_X_value = 0;
    }else if(PULSE_data[RB].TIME_X < 0){
				PULSE_data[RB].TIME_X = PULSE_data[RB].TIME_X_N;
        PULSE_data[RB].TIME_X_value = 0;
		}
    else if(PULSE_data[RB].TIME_X <= (PULSE_data[RB].TIME_X_N/4 *1) ){
        float k = PULSE_data[RB].TIME_X_MAX/(PULSE_data[RB].TIME_X_N/4);
        PULSE_data[RB].TIME_X_value = PULSE_data[RB].TIME_X * k;
    }
    else if(PULSE_data[RB].TIME_X > (PULSE_data[RB].TIME_X_N/4 * 1) && PULSE_data[RB].TIME_X < (PULSE_data[RB].TIME_X_N* 3/4 * 1))
    {
        float k =  (-PULSE_data[RB].TIME_X_MAX -PULSE_data[RB].TIME_X_MAX )/(PULSE_data[RB].TIME_X_N*3/4 - PULSE_data[RB].TIME_X_N *1/4);
        float b =  -(PULSE_data[RB].TIME_X_N *2 /4 * k * 1);
        PULSE_data[RB].TIME_X_value = PULSE_data[RB].TIME_X * k + b;
    }
    else if(PULSE_data[RB].TIME_X >= PULSE_data[RB].TIME_X_N*3/4 * 1){
        
        float k = PULSE_data[RB].TIME_X_MAX/(PULSE_data[RB].TIME_X_N/4);
       float b =  -(PULSE_data[RB].TIME_X_N *4 /4 * k * 1);
        PULSE_data[RB].TIME_X_value = PULSE_data[RB].TIME_X * k + b;
    }

    if(PULSE_data[RB].TIME_Y >= PULSE_data[RB].TIME_Y_N*4/4 * 1){
        PULSE_data[RB].TIME_Y = 0;
        PULSE_data[RB].TIME_Y_value = 0;
    }
		else if(PULSE_data[RB].TIME_Y < 0){
				PULSE_data[RB].TIME_Y = PULSE_data[RB].TIME_Y_N;
        PULSE_data[RB].TIME_Y_value = 0;
		}
    else if(PULSE_data[RB].TIME_Y <= (PULSE_data[RB].TIME_Y_N/4 *1) ){
        float k = PULSE_data[RB].TIME_Y_MAX/(PULSE_data[RB].TIME_Y_N/4);
        PULSE_data[RB].TIME_Y_value = PULSE_data[RB].TIME_Y * k;
    }
    else if(PULSE_data[RB].TIME_Y > (PULSE_data[RB].TIME_Y_N/4 * 1) && PULSE_data[RB].TIME_Y < (PULSE_data[RB].TIME_Y_N* 3/4 * 1))
    {
        float k =  (-PULSE_data[RB].TIME_Y_MAX -PULSE_data[RB].TIME_Y_MAX )/(PULSE_data[RB].TIME_Y_N*3/4 - PULSE_data[RB].TIME_Y_N *1/4);
       float b =  -(PULSE_data[RB].TIME_Y_N *2 /4 * k * 1);
        PULSE_data[RB].TIME_Y_value = PULSE_data[RB].TIME_Y * k + b;
    }
    else if(PULSE_data[RB].TIME_Y >= PULSE_data[RB].TIME_Y_N*3/4 * 1){
        
        float k = PULSE_data[RB].TIME_Y_MAX/(PULSE_data[RB].TIME_Y_N/4);
        float b =  -(PULSE_data[RB].TIME_Y_N *4 /4 * k * 1);
        PULSE_data[RB].TIME_Y_value = PULSE_data[RB].TIME_Y * k + b;
    }

    if(PULSE_data[LF].TIME_X >= PULSE_data[LF].TIME_X_N*4/4 * 1){
        PULSE_data[LF].TIME_X = 0;
        PULSE_data[LF].TIME_X_value = 0;
    }
		else if(PULSE_data[LF].TIME_X < 0){
				PULSE_data[LF].TIME_X = PULSE_data[LF].TIME_X_N;
        PULSE_data[LF].TIME_X_value = 0;
		}
    else if(PULSE_data[LF].TIME_X <= (PULSE_data[LF].TIME_X_N/4 *1) ){
        float k = PULSE_data[LF].TIME_X_MAX/(PULSE_data[LF].TIME_X_N/4);
        PULSE_data[LF].TIME_X_value = PULSE_data[LF].TIME_X * k;
    }
    else if(PULSE_data[LF].TIME_X > (PULSE_data[LF].TIME_X_N/4 * 1) && PULSE_data[LF].TIME_X < (PULSE_data[LF].TIME_X_N* 3/4 * 1))
    {
        float k =  (-PULSE_data[LF].TIME_X_MAX -PULSE_data[LF].TIME_X_MAX )/(PULSE_data[LF].TIME_X_N*3/4 - PULSE_data[LF].TIME_X_N *1/4);
        float b =  -(PULSE_data[LF].TIME_X_N *2 /4 * k * 1);
        PULSE_data[LF].TIME_X_value = PULSE_data[LF].TIME_X * k + b;
    }
    else if(PULSE_data[LF].TIME_X >= PULSE_data[LF].TIME_X_N*3/4 * 1){
        
        float k = PULSE_data[LF].TIME_X_MAX/(PULSE_data[LF].TIME_X_N/4);
        float b =  -(PULSE_data[LF].TIME_X_N *4 /4 * k * 1);
        PULSE_data[LF].TIME_X_value = PULSE_data[LF].TIME_X * k + b;
    }

    if(PULSE_data[LF].TIME_Y >= PULSE_data[LF].TIME_Y_N*4/4 * 1){
        PULSE_data[LF].TIME_Y = 0;
        PULSE_data[LF].TIME_Y_value = 0;
    }
		else if(PULSE_data[LF].TIME_Y < 0){
				PULSE_data[LF].TIME_Y = PULSE_data[LF].TIME_Y_N;
        PULSE_data[LF].TIME_Y_value = 0;
		}
    else if(PULSE_data[LF].TIME_Y <= (PULSE_data[LF].TIME_Y_N/4 *1) ){
        float k = PULSE_data[LF].TIME_Y_MAX/(PULSE_data[LF].TIME_Y_N/4);
        PULSE_data[LF].TIME_Y_value = PULSE_data[LF].TIME_Y * k;
    }
    else if(PULSE_data[LF].TIME_Y > (PULSE_data[LF].TIME_Y_N/4 * 1) && PULSE_data[LF].TIME_Y < (PULSE_data[LF].TIME_Y_N* 3/4 * 1))
    {
        float k =  (-PULSE_data[LF].TIME_Y_MAX -PULSE_data[LF].TIME_Y_MAX )/(PULSE_data[LF].TIME_Y_N*3/4 - PULSE_data[LF].TIME_Y_N *1/4);
        float b =  -(PULSE_data[LF].TIME_Y_N *2 /4 * k * 1);
        PULSE_data[LF].TIME_Y_value = PULSE_data[LF].TIME_Y * k + b;
    }
    else if(PULSE_data[LF].TIME_Y >= PULSE_data[LF].TIME_Y_N*3/4 * 1){
        
        float k = PULSE_data[LF].TIME_Y_MAX/(PULSE_data[LF].TIME_Y_N/4);
        float b =  -(PULSE_data[LF].TIME_Y_N *4 /4 * k * 1);
        PULSE_data[LF].TIME_Y_value = PULSE_data[LF].TIME_Y * k + b;
    }


    if(PULSE_data[LB].TIME_X >= PULSE_data[LB].TIME_X_N*4/4 * 1){
        PULSE_data[LB].TIME_X = 0;
        PULSE_data[LB].TIME_X_value = 0;
    }
		else if(PULSE_data[LB].TIME_X < 0){
				PULSE_data[LB].TIME_X = PULSE_data[LB].TIME_X_N;
        PULSE_data[LB].TIME_X_value = 0;
		}
    else if(PULSE_data[LB].TIME_X <= (PULSE_data[LB].TIME_X_N/4 *1) ){
        float k = PULSE_data[LB].TIME_X_MAX/(PULSE_data[LB].TIME_X_N/4);
        PULSE_data[LB].TIME_X_value = PULSE_data[LB].TIME_X * k;
    }
    else if(PULSE_data[LB].TIME_X > (PULSE_data[LB].TIME_X_N/4 * 1) && PULSE_data[LB].TIME_X < (PULSE_data[LB].TIME_X_N* 3/4 * 1))
    {
        float k =  (-PULSE_data[LB].TIME_X_MAX -PULSE_data[LB].TIME_X_MAX )/(PULSE_data[LB].TIME_X_N*3/4 - PULSE_data[LB].TIME_X_N *1/4);
        float b =  -(PULSE_data[LB].TIME_X_N *2 /4 * k * 1);
        PULSE_data[LB].TIME_X_value = PULSE_data[LB].TIME_X * k + b;
    }
    else if(PULSE_data[LB].TIME_X >= PULSE_data[LB].TIME_X_N*3/4 * 1){
        
        float k = PULSE_data[LB].TIME_X_MAX/(PULSE_data[LB].TIME_X_N/4);
        float b =  -(PULSE_data[LB].TIME_X_N *4 /4 * k * 1);
        PULSE_data[LB].TIME_X_value = PULSE_data[LB].TIME_X * k + b;
    }

    if(PULSE_data[LB].TIME_Y >= PULSE_data[LB].TIME_Y_N*4/4 * 1){
        PULSE_data[LB].TIME_Y = 0;
        PULSE_data[LB].TIME_Y_value = 0;
    }
		else if(PULSE_data[LB].TIME_Y < 0){
				PULSE_data[LB].TIME_Y = PULSE_data[LB].TIME_Y_N;
        PULSE_data[LB].TIME_Y_value = 0;
		}
    else if(PULSE_data[LB].TIME_Y <= (PULSE_data[LB].TIME_Y_N/4 *1) ){
        float k = PULSE_data[LB].TIME_Y_MAX/(PULSE_data[LB].TIME_Y_N/4);
        PULSE_data[LB].TIME_Y_value = PULSE_data[LB].TIME_Y * k;
    }
    else if(PULSE_data[LB].TIME_Y > (PULSE_data[LB].TIME_Y_N/4 * 1) && PULSE_data[LB].TIME_Y < (PULSE_data[LB].TIME_Y_N* 3/4 * 1))
    {
        float k =  (-PULSE_data[LB].TIME_Y_MAX -PULSE_data[LB].TIME_Y_MAX )/(PULSE_data[LB].TIME_Y_N*3/4 - PULSE_data[LB].TIME_Y_N *1/4);
        float b =  -(PULSE_data[LB].TIME_Y_N *2 /4 * k * 1);
        PULSE_data[LB].TIME_Y_value = PULSE_data[LB].TIME_Y * k + b;
    }
    else if(PULSE_data[LB].TIME_Y >= PULSE_data[LB].TIME_Y_N*3/4 * 1){
        
        float k = PULSE_data[LB].TIME_Y_MAX/(PULSE_data[LB].TIME_Y_N/4);
        float b =  -(PULSE_data[LB].TIME_Y_N *4 /4 * k * 1);
        PULSE_data[LB].TIME_Y_value = PULSE_data[LB].TIME_Y * k + b;
    }
    

    PULSE_data[RF].TIME_X += spd;
    PULSE_data[RF].TIME_Y += spd;
    PULSE_data[RB].TIME_X += spd;
    PULSE_data[RB].TIME_Y += spd;
    PULSE_data[LF].TIME_X += spd;
    PULSE_data[LF].TIME_Y += spd;
    PULSE_data[LB].TIME_X += spd;
    PULSE_data[LB].TIME_Y += spd;

  





}
