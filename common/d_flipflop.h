/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */


#ifndef __DFLIPFLOP_H__
#define __DFLIPFLOP_H__


#include "s_latch.h"


SC_MODULE(DFlipFlop)              
{
    sc_in<bool> d_in, clk_in;    // input signal ports
    //sc_port<sc_signal_out_if<bool>, 2> q_out, qn_out;              // output signal ports
    sc_signal<bool> clkn_sig, q_sig, qn_sig; 
    
    Nand2WithDelay u1;
    SLatch slatch0, slatch1;

    SC_CTOR(DFlipFlop) : u1("u1"), slatch0("slatch0"), slatch1("slatch1"),  
                         q_sig("q_sig"), qn_sig("qn_sig"), clkn_sig("clkn_sig"), 
                         d_in("d_in"), clk_in("clk_in")
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

#endif
