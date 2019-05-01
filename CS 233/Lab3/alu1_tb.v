module alu1_test;
    // exhaustively test your 1-bit ALU by adapting mux4_tb.v
    reg A_in=0;
    always #1 A_in=!A_in;
    reg B_in=0;
    always #2 B_in=!B_in;
    reg carryin_in=0;
    always #3 carryin_in=!carryin_in;

    reg [2:0] control=3'h0;
                               // these are inputs to "circuit under test"
                                              // use "reg" not "wire" so can assign a value
    wire out_out, carryout_out;                         // wires for the outputs of "circuit under test"

    alu1 l1(out_out, carryout_out,A_in, B_in,carryin_in,control[2:0]);  // the circuit under test
    
    initial begin                             // initial = run at beginning of simulation
                                              // begin/end = associate block with initial
 
        $dumpfile("alu1.vcd");                 
        $dumpvars(0,alu1_test);                 
                                               
        # 8 control = 3'h1; 
        # 8 control = 3'h2; 
        # 8 control = 3'h3; 
        # 8 control = 3'h4; 
        # 8 control = 3'h5; 
        # 8 control = 3'h6;  
        # 8 control = 3'h7; 
        # 8 

        $finish;                              // end the simulation
    end                      
    
    initial
        $monitor("At time %2t, A_in = %d  B_in = %d carryin_in=%d control_in =%d carryout_out=%d out_out = %d ",
                 $time, A_in, B_in, carryin_in, control, carryout_out, out_out);
endmodule
