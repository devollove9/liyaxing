
/******************************************************************************
  Project #3 skeleton
******************************************************************************/

#include <Sim.h>

void circuits( SD, Signal, Signal, Signal, Signal, Signal, Signal );


/******************************************************************************
  Function "simnet"   -- test bed for student circuits
******************************************************************************/

void simnet()
{
  Signal Init, Clock, w, x, y, z;

  // Insert your Pulsers here
  Pulser ((SD("5a"), "r -- Reset counter"),  Init, 'i', 10);
  Pulser ((SD("6a"), "s -- Strobe counter"), Clock, 'c', 10);

  circuits( SD("1b-4b"), Init, Clock, w, x, y, z );

  // Insert your Probes here
  Probe ((SD("1a"),"w"), w);         // Switch w controlled by 'w' key
  Probe ((SD("2a"),"x"), x);         // Switch x controlled by 'x' key
  Probe ((SD("3a"),"y"), y);         // Switch y controlled by 'y' key
  Probe ((SD("4a"),"z"), z);         // Switch z controlled by 'z' key
}


/******************************************************************************
  Function "circuits" -- implementation of student circuits
******************************************************************************/

void circuits( SD sd, Signal Init, Signal Clock, 
  Signal w, Signal x, Signal y, Signal z )
{
  Module( (sd, "circuits"), (Init, Clock), (w, x, y, z) );

  // Insert your declarations for any auxiliary Signals here
	Signal notw,notx,noty,notz;
  // Insert your DFFs here
   
  // Insert your combinational logic here (Not, And, Or gates)
  Not ( SD(sd,"1b"), w, notw );         // Switch w controlled by 'w' key
  Not ( SD(sd,"2b"), x, notx );         // Switch x controlled by 'x' key
  Not ( SD(sd,"3b"), y, noty );         // Switch y controlled by 'y' key
  Not ( SD(sd,"4b"), z, notz );         // Switch z controlled by 'z' key
}

