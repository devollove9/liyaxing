
/******************************************************************************
  Lab Exercise #13 -- driver function
******************************************************************************/

#include <stdio.h>
#include <sys/time.h>

double sum_vector( double *, int, int *, int * );

int main()
{
  char fmt1[] = "\nVector contains %d negative values and %d positive values\n";
  char fmt2[] = "\nSum of vector elements:  %lf\n";
  char fmt3[] = "\nMean of vector elements:  %lf\n";
  char fmt4[] = "\nNanoseconds used by code segment: %lld\n\n";

  double vec[] = { 25.4, -4.7, 3.3, 1.25, -96.2, -8.6, 1.2, 100.4 };

  int N = sizeof( vec ) / sizeof( vec[0] );


  double sum = 0.0;
  double mean = 0.0;

  int num_neg = 0;
  int num_pos = 0;

  hrtime_t time1, time2, elapsed;

  int i;

  time1 = gethrtime();

  for (i=0; i<500000; i++)
  {
    num_neg = 0;
    num_pos = 0;

    sum = sum_vector( &vec[0], N, &num_neg, &num_pos );

    mean = sum / (double) N;
  }

  time2 = gethrtime();

  elapsed = time2 - time1;

  printf( fmt1, num_neg, num_pos );
  printf( fmt2, sum );
  printf( fmt3, mean );
  printf( fmt4, elapsed );

  return 0;
}

