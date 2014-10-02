/****************************************************************************
  Yaxing Li
  CSE 320
  Project #9
****************************************************************************/
#include <stdio.h>
#include <math.h>
#include "/user/cse320/Projects/project10.support.h"

int main()
{
	union dp_item A,B,C,D,E,AA;
	double dblVal, answer;
	unsigned intVal;
 

	//Absolute
	printf("\n Absolute Tests:");
	dblVal =- 3.773;
	answer  = absolute(dblVal);
	printf("\n\tAbsolute value of %f = %f", dblVal, answer);
 
	dblVal = 0;
	answer  = absolute(dblVal);
	printf("\n\tAbsolute value of %f = %f", dblVal, answer);
 
 
	//Square Root
	dblVal = 36;
	printf("\n\n Square Root Tests:");
	answer = sqroot(dblVal);
	printf("\n\tSquare root of %f = %f", dblVal, answer);
 
	dblVal = -8;
	answer = sqroot(dblVal);
	printf("\n\tSquare root of %f = %f", dblVal, answer);
 
 
	//Factorial
	printf("\n\n Factorial Tests:");
	intVal = 4;
	answer = factorial(intVal);
	printf("\n\t%d! = %f", intVal, answer);
 
	intVal = 13;
	answer = factorial(intVal);
	printf("\n\t%d! = %f", intVal, answer);
 
 
	//Power
	printf("\n\n Power Tests:");
	dblVal = 6.3;
	intVal = 3;
	answer = power(dblVal, intVal);
	printf("\n\t%f^(%d) = %f", dblVal, intVal, answer);
 
	dblVal += 6.3;
	intVal *= 3;
	answer = power(dblVal, intVal);
	printf("\n\t%f^(%d) = %f", dblVal, intVal, answer);
 
 
	//Sine
	printf("\n\n Sine Tests:");
	answer = sine(0);
	printf("\n\tsin(0) = %0.9f", answer);
 
	dblVal = M_PI;
	answer = sine(dblVal);
	printf("\n\tsin(PI) = %0.8f", answer);
 
	dblVal /= 3;
	answer = sine(dblVal);
	printf("\n\tsin(PI/3) = %0.8f", answer);
 
	dblVal *= .5;
	dblVal *= 7;
	answer = sine(dblVal);
	printf("\n\tsin(7PI/6) = %0.8f", answer);
 
	dblVal = M_PI_2;
	answer = sine(dblVal);
	printf("\n\tsin(PI/2) = %0.8f", answer);
 
	dblVal = M_PI_4;
	answer = sine(dblVal);
	printf("\n\tsin(PI/4) = %0.8f", answer);
	printf("\n\n");
return 0;
}


