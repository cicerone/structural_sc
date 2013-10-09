/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */

#include "../common/nand.cpp"
#include "../common/sr_latch.cpp"



SC_MODULE(TestGenerator)
{
    sc_out<bool> s_out, r_out;
    sc_in<bool>  clk;
    
    void GenerateSignals()
    {
        while(1)
        {
            s_out.write(false);
            r_out.write(false);
            wait();
            s_out.write(false);
            r_out.write(true);
            wait();
            s_out.write(true);
            r_out.write(false);
            wait();
            s_out.write(true);
            r_out.write(true);
            wait();
        }
    }
    
    SC_CTOR(TestGenerator)
    {
        SC_CTHREAD(GenerateSignals, clk.pos());
    }
};


int sc_main(int argc, char* argv[])
{
    sc_signal<bool> s_sig, r_sig, q_sig, qn_sig;
    sc_clock clk_sig("TestClock", 10, SC_NS, 0.5);

    TestGenerator tg("test_generator");
    tg.s_out(s_sig);
    tg.r_out(r_sig);
    tg.clk(clk_sig);

    SRLatch DUT("SRLatch");
    DUT.clk_in(clk_sig);
    DUT.set_in(s_sig);
    DUT.reset_in(r_sig);
   // DUT.q_out(q_sig);
   // DUT.qn_out(qn_sig);

    sc_trace_file* p_trace_file;
    p_trace_file = sc_create_vcd_trace_file("traces");
    sc_trace(p_trace_file, s_sig  , "set" );
    sc_trace(p_trace_file, r_sig  , "reset" );
    sc_trace(p_trace_file, q_sig  , "q" );
    sc_trace(p_trace_file, qn_sig  , "qn" );
    sc_trace(p_trace_file, clk_sig  , "clk" );
    sc_trace(p_trace_file, DUT.a_sig  , "a" );
    sc_trace(p_trace_file, DUT.b_sig  , "b" );
    sc_trace(p_trace_file, DUT.q_internal_sig  , "q_int" );
    sc_trace(p_trace_file, DUT.qn_internal_sig  , "qn_int" );

    sc_start(70, SC_NS); 
    sc_close_vcd_trace_file(p_trace_file);

    return 0;
}




