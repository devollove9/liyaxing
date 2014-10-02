
/******************************************************************************
  Lab Exercise #12, Part B -- driver module
 
  Find the roots of a quadratic equation.

  Equation: A*X*X + B*X + C = 0
******************************************************************************/ 

#include <stdio.h>
#include <math.h>

void real_roots( double *, double *, double *, double *, double * );

int main()
{
  int flag;
  double A, B, C, Disc, Root1, Root2;

  for (;;)
  {
    printf( "\nPlease enter the values for A, B and C (ctrl-d to exit):\n" );

    flag = scanf( "%lf%lf%lf", &A, &B, &C );

    printf( "\n" );

    if (flag == EOF) break;

    if (A == 0.0 && B == 0.0)
    {
      printf( "The equation is degenerate and has no roots.\n" );
    }
    else if (A == 0.0)
    {
      printf( "The equation has a single root (%lf).\n", -C/B );
    }
    else
    {
      Disc = B*B - 4*A*C;
      if (Disc >= 0.0)
      {
        real_roots( &A, &B, &Disc, &Root1, &Root2 );
        printf( "The equation has two real roots (%lf and %lf).\n",
          Root1, Root2 );
      }
      else
      {
        printf( "Both roots are complex numbers.\n" );
      }
    }
  }

  return 0;
}

