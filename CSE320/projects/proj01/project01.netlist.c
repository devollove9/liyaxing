
/******************************************************************************
  Project #1 skeleton
******************************************************************************/

#include <Sim.h>

void circuits( SD, Signal, Signal, Signal, Signal, 
  Signal, Signal, Signal, Signal );


/******************************************************************************
  Function "simnet"   -- test bed for student circuits
******************************************************************************/

void simnet()
{
  Signal w, x, y, z, Valid, Present, Even, Prime;

  // Insert your Switches here

  circuits( SD("1b-4b"), w, x, y, z, Valid, Present, Even, Prime );

  // Insert your Probes here
}


/******************************************************************************
  Function "circuits" -- implementation of student circuits
******************************************************************************/

void circuits( SD sd, Signal w, Signal x, Signal y, Signal z, 
  Signal Valid, Signal Present, Signal Even, Signal Prime )    
{
  Module( (sd, "circuits"), (w, x, y, z), (Valid, Present, Even, Prime) );

  // Insert your declarations for any auxiliary Signals here

  // Insert your circuit implementation here (Not, And, Or gates)
}

