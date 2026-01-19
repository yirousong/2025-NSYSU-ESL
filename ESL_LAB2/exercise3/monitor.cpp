#include "monitor.h"


void monitor::monitor_proc()
{
  while(true)
  {
    cout<<"The result of the computation is = "<<re->read()<<endl;
  }
}