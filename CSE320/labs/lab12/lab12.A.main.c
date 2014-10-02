
/******************************************************************************
  Lab Exercise #12, Part A -- driver module
******************************************************************************/

#include <stdio.h>

double sum_vector( double *, int, int *, int * );

int main()
{
  char fmt1[] = "\nSize of array: %d bytes\n";
  char fmt2[] = "\nSize of one array element: %d bytes\n";
  char fmt3[] = "\nArray contains %d negative values and %d positive values\n";
  char fmt4[] = "\nSum of array elements:  %lf\n";
  char fmt5[] = "\nMean of array elements:  %lf\n\n";

  double vec[] = { 25.4, -4.7, 3.3, 1.25, -96.2, -8.6, 1.2, 100.4, 5.0, -2.6 };

  int N = sizeof( vec ) / sizeof( vec[0] );

  double sum = 0.0;
  double mean = 0.0;

  int num_neg = 0;
  int num_pos = 0;

  sum = sum_vector( &vec[0], N, &num_neg, &num_pos );

  mean = sum / (double) N;

  printf( fmt1, sizeof( vec ) );
  printf( fmt2, sizeof( vec[0] ) );
  printf( fmt3, num_neg, num_pos );
  printf( fmt4, sum );
  printf( fmt5, mean );

  return 0;
}

