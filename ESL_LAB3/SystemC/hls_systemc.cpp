#define SC_INCLUDE_FX
#include "systemc.h"

SC_MODULE(rgb2yuv)
{
    sc_in<bool> clk;
    sc_in<bool> rst;

    sc_in<sc_fixed<9, 9, SC_RND, SC_SAT>> R;
    sc_in<sc_fixed<9, 9, SC_RND, SC_SAT>> G;
    sc_in<sc_fixed<9, 9, SC_RND, SC_SAT>> B;

    sc_out<sc_fixed<9, 9, SC_RND, SC_SAT>> Y;
    sc_out<sc_fixed<9, 9, SC_RND, SC_SAT>> U;
    sc_out<sc_fixed<9, 9, SC_RND, SC_SAT>> V;

    void process()
    {
        wait();

        while (true)
        {
            if (rst.read() == 0)
            {
                Y.write(0);
                U.write(0);
                V.write(0);
            }
            else
            {
                Y.write(sc_fixed<8, 2>(0.299) * R.read() + sc_fixed<8, 2>(0.587) * G.read() + sc_fixed<8, 2>(0.114) * B.read());
                U.write(128 + sc_fixed<8, 2>(-0.169) * R.read() + sc_fixed<8, 2>(-0.331) * G.read() + sc_fixed<8, 2>(0.5) * B.read());
                V.write(128 + sc_fixed<8, 2>(0.5) * R.read() + sc_fixed<8, 2>(-0.419) * G.read() + sc_fixed<8, 2>(-0.081) * B.read());
            }
            wait();
        }
    }

    SC_CTOR(rgb2yuv)
    {
        SC_CTHREAD(process, clk.pos());
    }
};
