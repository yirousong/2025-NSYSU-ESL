#include "Adder.h"


void Adder::compute()
{
  while(true)
  {
    c-> write( a->read() + b->read());
    c-> write( a->read() + b->read()+2);
  }
}