/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */


#ifndef __XOR_H__
#define __XOR_H__


#include "nand.h"


SC_MODULE(Xor2Ver0)              

{
    sc_in<bool> in1, in2;  
    sc_out<bool> out;
    sc_signal<bool> a_sig, b_sig, c_sig, d_sig;
    
    Nand2WithDelay u1;
    Nand2WithDelay u2;
    Nand2WithDelay u3;
    Nand2WithDelay u4;
    Nand2WithDelay u5;

    SC_CTOR(Xor2Ver0) : u1("u1"), u2("u2"), u3("u3"), u4("u4"), u5("u5"),
                    in1("in1"), in2("in2"), a_sig("a_sig"), b_sig("b_sig"), 
                    c_sig("c_sig"), d_sig("d_sig"), out("out")
    {
        u1.in1(in2);
        u1.in2(in2);
        u1.out(a_sig);

        u2.in1(in1);
        u2.in2(in1);
        u2.out(b_sig);

        u3.in1(in1);
        u3.in2(a_sig);
        u3.out(c_sig);

        u4.in1(in2);
        u4.in2(b_sig);
        u4.out(d_sig);

        u5.in1(c_sig);
        u5.in2(d_sig);
        u5.out(out);
    }
};

SC_MODULE(Xor2)              

{
    sc_in<bool> in1, in2;  
    sc_out<bool> out;
    sc_signal<bool> a_sig, b_sig, c_sig;
    
    Nand2WithDelay u1;
    Nand2WithDelay u2;
    Nand2WithDelay u3;
    Nand2WithDelay u4;

    SC_CTOR(Xor2) : u1("u1"), u2("u2"), u3("u3"), u4("u4"), 
                    in1("in1"), in2("in2"), a_sig("a_sig"), b_sig("b_sig"), 
                    c_sig("c_sig"), out("out")
    {
        u1.in1(in1);
        u1.in2(in2);
        u1.out(a_sig);

        u2.in1(in1);
        u2.in2(a_sig);
        u2.out(b_sig);

        u3.in1(a_sig);
        u3.in2(in2);
        u3.out(c_sig);

        u4.in1(b_sig);
        u4.in2(c_sig);
        u4.out(out);

    }
};

#endif
