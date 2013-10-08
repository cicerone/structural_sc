/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */

//#include "systemc.h"
#include "../common/nand.cpp"

/*
SC_MODULE(Nand2)                   // declare Nand2 sc_module
{
    sc_in<bool> in1_in, in2_in;    // input signal ports
    sc_out<bool> Out_out;          // output signal ports
    
    void ComputeNand()      
    {
        Out_out.write( !(in1_in.read() && in2_in.read()) );
    }
    
    SC_CTOR(Nand2)                      // constructor for Nand2
    {
        SC_METHOD(ComputeNand);         // register do_nand2 with kernel
        sensitive << in1_in << in2_in;  // sensitivity list
    }
};
*/

SC_MODULE(TestGenerator)
{
    sc_out<bool> in1_out, in2_out;
    sc_in<bool>  clk;
    
    void GenerateSignals()
    {
        while(1)
        {
            in1_out.write(false);
            in2_out.write(false);
            wait();
            in1_out.write(false);
            in2_out.write(true);
            wait();
            in1_out.write(true);
            in2_out.write(false);
            wait();
            in1_out.write(true);
            in2_out.write(true);
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
    sc_signal<bool> in1_sig, in2_sig, out_sig;
    sc_clock clk_sig("TestClock", 10, SC_NS,0.5);

    TestGenerator tg("test_generator");
    tg.in1_out(in1_sig);
    tg.in2_out(in2_sig);
    tg.clk(clk_sig);

    Nand2 DUT("NAND2");
    DUT.in1_in(in1_sig);
    DUT.in2_in(in2_sig);
    DUT.Out_out(out_sig);

    sc_trace_file* p_trace_file;
    p_trace_file = sc_create_vcd_trace_file("traces");
    sc_trace(p_trace_file, in1_sig  , "in1" );
    sc_trace(p_trace_file, in2_sig  , "in2" );
    sc_trace(p_trace_file, out_sig  , "out" );
    sc_trace(p_trace_file, clk_sig  , "clk" );

    sc_start(70, SC_NS); 
    sc_close_vcd_trace_file(p_trace_file);

    return 0;
}




