
#include <stdio.h>
#include <string.h>
#include "/user/cse320/Projects/project06.support.h"
union D
{
    int inte;
    unsigned unsign;
};
int main()
{
    union D D;
    char destination[40];
    decode(0x02800005   ,destination);
    D.unsign=0x5;
    printf ("\nD.inte: %d   D.unsign: %08x    \n",D.inte,D.unsign);
}

void decode(unsigned A, char destination[])
{
    unsigned OP  =(A>>30) & 0x00000003;
    unsigned OP2 =(A>>22) & 0x00000007;
    unsigned OP3 =(A>>19) & 0x0000003f;
    unsigned cond=(A>>25) & 0x0000000f;
    unsigned rd  =(A>>25) & 0x0000001f;
    unsigned rs1 =(A>>14) & 0x0000001f;
    unsigned rs2 = A      & 0x0000001f;
    unsigned i   =(A>>13) & 0x00000001;
    unsigned simm13 = A   & 0x00001fff;
    printf ("OP: %08x   OP2: %08x    OP3: %08x \n",OP,OP2,OP3);
    printf ("rs1: %08x   rs2: %08x    rd: %08x \n",rs1,rs2,rd);
    printf ("cond: %08x   i: %08x    simm13: %08x \n",cond,i,simm13);
    if(OP==0x00000003)
    {
        printf(" OP is 11 Memory Formats\n");
        if (OP3 == 0x00000004){printf(" op3 is 000100 st");}
        else if (OP3 == 0x0){printf(" op3 is 000000 ld");}
    }
    else if (OP==0x00000002) 
    {
        printf(" OP is 10 Arithmetic Formats\n");
        if (OP3 == 0x00000010){printf(" op3 is 010000 addcc");}
        else if (OP3 == 0x00000011){printf(" op3 is 010001 andcc");}
        else if (OP3 == 0x00000012){printf(" op3 is 010010 orcc");}
        else if (OP3 == 0x00000016){printf(" op3 is 010110 orncc");}
        else if (OP3 == 0x00000026){printf(" op3 is 100110 srl");}
        else if (OP3 == 0x00000038){printf(" op3 is 111000 jmpl");}
        else {printf(" Not taking care in this project");}
    }
    else if  (OP==0x00000001)
    {
        printf(" OP is 01 Call Formats");
    }
    else if (OP==0x00000000)
    {
        if (OP2==0x00000004) {printf(" OP2 is 100 Sethi Formats \n");}
        else if (OP2==0x00000002) 
        {
            printf(" OP2 is 010 Branch Formats\n");
            if (cond == 0x00000001){printf(" cond is 0001 be");}
            else if (cond == 0x00000005){printf(" cond is 0101 bcs");}
            else if (cond == 0x00000006){printf(" cond is 0110 bneg");}
            else if (cond == 0x00000007){printf(" cond is 0111 bvs");}
            else if (cond == 0x00000008){printf(" cond is 1000 ba");}
            else {printf(" Not taking care in this project");}
        }
        else {printf(" Not taking care in this project");}
    }    
}