#include <systemc.h>
#include <iostream>
#include <stdlib.h>
SC_MODULE(consumer)
{
  sc_in_clk iclk;
  sc_fifo_in<int> data_in;
  int data_value;
  SC_CTOR(consumer)
  {
  SC_CTHREAD(x_consumer,iclk.pos());
  data_value=0;
  }
  void x_consumer()
  {
  for(;;){
    wait(3);
    data_value=data_in.read();
    cout<<"At time"<<sc_time_stamp()<<
    "consume data"<<data_value<<endl;
    }
  }
};
SC_MODULE(producer)
{
  sc_in_clk iclk;
  sc_fifo_out<int> data_out;
  int data_value;
  SC_CTOR(producer)
  {
  SC_CTHREAD(x_producer,iclk.pos());
  data_value=0;
  }
  void x_producer()
  {
    for(;;){
    wait(2);
    data_value=rand()%100;
    data_out.write(data_value);
    cout<< "At time"<<sc_time_stamp()<<
    "produces data"<<data_value<<endl;
    }
  }
};
int sc_main(int argc, char *argv[])
{
  const sc_time t_PERIOD(10,SC_NS);
  sc_clock clk("clk",t_PERIOD);
  sc_fifo<int> x_fifo;
  producer x_producer("x_producer");
  consumer x_consumer("x_consumer");
  x_producer.iclk(clk);
  x_consumer.iclk(clk);
  x_producer.data_out(x_fifo);
  x_consumer.data_in(x_fifo);
  sc_start(200,SC_NS);
  return 0;
}
