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

SC_MODULE(DFlipFlopMasterSlave)              
{
    sc_in<bool> d_in, clk_in; 
    sc_signal<bool> clkn_sig; 
    sc_out<bool> q_out, qn_out, q_int_out, qn_int_out;
    
    Nand2WithDelay u1;
    SLatchV1 slatch0, slatch1;

    SC_CTOR(DFlipFlopMasterSlave) : u1("u1"), slatch0("slatch0"), slatch1("slatch1"),  
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

SC_MODULE(DFlipFlop)              
{
    sc_in<bool> d_in, clk_in; 
    sc_signal<bool> a_sig, b_sig, c_sig, d_sig, q_int_sig, qn_int_sig; 
    sc_out<bool> q_out, qn_out;
    
    Nand2WithDelay u1, u2, u3, u4, u5;
    Nand3WithDelay u6;

    void WriteOutPort() {
        q_out.write(q_int_sig);
        qn_out.write(qn_int_sig);
    }

    SC_CTOR(DFlipFlop) : u1("u1"), u2("u2"), u3("u3"), u4("u4"), u5("u5"), u6("u6"),  
                         a_sig("a"), b_sig("b"), c_sig("c"), d_sig("d"), 
                         q_int_sig("q_int"), qn_int_sig("qn_int"), d_in("d_in"), clk_in("clk_in"), 
                         q_out("q_out"), qn_out("qn_out")
    {
        SC_METHOD(WriteOutPort);       
        sensitive << q_int_sig << qn_int_sig; 

        u1.in1(b_sig);
        u1.in2(d_sig);
        u1.out(c_sig);
        
        u2.in1(c_sig);
        u2.in2(clk_in);
        u2.out(d_sig);

        u3.in1(q_int_sig);
        u3.in2(a_sig);
        u3.out(qn_int_sig);

        u4.in1(d_sig);
        u4.in2(qn_int_sig);
        u4.out(q_int_sig);

        u5.in1(d_in);
        u5.in2(a_sig);
        u5.out(b_sig);

        u6.in1(b_sig);
        u6.in2(d_sig);
        u6.in3(clk_in);
        u6.out(a_sig);
    }
};

SC_MODULE(DFlipFlopSR) // set reset dflipflop              
{
    sc_in<bool> d_in, clk_in, set_in, reset_in; 
    sc_signal<bool> a_sig, b_sig, c_sig, e_sig, q_int_sig, qn_int_sig; 
    sc_out<bool> q_out, qn_out;
    
    Nand3WithDelay u1, u2, u3, u4, u5, u6;

    void WriteOutPort() {
        q_out.write(q_int_sig);
        qn_out.write(qn_int_sig);
    }

    SC_CTOR(DFlipFlopSR) : u1("u1"), u2("u2"), u3("u3"), u4("u4"), u5("u5"), u6("u6"),  
                         a_sig("a"), b_sig("b"), c_sig("c"), e_sig("d"), 
                         q_int_sig("q_int"), qn_int_sig("qn_int"), d_in("d_in"), clk_in("clk_in"), 
                         set_in("set_in"), reset_in("reset_in"), q_out("q_out"), qn_out("qn_out")
    {
        SC_METHOD(WriteOutPort);       
        sensitive << q_int_sig << qn_int_sig; 

        u1.in1(set_in);
        u1.in2(a_sig);
        u1.in3(c_sig);
        u1.out(e_sig);

        u2.in1(e_sig);
        u2.in2(clk_in);
        u2.in3(reset_in);
        u2.out(c_sig);

        u3.in1(c_sig);
        u3.in2(clk_in);
        u3.in3(a_sig);
        u3.out(b_sig);

        u4.in1(b_sig);
        u4.in2(d_in);
        u4.in3(reset_in);
        u4.out(a_sig);

        u5.in1(set_in);
        u5.in2(c_sig);
        u5.in3(qn_int_sig);
        u5.out(q_int_sig);

        u6.in1(q_int_sig);
        u6.in2(b_sig);
        u6.in3(reset_in);
        u6.out(qn_int_sig);
    }
};

#endif
