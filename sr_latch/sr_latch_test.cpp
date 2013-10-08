/* ===============================================================================================
Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================================== */

#include "../common/nand.cpp"


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

SC_MODULE(TestGenerator)
{
    sc_out<bool> s_out, r_out;
    sc_in<bool>  clk;
    
    void GenerateSignals()
    {
        while(1)
        {
            cout << "1" << endl;
            s_out.write(false);
            r_out.write(false);
            wait();
            cout << "2" << endl;
            s_out.write(false);
            r_out.write(true);
            wait();
            cout << "3" << endl;
            s_out.write(true);
            r_out.write(false);
            wait();
            cout << "4" << endl;
            s_out.write(true);
            r_out.write(true);
            wait();
            cout << "5" << endl;
        }
    }
    
    SC_CTOR(TestGenerator)
    {
        SC_CTHREAD(GenerateSignals, clk.pos());
    }
};


int sc_main(int argc, char* argv[])
{
    sc_signal<bool> s_sig, r_sig, q_sig, qn_sig;
    sc_clock clk_sig("TestClock", 10, SC_NS, 0.5);

    TestGenerator tg("test_generator");
    tg.s_out(s_sig);
    tg.r_out(r_sig);
    tg.clk(clk_sig);

    SRLatch DUT("SRLatch");
    DUT.clk_in(clk_sig);
    DUT.set_in(s_sig);
    DUT.reset_in(r_sig);
   // DUT.q_out(q_sig);
   // DUT.qn_out(qn_sig);

    sc_trace_file* p_trace_file;
    p_trace_file = sc_create_vcd_trace_file("traces");
    sc_trace(p_trace_file, s_sig  , "set" );
    sc_trace(p_trace_file, r_sig  , "reset" );
    sc_trace(p_trace_file, q_sig  , "q" );
    sc_trace(p_trace_file, qn_sig  , "qn" );
    sc_trace(p_trace_file, clk_sig  , "clk" );
    sc_trace(p_trace_file, DUT.a_sig  , "a" );
    sc_trace(p_trace_file, DUT.b_sig  , "b" );
    sc_trace(p_trace_file, DUT.q_internal_sig  , "q_int" );
    sc_trace(p_trace_file, DUT.qn_internal_sig  , "qn_int" );

    sc_start(70, SC_NS); 
    sc_close_vcd_trace_file(p_trace_file);

    return 0;
}




