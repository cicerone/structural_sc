/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */

#ifndef __SRLATCH_H__
#define __SRLATCH_H__


#include "nand.h"

SC_MODULE(SRLatch)              
{
    sc_in<bool> set_in, reset_in, clk_in;    // input signal ports
    //sc_port<sc_signal_out_if<bool>, 2> q_out, qn_out;              // output signal ports
    sc_signal<bool> a_sig, b_sig, q_internal_sig, qn_internal_sig; // internal signals
    
    Nand2WithDelay u1;
    Nand2WithDelay u2;
    Nand2WithDelay u3;
    Nand2WithDelay u4;

    SC_CTOR(SRLatch) : u1("u1"), u2("u2"), u3("u3"), u4("u4"), 
                       set_in("set_in"), reset_in("reset_in"), clk_in("clk_in")
                       //q_out("q_out"), qn_out("qn_out") 
    {
        u1.in1_in(set_in);
        u1.in2_in(clk_in);
        u1.out_out(a_sig);

        u2.in1_in(clk_in);
        u2.in2_in(reset_in);
        u2.out_out(b_sig);

        u3.in1_in(a_sig);
        u3.in2_in(qn_internal_sig);
        u3.out_out(q_internal_sig);

        u4.in1_in(q_internal_sig);
        u4.in2_in(b_sig);
        u4.out_out(qn_internal_sig);
    }
};

#endif

