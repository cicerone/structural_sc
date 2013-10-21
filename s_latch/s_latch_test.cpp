/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */

#include "../common/s_latch.h"


/*
SC_MODULE(TestGenerator)
{
    sc_out<bool> s_out;
    sc_in<bool>  clk;
    
    void GenerateSignals()
    {
        while(1)
        {
            s_out.write(false);
            wait();
            s_out.write(false);
            wait();
            s_out.write(true);
            wait();
            s_out.write(true);
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
    sc_out<bool> s_out;
    sc_in<bool>  clk;
    
    void GenerateSignals()
    {
        while(1)
        {
            s_out.write(false);
            wait(10, SC_NS);
            s_out.write(true);
            wait(1, SC_NS);
            s_out.write(false);
            wait(2, SC_NS);
            s_out.write(true);
            wait(3, SC_NS);
            s_out.write(false);
            wait(2, SC_NS);
            s_out.write(true);
            wait(5, SC_NS);
            s_out.write(true);
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
    sc_signal<bool> s_sig;
    sc_signal<bool> q_sig, qn_sig;
    sc_clock clk_sig("TestClock", 10, SC_NS, 0.5);

    TestGenerator tg("test_generator");
    tg.s_out(s_sig);
    tg.clk(clk_sig);

#define TEST_S_LATCH_V0

#ifdef TEST_S_LATCH_V0
    SLatchV0 DUT("SLatch");
#endif
    DUT.clk_in(clk_sig);
    DUT.set_in(s_sig);
#ifndef TEST_S_LATCH_V0
    DUT.q_out(q_sig);
    DUT.qn_out(qn_sig);
#endif

    sc_trace_file* p_trace_file;
    p_trace_file = sc_create_vcd_trace_file("traces");
    sc_trace(p_trace_file, s_sig  , "set" );
    sc_trace(p_trace_file, DUT.reset_sig  , "reset" );
    sc_trace(p_trace_file, clk_sig  , "clk" );
    sc_trace(p_trace_file, DUT.a_sig  , "a" );
    sc_trace(p_trace_file, DUT.b_sig  , "b" );
    sc_trace(p_trace_file, DUT.q_internal_sig  , "q_internal_sig" );
    sc_trace(p_trace_file, DUT.qn_internal_sig  , "qn_internal_sig" );
#ifndef TEST_S_LATCH_V0
    sc_trace(p_trace_file, q_sig  , "q_sig" );
    sc_trace(p_trace_file, qn_sig  , "qn_sig" );
#endif

    sc_start(70, SC_NS); 
    sc_close_vcd_trace_file(p_trace_file);

    return 0;
}




