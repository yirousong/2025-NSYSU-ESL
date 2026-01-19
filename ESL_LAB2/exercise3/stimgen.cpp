#include "stimgen.h"

void stimgen::stim_proc()
{
  int temp;
  for(int i=0; i<20; i++)
  {
    temp = seed+1;
    in1 ->write(temp);
    in2 ->write(temp+5);
    seed = (seed+19)%123;
  }
  sc_stop;
}