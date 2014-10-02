
#include <math.h>

#define NAN       (__builtin_nan(""))
#define INFINITY  (__builtin_inf())

int is_negative( double );    /* Test if argument is negative */
int is_zero( double );        /* Test if argument is zero */
int is_denormal( double );    /* Test if argument is denormal */
int is_nan( double );         /* Test if argument is NaN */
int is_infinite( double );    /* Test if argument is infinite */
int is_finite( double );      /* Test if argument is finite */

double negate( double );      /* Return negation of argument */
double absolute( double );    /* Return absolute value of argument */

void display( double );       /* Display fields of argument */

union dp_item
{
  double drep;
  unsigned long long int irep;
};

