/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */


#ifndef __DFLIPFLOP_H__
#define __DFLIPFLOP_H__


#include "s_latch.h"


SC_MODULE(DFlipFlopFast)              
{
    sc_in<bool> d_in, clk_in; 
    sc_signal<bool> clkn_sig; 
    
    Nand2WithDelay u1;
    SLatchV0 slatch0, slatch1;

    SC_CTOR(DFlipFlopFast) : u1("u1"), slatch0("slatch0"), slatch1("slatch1"),  
                             clkn_sig("clkn_sig"), d_in("d_in"), clk_in("clk_in")
    {
        u1.in1(clk_in);
        u1.in2(clk_in);
        u1.out(clkn_sig);
        
        slatch0.set_in(d_in);
        slatch0.clk_in(clkn_sig);
        slatch1.set_in(slatch0.q_internal_sig);
        slatch1.clk_in(clk_in);
    }
};

SC_MODULE(DFlipFlop)              
{
    sc_in<bool> d_in, clk_in; 
    sc_signal<bool> clkn_sig; 
    //sc_port<sc_signal_inout_if<bool>, 0, SC_ONE_OR_MORE_BOUND> q_out, qn_out, q_int_out, qn_int_out;
    sc_out<bool> q_out, qn_out, q_int_out, qn_int_out;
    
    Nand2WithDelay u1;
    SLatchV1 slatch0, slatch1;

    SC_CTOR(DFlipFlop) : u1("u1"), slatch0("slatch0"), slatch1("slatch1"),  
                         clkn_sig("clkn_sig"), d_in("d_in"), clk_in("clk_in"), 
                         q_out("q_out"), qn_out("qn_out"), q_int_out("q_int_out"), qn_int_out("qn_int_out")
    {
        u1.in1(clk_in);
        u1.in2(clk_in);
        u1.out(clkn_sig);
        
        slatch0.set_in(d_in);
        slatch0.clk_in(clkn_sig);
        slatch0.q_out(q_int_out);
        slatch0.qn_out(qn_int_out);
        slatch1.set_in(q_int_out);
        slatch1.clk_in(clk_in);
        slatch1.q_out(q_out);
        slatch1.qn_out(qn_out);

    }
};
#endif
