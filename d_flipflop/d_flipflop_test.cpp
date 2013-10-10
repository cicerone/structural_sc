/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */

#include "../common/d_flipflop.h"


/*
SC_MODULE(TestGenerator)
{
    sc_out<bool> d_out;
    sc_in<bool>  clk;
    
    void GenerateSignals()
    {
        while(1)
        {
            d_out.write(false);
            wait();
            d_out.write(false);
            wait();
            d_out.write(true);
            wait();
            d_out.write(true);
            wait();
        }
    }
    
    SC_CTOR(TestGenerator)
    {
        SC_CTHREAD(GenerateSignals, clk.pos());
    }
};
*/

SC_MODULE(TestGenerator)
{
    sc_out<bool> d_out;
    sc_in<bool>  clk;
    
    void GenerateSignals()
    {
        while(1)
        {
            d_out.write(false);
            wait(9, SC_NS);
            d_out.write(true);
            wait(1, SC_NS);
            d_out.write(false);
            wait(2, SC_NS);
            d_out.write(true);
            wait(3, SC_NS);
            d_out.write(false);
            wait(2, SC_NS);
            d_out.write(true);
            wait(5, SC_NS);
            d_out.write(true);
            wait(10, SC_NS);
        }
    }
    
    SC_CTOR(TestGenerator)
    {
        SC_THREAD(GenerateSignals);
    }
};

int sc_main(int argc, char* argv[])
{
    sc_signal<bool> d_sig;
    sc_clock clk_sig("TestClock", 10, SC_NS, 0.5);

    TestGenerator tg("test_generator");
    tg.d_out(d_sig);
    tg.clk(clk_sig);

    DFlipFlop DUT("DFlipFlop");
    DUT.clk_in(clk_sig);
    DUT.d_in(d_sig);

    sc_trace_file* p_trace_file;
    p_trace_file = sc_create_vcd_trace_file("traces");
    sc_trace(p_trace_file, d_sig  , "d" );
    sc_trace(p_trace_file, clk_sig  , "clk" );
    sc_trace(p_trace_file, DUT.slatch1.q_internal_sig  , "q" );
    sc_trace(p_trace_file, DUT.slatch1.qn_internal_sig  , "qn" );

    sc_start(170, SC_NS); 
    sc_close_vcd_trace_file(p_trace_file);

    return 0;
}




