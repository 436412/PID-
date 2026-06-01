#include "stm32f10x.h"                  // Device header
#include "pid.h"

void PID_Init(PID_HandleTypeDef *pid, float kp, float ki, float kd)
{
	pid->target_val = 0;
	pid->actual_val = 0;
	pid->err = 0;
	pid->err_last = 0;
	pid->err_prev = 0;
	pid->err_sum = 0;
	
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
}
float PID_Calc(PID_HandleTypeDef *pid, float target,float actual)
{
	pid->target_val = target;
	pid->actual_val = actual;
	pid->err = pid->target_val - pid->actual_val;
	
	float integral_term = pid->ki * pid->err_sum;
	if(integral_term > 1000)
	{
		pid->err_sum = 1000 / pid->ki;
	}
	else if(integral_term < -1000)
	{
		pid->err_sum = -1000 / pid->ki;
		
	}
	else
	{
		pid->err_sum += pid->err;
	}
	
	float output = pid->kp * pid->err
	             + pid->ki * pid->err_sum
	             + pid->kd * (pid->err - pid->err_last);
	
	pid->err_last = pid->err;
	return output;
	
}
//
float PID_Calc_Incremental(PID_HandleTypeDef *pid,float target,float actual)
{
	pid->target_val = target;
	pid->actual_val = actual;
	pid->err = pid->target_val - pid->actual_val;
	
	
	float delta_output = pid->kp * (pid->err - pid->err_last)
		               + pid->ki * pid->err
	                   + pid->kd * (pid->err - 2*pid->err_last + pid->err_prev);
	pid->err_prev = pid->err_last;
	pid->err_last = pid->err;
	static float output = 0;
	output += delta_output;
	return output;
}