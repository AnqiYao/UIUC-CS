module test;

   // these are inputs to "circuit under test"
   reg       a0;
   reg       a1;
   reg       a2;
   reg       a3;
  // wires for the outputs of "circuit under test"
   wire [1:0] out;
   wire       valid;
  // the circuit under test
   priority_encoder p(out, valid, a0, a1, a2, a3);  
    
   initial begin               // initial = run at beginning of simulation
                               // begin/end = associate block with initial
      
      $dumpfile("test.vcd");  // name of dump file to create
      $dumpvars(0, test);     // record all signals of module "test" and sub-modules
                              // remember to change "test" to the correct
                              // module name when writing your own test benches
        
      // test all input combinations
      a0 = 0; a1 = 0; a2 = 0; a3 = 0; #10;
      a0 = 0; a1 = 0; a2 = 0; a3 = 1; #10;
      a0 = 0; a1 = 0; a2 = 1; a3 = 0; #10;
      a0 = 0; a1 = 0; a2 = 1; a3 = 1; #10;
      a0 = 0; a1 = 1; a2 = 0; a3 = 0; #10;
      a0 = 0; a1 = 1; a2 = 0; a3 = 1; #10;
      a0 = 0; a1 = 1; a2 = 1; a3 = 0; #10;
      a0 = 0; a1 = 1; a2 = 1; a3 = 1; #10;
      a0 = 1; a1 = 0; a2 = 0; a3 = 0; #10;
      a0 = 1; a1 = 0; a2 = 0; a3 = 1; #10;
      a0 = 1; a1 = 0; a2 = 1; a3 = 0; #10;
      a0 = 1; a1 = 0; a2 = 1; a3 = 1; #10;
      a0 = 1; a1 = 1; a2 = 0; a3 = 0; #10;
      a0 = 1; a1 = 1; a2 = 0; a3 = 1; #10;
      a0 = 1; a1 = 1; a2 = 1; a3 = 0; #10;
      a0 = 1; a1 = 1; a2 = 1; a3 = 1; #10;
      
      $finish;        // end the simulation
   end                      
   
   initial begin
     $display("inputs = a0, a1, a2, a3  outputs = out, valid");
     $monitor("inputs = %b  %b  %b  %b  outputs = %b  %b   time = %2t",
              a0, a1, a2, a3, out, valid, $time);
   end
endmodule // test
