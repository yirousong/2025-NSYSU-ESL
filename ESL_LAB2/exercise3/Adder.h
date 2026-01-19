#include <systemc.h>

SC_MODULE(Adder)
{
  //sc_in <int> a;
  //sc_in <int> b;
  //sc_out <int> c;
  sc_port<sc_fifo_in_if<int> > a;
  sc_port<sc_fifo_in_if<int> > b;
  sc_port<sc_fifo_out_if<int> > c;
  
  void compute();
  SC_CTOR(Adder)
  {
    SC_THREAD(compute);
  }
   
};