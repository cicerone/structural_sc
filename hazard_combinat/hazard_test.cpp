/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */

#include "../common/nand.h"


SC_MODULE(TestGenerator)
{
    sc_out<bool> in1_out, in2_out, in3_out;
    sc_in<bool>  clk;
    
    void GenerateSignals()
    {
        while(1)
        {
            in1_out.write(true);
            in2_out.write(false);
            in3_out.write(true);
            wait();
            in1_out.write(true);
            in2_out.write(false);
            in3_out.write(true);
            wait();
            in1_out.write(true);
            in2_out.write(true);
            in3_out.write(true);
            wait();
            in1_out.write(true);
            in2_out.write(true);
            in3_out.write(true);
            wait();
            in1_out.write(true);
            in2_out.write(false);
            in3_out.write(true);
            wait();
            in1_out.write(true);
            in2_out.write(false);
            in3_out.write(true);
            wait();
            in1_out.write(true);
            in2_out.write(true);
            in3_out.write(true);
            wait();
            in1_out.write(true);
            in2_out.write(true);
            in3_out.write(true);
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
    sc_signal<bool> in1_sig, in2_sig, in3_sig, out_sig;
    sc_signal<bool> a_sig, b_sig, c_sig;
    sc_clock clk_sig("TestClock", 10, SC_NS,0.5);

    TestGenerator tg("test_generator");
    tg.in1_out(in1_sig);
    tg.in2_out(in2_sig);
    tg.in3_out(in3_sig);
    tg.clk(clk_sig);

    Nand2WithDelay u1("u1"); 
    Nand2WithDelay u2("u2"); 
    Nand2WithDelay u3("u3"); 
    Nand2WithDelay u4("u4"); 

    u1.in1(in1_sig);
    u1.in2(a_sig);
    u1.out(b_sig);

    u2.in1(in2_sig);
    u2.in2(in2_sig);
    u2.out(a_sig);

    u3.in1(in2_sig);
    u3.in2(in3_sig);
    u3.out(c_sig);

    u4.in1(b_sig);
    u4.in2(c_sig);
    u4.out(out_sig);

    sc_trace_file* p_trace_file;
    p_trace_file = sc_create_vcd_trace_file("traces");
    sc_trace(p_trace_file, in1_sig  , "in1" );
    sc_trace(p_trace_file, in2_sig  , "in2" );
    sc_trace(p_trace_file, in3_sig  , "in3" );
    sc_trace(p_trace_file, out_sig  , "out" );
    sc_trace(p_trace_file, clk_sig  , "clk" );
    sc_trace(p_trace_file, a_sig  , "a" );
    sc_trace(p_trace_file, b_sig  , "b" );
    sc_trace(p_trace_file, c_sig  , "c" );

    sc_start(100, SC_NS); 
    sc_close_vcd_trace_file(p_trace_file);

    return 0;
}




