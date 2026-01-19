#include <systemc.h>
#include "Adder.h"
#include "stimgen.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	//sc_signal<int> sig_a,sig_b,sig_c;
	sc_fifo<int> sig_a(10), sig_b(10),sig_c(10);

	Adder my_adder("my_adder"); 
  stimgen stim("stim");
  
  stim(sig_a,sig_b);
  my_adder(sig_a,sig_b,sig_c);
	
  monitor mon("mon");
  mon.re(sig_c);
  
	sc_start();
	return 0;
}
