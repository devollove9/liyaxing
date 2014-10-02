
/******************************************************************************
  CSE320
  Name:Yaxing Li
  PID :A41898556
  Project #2 skeleton
******************************************************************************/

#include <Sim.h>

void circuits( SD, Signal, Signal, Signal, Signal, 
  Signal, Signal, Signal, Signal, Signal, Signal, Signal, Signal );


/******************************************************************************
  Function "simnet"   -- test bed for student circuits
******************************************************************************/

void simnet()
{
  Signal w, x, y, z, Present, a, b, c, d, e, f, g;
  Signal Strobe (1);   // Counter strobe input
  Signal ResetA (1);   // Counter reset signal (before complemented)
  Signal ResetB (1);   // Counter reset signal (after complemented)
 
  

  Probe ((SD("1a"),"w"), w);         // Switch w controlled by 'w' key
  Probe ((SD("2a"),"x"), x);         // Switch x controlled by 'x' key
  Probe ((SD("3a"),"y"), y);         // Switch y controlled by 'y' key
  Probe ((SD("4a"),"z"), z);         // Switch z controlled by 'z' key
  
  // A pulser is used to generate a temporary value of "One" on a specified
  // signal line (signal value:  Zero ==> One ==> Zero)

  Pulser ((SD("5a"), "r -- Reset counter"),  ResetA, 'r', 10);
  Pulser ((SD("6a"), "s -- Strobe counter"), Strobe, 's', 10);

  // Complement the reset signal (counter reset is active low)
  Not (SD("4b"), ResetA, ResetB);
  
  Counter ((SD("1c-4c"), "4-bit counter"), (ResetB, Strobe), (w,x,y,z));
  
// Code to generate four input signals*/
  circuits( SD("1d-4d"), w, x, y, z, Present, a, b, c, d, e, f, g);

  // Code to display eight output signals
  

  Probe((SD("1f"),"present"),Present);
  Probe((SD("2f"),"a"),a);
  Probe((SD("3g"),"b"),b);
  Probe((SD("5g"),"c"),c);
  Probe((SD("6f"),"d"),d);
  Probe((SD("5e"),"e"),e);
  Probe((SD("3e"),"f"),f);
  Probe((SD("4f"),"g"),g);     
}


/******************************************************************************
  Function "circuits" -- implementation of student circuits

  Do not alter the interface -- function "circuits" must receive four
  signals as inputs and return eight signals as outputs.
******************************************************************************/

void circuits( SD sd, Signal w, Signal x, Signal y, Signal z, 
  Signal Present, Signal a, Signal b, Signal c, Signal d, Signal e,
  Signal f, Signal g )    
{
  Module( (sd, "circuits"), (w, x, y, z), (Present, a, b, c, d, e, f, g) );

  // Declarations for any auxiliary Signals
  Signal notw,notx,noty,notz;
  Signal P1,P2,P3,P4;
  Signal a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,f1,f2,g1,g2;
  
  // Circuit implementation (Not, And, Or gates)
  Not ( SD(sd,"1b"), w, notw );         // Switch w controlled by 'w' key
  Not ( SD(sd,"2b"), x, notx );         // Switch x controlled by 'x' key
  Not ( SD(sd,"3b"), y, noty );         // Switch y controlled by 'y' key
  Not ( SD(sd,"4b"), z, notz );         // Switch z controlled by 'z' key
  
  And (SD(sd,"1c"),(notw,noty,z),P1);
  And (SD(sd,"2c"),(notw,x,notz),P2);
  And (SD(sd,"3c"),(w,notx,noty),P3);
  And (SD(sd,"4c"),(w,notx,y,notz),P4);
  
  And (SD(sd,"5c"),(notw,x,noty,z),a1);
  And (SD(sd,"6c"),(notw,x,y,notz),a2);
  And (SD(sd,"7c"),(w,notx),a3);

  And (SD(sd,"8c"),(notw,x,noty,notz),b1);
  And (SD(sd,"9c"),(notw,notx,noty,z),b2);
  And (SD(sd,"0c"),(w,notx),b3);
  
  And (SD(sd,"1d"),(notw,x),c1);
  And (SD(sd,"2d"),(w,notx),c2);
  And (SD(sd,"3d"),(noty,z),c3);

  And (SD(sd,"4d"),(w,notx,noty),d1);
  And (SD(sd,"5d"),(notw,x,noty,z),d2);
  And (SD(sd,"6d"),(notw,x,y,notz),d3);

  And (SD(sd,"7d"),(notw,x,y,notz),e1);
  And (SD(sd,"8d"),(w,notx,notz),e2);

  And (SD(sd,"9d"),(notw,x),f1);
  And (SD(sd,"0d"),(w,notx),f2);
  
  And (SD(sd,"5a"),(notw,x),g1);
  And (SD(sd,"6a"),(w,notx),g2);
  
  Or ( SD(sd,"1e"), (P1,P2,P3,P4), Present ); // OR gate
  Or ( SD(sd,"2e"), (a1,a2,a3), a );
  Or ( SD(sd,"3e"), (b1,b2,b3), b );
  Or ( SD(sd,"4e"), (c1,c2,c3), c );
  Or ( SD(sd,"5e"), (d1,d2,d3), d );
  Or ( SD(sd,"6e"), (e1,e2), e );
  Or ( SD(sd,"7e"), (f1,f2), f );
  Or ( SD(sd,"8e"), (g1,g2), g );
   
}


