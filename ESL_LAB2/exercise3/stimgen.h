#include <systemc.h>

SC_MODULE(stimgen)
{
  //sc_out <int> in1,in2;
  sc_port<sc_fifo_out_if<int> > in1,in2;
  int seed;
  void stim_proc();
  SC_CTOR(stimgen)
  {
    seed = 12;
    SC_THREAD(stim_proc);
  }
    
};