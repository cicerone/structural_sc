#include "systemc.h"
#include <iomanip>      // std::setw

using namespace std;

SC_MODULE(Nand2)                   // declare Nand2 sc_module
{
    sc_in<bool> In1_in, In2_in;    // input signal ports
    sc_out<bool> Out_out;          // output signal ports
    
    void ComputeNand()      
    {
        Out_out.write( !(In1_in.read() && In2_in.read()) );
    }
    
    SC_CTOR(Nand2)                      // constructor for Nand2
    {
        SC_METHOD(ComputeNand);         // register do_nand2 with kernel
        sensitive << In1_in << In2_in;  // sensitivity list
    }
};



SC_MODULE(TestGenerator)
{
    sc_out<bool> In1_out, In2_out;
    sc_in<bool>  Clk;
    
    void GenerateSignals()
    {
        while(1)
        {
            In1_out.write(false);
            In2_out.write(false);
            wait();
            In1_out.write(false);
            In2_out.write(true);
            wait();
            In1_out.write(true);
            In2_out.write(false);
            wait();
            In1_out.write(true);
            In2_out.write(true);
            wait();
        }
    }
    
    SC_CTOR(TestGenerator)
    {
        SC_THREAD(GenerateSignals);
        sensitive << Clk.pos();
    }
};



int sc_main(int argc, char* argv[])
{
  sc_signal<bool> ASig, BSig, FSig;
  sc_clock TestClk("TestClock", 10, SC_NS,0.5);


  TestGenerator Stim1("Stimulus");
  Stim1.In1_out(ASig);
  Stim1.In2_out(BSig);
  Stim1.Clk(TestClk);

  Nand2 DUT("NAND2");
  DUT.In1_in(ASig);
  DUT.In2_in(BSig);
  DUT.Out_out(FSig);

  sc_trace_file* Tf;
  Tf = sc_create_vcd_trace_file("traces");
 // ((vcd_trace_file*)Tf)->sc_set_vcd_time_unit(-9);
  sc_trace(Tf, ASig  , "In1" );
  sc_trace(Tf, BSig  , "In2" );
  sc_trace(Tf, FSig  , "Out" );

  sc_start(70, SC_NS); 
  sc_close_vcd_trace_file(Tf);

  return 0;

}




