module blackbox_test;

    
    reg y_in, t_in , e_in;                           // these are inputs to "circuit under test"
                                              // use "reg" not "wire" so can assign a value
    wire n_out;                         // wires for the outputs of "circuit under test"

    blackbox bb1 (n_out, y_in, t_in, e_in);  // the circuit under test
    
    initial begin                             // initial = run at beginning of simulation
                                              // begin/end = associate block with initial
 
        $dumpfile("blackbox.vcd");                 
        $dumpvars(0,blackbox_test);                 
                                               
        // test all four input combinations
        // remember that 2 inputs means 2^2 = 4 combinations
        // 3 inputs would mean 2^3 = 8 combinations to test, and so on
        // this is very similar to the input columns of a truth table
        y_in = 0; t_in = 0; e_in = 0; # 10;             // set initial values and wait 10 time units
        y_in = 0; t_in = 1; e_in = 0; # 10;             // change inputs and then wait 10 time units
        y_in = 1; t_in = 0; e_in = 0; # 10;             // as above
        y_in = 1; t_in = 1; e_in = 0; # 10;
        y_in = 0; t_in = 0; e_in = 1; # 10;             // set initial values and wait 10 time units
        y_in = 0; t_in = 1; e_in = 1; # 10;             // change inputs and then wait 10 time units
        y_in = 1; t_in = 0; e_in = 1; # 10;             // as above
        y_in = 1; t_in = 1; e_in = 1; # 10;
 
        $finish;                              // end the simulation
    end                      
    
    initial
        $monitor("At time %2t, y_in = %d t_in = %d e_in = %d n_out = %d ",
                 $time, y_in, t_in, e_in, n_out);

endmodule // blackbox_test
