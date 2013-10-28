/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */

#include "../common/t_flipflop.h"



SC_MODULE(TestGenerator)
{
    sc_out<bool> d_out, reset_out;
    sc_in<bool>  clk;
    unsigned cntr;
    
    void GenerateSignals()
    {
        cntr = 0;
        reset_out.write(true);
        d_out.write(false);
        wait(3, SC_NS);
        d_out.write(true);
        wait(2, SC_NS);
        d_out.write(false);
        wait(5, SC_NS);
        while(1)
        {
            cntr++;
            if (cntr == 15 || cntr == 16) {
                reset_out.write(false);
            }
            else {
                reset_out.write(true);
            }
            d_out.write(true);
            wait(10, SC_NS);
            d_out.write(false);
            wait(10, SC_NS);
        }
    }
    
    SC_CTOR(TestGenerator)
    {
        SC_THREAD(GenerateSignals);
    }
};


class Top : public sc_core::sc_module
{
public:
    sc_signal<bool> d_sig, reset_sig, q_sig, qn_sig, q_int_sig, qn_int_sig;
    sc_clock clk_sig;
    TestGenerator tg;
    TFlipFlopR DUT;

public:
    SC_CTOR(Top) : clk_sig("TestClock", 10, SC_NS, 0.5, 1, SC_NS, true),
                   tg("test_generator"), DUT("DUT")
    {
        tg.d_out(d_sig);
        tg.clk(clk_sig);
        tg.reset_out(reset_sig);

        DUT.clk_in(clk_sig);
        DUT.d_in(d_sig);

        DUT.q_out(q_sig);
        DUT.qn_out(qn_sig);
        DUT.reset_in(reset_sig);
        cout << "Test flipflop reset" << endl;
    }
};


int sc_main(int argc, char* argv[])
{

    Top top("top");
    sc_trace_file* p_trace_file;
    p_trace_file = sc_create_vcd_trace_file("traces");
    sc_trace(p_trace_file, top.d_sig  , "d" );
    sc_trace(p_trace_file, top.clk_sig  , "clk" );
    sc_trace(p_trace_file, top.reset_sig  , "reset");
    sc_trace(p_trace_file, top.qn_sig  , "qn");
    sc_trace(p_trace_file, top.q_sig  , "q");

    sc_start(1700, SC_NS); 
    sc_close_vcd_trace_file(p_trace_file);

    return 0;
}




