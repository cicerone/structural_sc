/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */


#ifndef __SLATCH_H__
#define __SLATCH_H__


#include "nand.h"


SC_MODULE(SLatchV0)              
{
    sc_in<bool> set_in, clk_in;  
    sc_signal<bool> a_sig, b_sig, reset_sig, q_internal_sig, qn_internal_sig; 
    
    Nand2WithDelay u1;
    Nand2WithDelay u2;
    Nand2WithDelay u3;
    Nand2WithDelay u4;
    Nand2WithDelay u5;

    SC_CTOR(SLatchV0) : u1("u1"), u2("u2"), u3("u3"), u4("u4"), u5("u5"),
                       set_in("set_in"), clk_in("clk_in"), a_sig("a_sig"), b_sig("b_sig"), 
                       reset_sig("reset_sig"), q_internal_sig("q_internal_sig"), 
                       qn_internal_sig("qn_internal_sig")
    {
        u1.in1(set_in);
        u1.in2(clk_in);
        u1.out(a_sig);

        u2.in1(clk_in);
        u2.in2(reset_sig);
        u2.out(b_sig);

        u3.in1(a_sig);
        u3.in2(qn_internal_sig);
        u3.out(q_internal_sig);

        u4.in1(q_internal_sig);
        u4.in2(b_sig);
        u4.out(qn_internal_sig);

        u5.in1(set_in);
        u5.in2(set_in);
        u5.out(reset_sig);
    }
};

SC_MODULE(SLatchV1)              
{
    sc_in<bool> set_in, clk_in;  
    sc_out<bool> q_out, qn_out;
    sc_signal<bool> a_sig, b_sig, reset_sig, q_internal_sig, qn_internal_sig; 
    
    Nand2WithDelay u1;
    Nand2WithDelay u2;
    Nand2WithDelay u3;
    Nand2WithDelay u4;
    Nand2WithDelay u5;
  
    void WriteOutPort() {
        q_out.write(q_internal_sig);
        qn_out.write(qn_internal_sig);
    }



    SC_CTOR(SLatchV1) : u1("u1"), u2("u2"), u3("u3"), u4("u4"), u5("u5"),
                      set_in("set_in"), clk_in("clk_in"), q_out("q_out"), qn_out("qn_out"), 
                      a_sig("a_sig"), b_sig("b_sig"), reset_sig("reset_sig"), q_internal_sig("q_internal_sig"), 
                      qn_internal_sig("qn_internal_sig")
    {
        SC_METHOD(WriteOutPort);       
        sensitive << q_internal_sig << qn_internal_sig; 

        u1.in1(set_in);
        u1.in2(clk_in);
        u1.out(a_sig);

        u2.in1(clk_in);
        u2.in2(reset_sig);
        u2.out(b_sig);

        u3.in1(a_sig);
        u3.in2(qn_internal_sig);
        u3.out(q_internal_sig);

        u4.in1(q_internal_sig);
        u4.in2(b_sig);
        u4.out(qn_internal_sig);

        u5.in1(set_in);
        u5.in2(set_in);
        u5.out(reset_sig);
    }
};

SC_MODULE(SLatchWithTwoOut)              
{
    sc_in<bool> set_in, clk_in;  
    sc_port<sc_signal_inout_if<bool>, 2, SC_ONE_OR_MORE_BOUND> q_out, qn_out;
    sc_signal<bool> a_sig, b_sig, reset_sig, q_internal_sig, qn_internal_sig; 
    
    Nand2WithTwoOut u1;
    Nand2WithTwoOut u2;
    Nand2WithTwoOut u3;
    Nand2WithTwoOut u4;
    Nand2WithTwoOut u5;

    SC_CTOR(SLatchWithTwoOut) : u1("u1"), u2("u2"), u3("u3"), u4("u4"), u5("u5"),
                      set_in("set_in"), clk_in("clk_in"), q_out("q_out"), qn_out("qn_out"), 
                      a_sig("a_sig"), b_sig("b_sig"), reset_sig("reset_sig"), q_internal_sig("q_internal_sig"), 
                      qn_internal_sig("qn_internal_sig")
    {

        u1.in1(set_in);
        u1.in2(clk_in);
        u1.out(a_sig);

        u2.in1(clk_in);
        u2.in2(reset_sig);
        u2.out(b_sig);

        u3.in1(a_sig);
        u3.in2(qn_internal_sig);
        u3.out(q_internal_sig);
        u3.out(q_out);

        u4.in1(q_internal_sig);
        u4.in2(b_sig);
        u4.out(qn_internal_sig);
        u4.out(qn_out);

        u5.in1(set_in);
        u5.in2(set_in);
        u5.out(reset_sig);
    }
};

#endif
