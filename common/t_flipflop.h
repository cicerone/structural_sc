/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */


#ifndef __TFLIPFLOP_H__
#define __TFLIPFLOP_H__

#include "xor.h"
#include "d_flipflop.h"




SC_MODULE(TFlipFlopR) // reset tflipflop              
{
    sc_in<bool> t_in, clk_in, reset_in; 
    sc_signal<bool> d_sig, q_int_sig, qn_int_sig;
    sc_out<bool> q_out, qn_out;
    
    Xor2 u1;
    DFlipFlopR u2;

    void WriteOutPort() {
        q_out.write(q_int_sig);
        qn_out.write(qn_int_sig);
    }


    SC_CTOR(TFlipFlopR) : u1("u1"), u2("u2"), d_sig("a"), q_int_sig("q_int_sig"), qn_int_sig("qn_int_sig"),
                         t_in("t_in"), clk_in("clk_in"), reset_in("reset_in"), q_out("q_out"), qn_out("qn_out")
    {
        SC_METHOD(WriteOutPort);       
        sensitive << q_int_sig << qn_int_sig; 

        u1.in1(t_in);
        u1.in2(q_int_sig);
        u1.out(d_sig);

        u2.d_in(d_sig);
        u2.clk_in(clk_in);
        u2.reset_in(reset_in);
        u2.q_out(q_int_sig);
        u2.qn_out(qn_int_sig);
    }
};

#endif
