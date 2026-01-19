#include <systemc.h>
#include <systemc.h>
#include <iostream>
#include <stdlib.h>
SC_MODULE(shift_reg)
{
  sc_in_clk iclk;
  sc_signal<int> data_in;
  sc_signal<int> Q1;
  sc_signal<int> Q2;
  sc_signal<int> Q3;
  
  SC_CTOR(shift_reg)
  {
    SC_CTHREAD(sync_shift_reg,iclk.pos());
    data_in=0;
    Q1=0;
    Q2=0;
    Q3=0;
  }
  void sync_shift_reg()
  {
    for(;;)
      {
        data_in=rand()%100;
        Q1=data_in;
        Q2=Q1;
        Q3=Q2;
        wait(SC_ZERO_TIME);
        cout<<"At time "<<sc_time_stamp()<<" Q1: "<<Q1<<" Q2: "<<Q2<<" Q3:"
        <<Q3<<endl;   
      }
  }
};

int sc_main(int argc, char *argv[])
{
  const sc_time t_PERIOD(20,SC_NS);
  
  sc_clock clk("clk",t_PERIOD);
  shift_reg ishift_reg("ishift_reg");
  ishift_reg.iclk(clk);
  
  sc_start(200,SC_NS);
  
  return 0;
}