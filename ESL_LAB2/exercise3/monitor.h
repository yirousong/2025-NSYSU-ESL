#include <systemc.h>

SC_MODULE(monitor)
{
  //sc_out <int> re;
  sc_port<sc_fifo_in_if<int> > re;
  
  void monitor_proc();
  SC_CTOR(monitor)
  {
    SC_THREAD(monitor_proc);
  }
  
  
};