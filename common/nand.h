/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */

#ifndef __NAND2_H__
#define __NAND2_H__

#include "systemc.h"

SC_MODULE(Nand2)                   // declare Nand2 sc_module
{
    sc_in<bool> in1_in, in2_in;    // input signal ports
    sc_out<bool> out_out;          // output signal ports
    
    void ComputeNand()      
    {
        out_out.write( !(in1_in.read() && in2_in.read()) );
    }
    
    SC_CTOR(Nand2) : in1_in("in1"), in2_in("in2"), out_out("out")
    {
        SC_METHOD(ComputeNand);         // register do_nand2 with kernel
        sensitive << in1_in << in2_in;  // sensitivity list
    }
};


SC_MODULE(Nand2WithDelay)                   // declare Nand2 sc_module
{
    sc_in<bool> in1_in, in2_in;    // input signal ports
    sc_out<bool> out_out;          // output signal ports
    double delay_high2low, delay_low2high;  // propagation delay times
    bool         previous_value;
    bool         is_delayed_output;
    
    void ComputeNand()      
    {
        bool current_value = !(in1_in.read() && in2_in.read());
        if (is_delayed_output) {
            out_out.write(current_value);
            is_delayed_output = false;
        }
        else 
        {
            if (previous_value == current_value) {
                out_out.write(current_value);
                is_delayed_output = false;
            }
            else {
                is_delayed_output = true;
                if (previous_value == true) {
                    next_trigger(delay_high2low, SC_NS);
                }
                else {
                    next_trigger(delay_low2high, SC_NS);
                }
                previous_value = current_value;
            }
        }
        
    }
    
    SC_CTOR(Nand2WithDelay)                      // constructor for Nand2
    {
        SC_METHOD(ComputeNand);         // register do_nand2 with kernel
        sensitive << in1_in << in2_in;  // sensitivity list

        delay_high2low = 0.1; // measured in ns
        delay_low2high = 0.1; 
        previous_value = false;
        is_delayed_output = false;
    }
};

#endif

