/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */

#ifndef __NAND2_H__
#define __NAND2_H__

#include "systemc.h"

SC_MODULE(Nand2Ideal)                
{
    sc_in<bool> in1, in2;   
    sc_out<bool> out;      
    
    void ComputeNand()      
    {
        out.write( !(in1.read() && in2.read()) );
    }
    
    SC_CTOR(Nand2Ideal) : in1("in1"), in2("in2"), out("out")
    {
        SC_METHOD(ComputeNand);  
        sensitive << in1 << in2; 
    }
};


SC_MODULE(Nand2WithDelay)       
{
    sc_in<bool> in1, in2;   
    sc_out<bool> out;
    unsigned int delay_high2low, delay_low2high; 
    bool         previous_value;
    bool         is_delayed_output;
    
    void ComputeNand()      
    {
        bool current_value = !(in1.read() && in2.read());
        if (is_delayed_output) {
            out->write(current_value);
            is_delayed_output = false;
        }
        else 
        {
            if (previous_value == current_value) {
                out->write(current_value);
                is_delayed_output = false;
            }
            else {
                is_delayed_output = true;
                if (previous_value == true) {
                    next_trigger(delay_high2low, SC_PS);
                }
                else {
                    next_trigger(delay_low2high, SC_PS);
                }
                previous_value = current_value;
            }
        }
        
    }
    
    SC_CTOR(Nand2WithDelay) : in1("in1"), in2("in2"), out("out")
    {
        SC_METHOD(ComputeNand);       
        sensitive << in1 << in2; 

        delay_high2low = 100;
        delay_low2high = 100; 
        previous_value = false;
        is_delayed_output = false;
    }
};

SC_MODULE(Nand2WithTwoOut)       
{
    sc_in<bool> in1, in2;   
    //sc_out<bool> out;
    sc_port<sc_signal_inout_if<bool>, 2, SC_ONE_OR_MORE_BOUND> out;
    unsigned int delay_high2low, delay_low2high; 
    bool         previous_value;
    bool         is_delayed_output;
    
    void ComputeNand()      
    {
        bool current_value = !(in1.read() && in2.read());
        if (is_delayed_output) {
            for (unsigned i = 0; i != out.size(); i++) {
                out[i]->write(current_value);
            }
            is_delayed_output = false;
        }
        else 
        {
            if (previous_value == current_value) {
                for (unsigned i = 0; i != out.size(); i++) {
                    out[i]->write(current_value);
                }
                is_delayed_output = false;
            }
            else {
                is_delayed_output = true;
                if (previous_value == true) {
                    next_trigger(delay_high2low, SC_PS);
                }
                else {
                    next_trigger(delay_low2high, SC_PS);
                }
                previous_value = current_value;
            }
        }
    }
    
    SC_CTOR(Nand2WithTwoOut) : in1("in1"), in2("in2"), out("out")
    {
        SC_METHOD(ComputeNand);       
        sensitive << in1 << in2; 

        delay_high2low = 100;
        delay_low2high = 100; 
        previous_value = false;
        is_delayed_output = false;
    }
};

SC_MODULE(Nand3WithDelay)       
{
    sc_in<bool>  in1, in2, in3;   
    sc_out<bool> out;
    unsigned int delay_high2low, delay_low2high; 
    bool         previous_value;
    bool         is_delayed_output;
    
    void ComputeNand()      
    {
        bool current_value = !(in1.read() && in2.read() && in3.read());
        if (is_delayed_output) {
            out->write(current_value);
            is_delayed_output = false;
        }
        else 
        {
            if (previous_value == current_value) {
                out->write(current_value);
                is_delayed_output = false;
            }
            else {
                is_delayed_output = true;
                if (previous_value == true) {
                    next_trigger(delay_high2low, SC_PS);
                }
                else {
                    next_trigger(delay_low2high, SC_PS);
                }
                previous_value = current_value;
            }
        }
        
    }
    
    SC_CTOR(Nand3WithDelay) : in1("in1"), in2("in2"), in3("in3"), out("out")
    {
        SC_METHOD(ComputeNand);       
        sensitive << in1 << in2 << in3; 

        delay_high2low = 100;
        delay_low2high = 100; 
        previous_value = false;
        is_delayed_output = false;
    }
};

SC_MODULE(Nand)
{
    sc_vector<sc_in<bool> > in;   
    sc_out<bool> out;
    unsigned int delay_high2low, delay_low2high; 
    bool         previous_value;
    bool         is_delayed_output;
    
    void ComputeNand()      
    {
        bool current_value = true;
        for( unsigned i= 0; i < in.size(); ++i )
        {
            current_value = (current_value && in[i].read());
        }
        current_value = !current_value;

        if (is_delayed_output) {
            out->write(current_value);
            is_delayed_output = false;
        }
        else 
        {
            if (previous_value == current_value) {
                out->write(current_value);
                is_delayed_output = false;
            }
            else {
                is_delayed_output = true;
                if (previous_value == true) {
                    next_trigger(delay_high2low, SC_PS);
                }
                else {
                    next_trigger(delay_low2high, SC_PS);
                }
                previous_value = current_value;
            }
        }
        
    }
    
    SC_HAS_PROCESS(Nand);
    Nand(sc_module_name name_, unsigned nr_inputs_= 2) : in("in", nr_inputs_), out("out")
    {
        SC_METHOD(ComputeNand);       
        for( unsigned i= 0; i < in.size(); ++i )
            sensitive << in[i];

        delay_high2low = 100;
        delay_low2high = 100; 
        previous_value = false;
        is_delayed_output = false;
    }
};

#endif

