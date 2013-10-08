/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */

#include "systemc.h"

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


