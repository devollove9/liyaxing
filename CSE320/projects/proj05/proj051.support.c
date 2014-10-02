/****************************************************************************
  Yaxing Li
  CSE 320
  Project #5
****************************************************************************/

#include <stdio.h>
#include "/user/cse320/Projects/project05.support.h"
unsigned getSign(unsigned const,unsigned const);
unsigned getExp(unsigned const,unsigned const);
unsigned getFrac(unsigned const,unsigned const);
unsigned Isnormed(unsigned const);

int main()
  {
    union sp_item num,num1,num2,num3,num4,num5,num6;
    signed true_exp;
    true_exp = ((num.irep >> 23) & 0xff) - 0x7f;
    num.frep=mult(-12324.5,-234.245);
    num1.frep=mult(NAN,234.5);
    num2.frep=mult(INFINITY,234.5);
    num3.frep=mult(0,234.5);
    num4.frep=mult(24.5,234.5);
    num5.frep=mult(1.5,-24.5);
    num6.frep=mult(+1.1754944e-38,+3.7500000e-01);
    
    printf( "Real: %f  Hex integer: %08x   \n", num.frep, num.irep );
    printf( "Real: %f  Hex integer: %08x   \n", num1.frep, num1.irep );
    printf( "Real: %f  Hex integer: %08x   \n", num2.frep, num2.irep );
    printf( "Real: %f  Hex integer: %08x   \n", num3.frep, num3.irep );
    printf( "Real: %f  Hex integer: %08x   \n", num4.frep, num4.irep );
    printf( "Real: %f  Hex integer: %08x   \n", num5.frep, num5.irep );
    printf( "Real: %f  Hex integer: %08x   \n", num6.frep, num6.irep );
    return 0;
  }


// function mult return float c=a*b
float mult( float a, float b)
{
    union sp_item A;A.frep=1.5;               //union A
    union sp_item B;B.frep=1.5;               //union B    
    
	printf( "Real: %f  Hex integer: %08x   \n", A.frep, A.irep );
	printf( "Real: %f  Hex integer: %08x   \n", B.frep, B.irep );
    if (A.frep==NAN) return NAN;            //special situations      
    else if (B.frep==NAN) return NAN;
    else if (A.frep==INFINITY) return INFINITY;
    else if (B.frep==INFINITY) return INFINITY;
    else if (A.frep==0x0) return (float)0;
    else if (B.frep==0x0) return (float)0;
    
    union sp_item C; unsigned signC,expC,fracC;    //returning float C significantC, exponentsC , fractionC
    signC=getSign(A.irep,B.irep);                  //function get the significant C
    expC=getExp(A.irep,B.irep);                    //function get the exponents C
    if (expC==0x0) return 0;                       //Number denormal if exponents are zeros 
    fracC=getFrac(A.irep,B.irep);                  //function get the fraction C
    
    C.irep= signC |(expC +  fracC);                //inserting 3 together
    
    //printf( "Real: %f  Hex integer: %08x  signC: %08x trueC: %08x fracC: %08x \n", C.frep, C.irep , signC,trueC,fracC);
    printf( "Real: %f  Hex integer: %08x   \n", C.frep, C.irep );
    return C.frep;
}

// function getSign, return sign(+) 00~~~0 if they have same signs, else return (-) 10~~~0 if different signs
unsigned getSign(unsigned const A ,unsigned const B)
{
    
    if (A>>31<<31 == B>>31<<31) return 0x0;
    else return ((0x80000000));
}

// function getExp, return exponents A - 0x3f8~~0 + exponents B get a new exponent
unsigned getExp(unsigned const A ,unsigned const B)
{ 
  
    return (A & 0x7f800000) -0x3f800000 + (B & 0x7f800000);    
}

// function getFrac, return fractions 
unsigned getFrac(unsigned const A ,unsigned const B)
{ 
    
    unsigned long AA= (A & 0x007fffff) |0x00800000;   //Add 1 before multiplication
    unsigned long BB= (B & 0x007fffff) |0x00800000;
   
    //printf( "_Real: %f  Hex integer: %016llx   \n", AA, AA );
    //printf( "_Real: %f  Hex integer: %016llx   \n", BB, BB );
    
    unsigned long long result;
    result= ((AA*BB));                                // multiply
    
    //printf( "_Result: %f  Result: %016llx   \n", result, result );
    unsigned  a=(result>>24) & 0xffffff;              //xfer 64 bits back to 32 bits
    unsigned n=Isnormed(a);                           //normalize the number
    a<<=n;                                            //if normalize happened subtract the exponent 
    n<<=23;
    //printf( "_n: %f  Result: %08x   \n", n, n );
    a -= n;
    //printf( "  a _Real: %f  Hex integer: %08x   \n", a, a);
    return  a;                                       //return the normalized unsigned a
}

//function normalize a number
unsigned Isnormed(unsigned const result)
{
    unsigned test=0x00800000,n=0;
    for(;;)
    {
        if ((result & test)== test) break;        //Break when find the most significant digit  
        test>>=1;                                 //shift one bit until we find 1
        n++;                                      //count the exponents
    }
    return n;
}