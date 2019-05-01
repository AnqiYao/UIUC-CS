// A priority encoder is a circuit (or algorithm) that compresses
// multiple binary inputs into a smaller number of outputs. The output
// of a priority encoder is the binary representation of the most
// significant input bit.  For example, if only the 'a1' input is
// set (i.e., inputs 'a0', 'a2', and 'a3' are zero), then the output
// is a binary representation of the number one.

// If multiple input bits are set, then the output is set to the
// value of the most significant one.  For example, if both 'a0' and
// 'a3' are set, then 'out' is set to the binary representation
// for the number three.

// The 'valid' output indicates that at least one input bit is set
// so that the 'out' signal correctly represents the priority of
// highest priority set input bit.

module priority_encoder(out, valid, a0, a1, a2, a3);
   output [1:0] out;
   output 	valid;
   input 	a0, a1, a2, a3;
   wire not_3,not_2,not_1,w1,w2,w3,w4,w5;
  
   not n1(not_3,a3);
   not n2(not_2,a2);
   not n1(not_1,a1);
   or o1(valid,a0,a1,a2,a3);
  //a3 being biggest
   and an1(w1,valid,a3);
  //a2 being biggest
   and an2(w2,a2,not_3);
  //a1 being biggest
   and an3(w3,not_3,not_2);
   and an4(w4,w3,a1);
  //a0 being biggest
   and an5(w5,w3,not_1);
   
   or o2(out[0],w1,w4);
   or o3(out[1],w1,w2);

endmodule // priority_encoder

