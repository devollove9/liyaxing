
/******************************************************************************
  Lab Exercise #6 -- display attributes of signed integer values
******************************************************************************/

#include <stdio.h>

/*-----------------------------------------------------------------------------
   Name:  main

   Purpose:   Display selected attributes of signed decimal integer values
	      entered by the user.

   Outputs:   External representation of value in base 10
              Internal representation as hexadecimal
              Internal representation as binary
              Message -- positive or negative
              Message -- odd or even
              Message -- multiple of eight or not

   Comments:  The external representation in base 10 can be displayed using
	      "printf" and the "%+d" formatting specification.

	      The internal representation as hexadecimal can be displayed
	      using "printf" and the "%08x" formatting specification.

	      The internal representation as binary can be displayed using
	      "printf", "bit32" and the "%s" formatting specification.

              The three messages can be displayed using selective control
              constructs and "printf".

              The tests for the three messages will be performed using only
              bitwise operations (no arithmetic operations).
-----------------------------------------------------------------------------*/

int main()
{
  int value, flag;

  printf( "\nAt the prompt, please enter a signed decimal integer value\n" );
  printf( "(touch 'ctrl-d' to exit).\n" );

  for (;;)
  {
    printf( "\nNext value: " );

    flag = scanf( "%d", &value );

    if (flag == EOF) break;

    printf( "\nAttributes of value:\n\n" );
    printf( "  Decimal equivalent: %+d\n", value );
  }
  printf( "\n" );

  return 0;
}

