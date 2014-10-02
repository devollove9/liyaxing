
int is_negative( double );         /* Test if argument is negative */
int is_zero( double );             /* Test if argument is zero */
int is_denormal( double );         /* Test if argument is denormal */
int is_nan( double );              /* Test if argument is NaN */
int is_infinite( double );         /* Test if argument is infinite */
int is_finite( double );           /* Test if argument is finite */

void negate( double, double* );    /* Return negation of argument */
void absolute( double, double* );  /* Return absolute value of argument */

void display( double );            /* Classify argument */

union dp_item
{
  double drep;
  unsigned long long int irep;
};

