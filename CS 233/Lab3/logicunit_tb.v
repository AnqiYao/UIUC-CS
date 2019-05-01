module logicunit_test;
    // exhaustively test your logic unit by adapting mux4_tb.v
    
    
    reg A_in, B_in;
    reg [1:0] control;
                               // these are inputs to "circuit under test"
                                              // use "reg" not "wire" so can assign a value
    wire out_out;                         // wires for the outputs of "circuit under test"

    logicunit log1(out_out, A_in, B_in, control[1:0]);  // the circuit under test
    
    initial begin                             // initial = run at beginning of simulation
                                              // begin/end = associate block with initial
 
        $dumpfile("logicunit.vcd");                 
        $dumpvars(0,logicunit_test);                 
                                               
        // test all four input combinations
        // remember that 2 inputs means 2^2 = 4 combinations
        // 3 inputs would mean 2^3 = 8 combinations to test, and so on
        // this is very similar to the input columns of a truth table
        A_in = 0; B_in = 0; control = 2'b00;  # 10;             // set initial values and wait 10 time units
        A_in = 0; B_in = 0; control = 2'b01;  # 10;            // change inputs and then wait 10 time units
        A_in = 0; B_in = 0; control = 2'b10;  # 10;            // as above
        A_in = 0; B_in = 0; control = 2'b11;  # 10;
        A_in = 0; B_in = 1; control = 2'b00;  # 10;            // set initial values and wait 10 time units
        A_in = 0; B_in = 1; control = 2'b01;  # 10;           // change inputs and then wait 10 time units
        A_in = 0; B_in = 1; control = 2'b10;  # 10;          // as above
        A_in = 0; B_in = 1; control = 2'b11;  # 10;
        A_in = 1; B_in = 0; control = 2'b00;  # 10;
        A_in = 1; B_in = 0; control = 2'b01;  # 10;
        A_in = 1; B_in = 0; control = 2'b10;  # 10;
        A_in = 1; B_in = 0; control = 2'b11;  # 10;
        A_in = 1; B_in = 1; control = 2'b00;  # 10;
        A_in = 1; B_in = 1; control = 2'b01;  # 10;
        A_in = 1; B_in = 1; control = 2'b10;  # 10;
        A_in = 1; B_in = 1; control = 2'b11;  # 10;
        
        $finish;                              // end the simulation
    end                      
    
    initial
        $monitor("At time %2t, A_in = %d  B_in = %d  control_in =%d  out_out = %d ",
                 $time, A_in, B_in, control, out_out);
endmodule // logicunit_test
