module keypad(valid, number, a, b, c, d, e, f, g);
   output 	valid;
   output [3:0] number;
   input 	a, b, c, d, e, f, g;
   wire     w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14;

  // valid or not
   or o1(valid, a, b, c);
  //index 0 
   and a1(w1,a,d);
   and a2(w2,c,d);
   and a3(w3,a,f);
   and a4(w4,c,f);
   and a5(w5,b,e);
   or o2(number[0],w1,w2,w3,w4);
  //index 1  
   and a6(w6,b,d);
   and a7(w7,c,d);
   and a8(w8,c,e);
   or o3(number[1],w6,w7,w8);
  //index 2
   and a9(w9,a,e);
   and a10(w10,b,e);
   and a11(w11,c,e);
   and a12(w12,a,f);
   or o4(number[2],w9,w10,w11,w12);
  //index 3 
   and a13(w13,b,f);
   and a14(w14,c,f);
   or o5(number[3],w13,w14);
  
endmodule // keypad
