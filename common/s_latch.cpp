/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */


SC_MODULE(SLatch)              
{
    sc_in<bool> set_in, clk_in;    // input signal ports
    //sc_port<sc_signal_out_if<bool>, 2> q_out, qn_out;              // output signal ports
    sc_signal<bool> a_sig, b_sig, reset_sig, q_internal_sig, qn_internal_sig; // internal signals
    
    Nand2WithDelay u1;
    Nand2WithDelay u2;
    Nand2WithDelay u3;
    Nand2WithDelay u4;
    Nand2WithDelay u5;

    SC_CTOR(SLatch) : u1("u1"), u2("u2"), u3("u3"), u4("u4"), u5("u5"),
                       set_in("set_in"), clk_in("clk_in")
    {
        u1.in1_in(set_in);
        u1.in2_in(clk_in);
        u1.out_out(a_sig);

        u2.in1_in(clk_in);
        u2.in2_in(reset_sig);
        u2.out_out(b_sig);

        u3.in1_in(a_sig);
        u3.in2_in(qn_internal_sig);
        u3.out_out(q_internal_sig);

        u4.in1_in(q_internal_sig);
        u4.in2_in(b_sig);
        u4.out_out(qn_internal_sig);

        u5.in1_in(set_in);
        u5.in2_in(set_in);
        u5.out_out(reset_sig);
    }
};


