#ifndef _PID_H
#define _PID_H
typedef struct{
	float target_val;
	float actual_val;
	float err;
	float err_last;
	float err_prev;
	float err_sum;
	float kp,ki,kd;
}PID_HandleTypeDef;

void PID_Init(PID_HandleTypeDef *pid, float kp, float ki, float kd);


#endif
